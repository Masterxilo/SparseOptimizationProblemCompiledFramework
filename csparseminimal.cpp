#pragma once

/*
CSPARSE library, reduced to only the things needed for sparse conjugate gradient method
and for running on CUDA, with a user-supplied memory-pool

Based on
CSparse Version 1.2.0 Copyright (c) Timothy A. Davis, 2006
without permission
*/

#include <math.h>
#include <assert.h>
#include <memory.h> // memset
#include <paul.h>

#ifdef __CUDACC__
#define CSPARSEFUNC __host__ __device__
#else
#define CSPARSEFUNC 
#endif

// can work with any floating point type
// TODO if this is 8 bytes instead of 4, many nextEven calls could be saved
typedef float real;

/* --- primary CSparse routines and data structures ------------------------- */
typedef struct cs_sparse    /* matrix in compressed-column or triplet form . must be aligned on 8 bytes */
{
    int nzmax;	    /* maximum number of entries */
    int m;	    /* number of rows */

    int n;	    /* number of columns */
    int nz;	    /* # of entries in triplet matrix, -1 for compressed-col */

    // this order preserves alignment
    int *p;	    /* column pointers (size n+1) or col indices (size nzmax) */

    int *i;	    /* row indices, size nzmax */

    real *x;	    /* numerical values, size nzmax, always valid*/

} cs;

CSPARSEFUNC bool cs_is_triplet(const cs *A) {
    assert(A);
    return A->nz >= 0;
}
const int NZ_COMPRESSED_COLUMN_INDICATOR = -1;

CSPARSEFUNC bool cs_is_compressed_col(const cs *A) {
    assert(A);
    assert(A->m >= 1 && A->n >= 1);
    return A->nz == NZ_COMPRESSED_COLUMN_INDICATOR;
}



// hacky arbitrary memory-management by passing
// reduces memory_size and increases memoryPool on use
#define MEMPOOL char*& memoryPool, int& memory_size
#define MEMPOOLPARAM memoryPool, memory_size

// allocate new stuff can only allocate multiples of 8 bytes to preserve alignment of pointers in cs
CSPARSEFUNC char* cs_malloc_(char*& memoryPool, int& memory_size, size_t sz) {
    assert(memory_size >= sz);
    assert(aligned(memoryPool, 8));
    assert(divisible(sz, 8)); 
    auto out = memoryPool;
    memoryPool += sz; 
    memory_size -= sz; 
    return out;
}

#define cs_malloc(varname, sz) {(varname) = (decltype(varname))cs_malloc_(MEMPOOLPARAM, (sz));}

// free the last allocated thing of given size
CSPARSEFUNC void cs_free_(char*& memoryPool, int& memory_size, size_t sz) {
    assert(divisible(sz, 8));
    assert(aligned(memoryPool, 8));
    memoryPool -= sz;
    memory_size += sz;
}

#define cs_free(sz) {cs_free_(MEMPOOLPARAM, (sz));}

CSPARSEFUNC int nextEven(int i) { // support even allocation
    if (i % 2 == 0) return i;
    return i + 1;
}

/* amount of bytes a sparse matrix with the given characteristics will occupy */
CSPARSEFUNC int cs_spalloc_size(size_t m, size_t n, size_t nzmax, bool triplet) {
    return sizeof(cs) + nextEven(triplet ? nzmax : n + 1) * sizeof(int) + nextEven(nzmax) *  (sizeof(int) + sizeof(real));
}

/* allocates a sparse matrix using memory starting at memoryPool,
uses exactly
sizeof(cs) + cs_spalloc_size(m, n, nzmax, triplet) BYTES
of the pool

modifies memoryPool to point to the now free memory
*/
CSPARSEFUNC cs *cs_spalloc(size_t m, size_t n, size_t nzmax, bool triplet, MEMPOOL)
{
    char* initial_memoryPool = memoryPool;
    assert(nzmax > 0);

    cs* A; cs_malloc(A, sizeof(cs));    /* allocate the cs struct */

    A->m = m;				    /* define dimensions and nzmax */
    A->n = n;
    A->nzmax = nzmax;
    A->nz = triplet ? 0 : NZ_COMPRESSED_COLUMN_INDICATOR;		    /* allocate triplet or comp.col */

    // Allocate too much to preserve alignment
    cs_malloc(A->p, nextEven(triplet ? nzmax : n + 1) * sizeof(int));
    cs_malloc(A->i, nextEven(nzmax) * sizeof(int));
    cs_malloc(A->x, nextEven(nzmax) * sizeof(real));

    assert(memoryPool == initial_memoryPool + cs_spalloc_size(m, n, nzmax, triplet));
    return A;
}

/* p [0..n] = cumulative sum of c [0..n-1], and then copy p [0..n-1] into c */
CSPARSEFUNC int cs_cumsum(int *p, int *c, int n)
{
    assert(n >= 0 && p && c); /* check inputs */
    int i, nz = 0;
    for (i = 0; i < n; i++)
    {
        p[i] = nz;
        nz += c[i];
        c[i] = p[i];
    }
    p[n] = nz;
    return (nz);		    /* return sum (c [0..n-1]) */
}

CSPARSEFUNC int* allocZeroedIntegers(const int n, MEMPOOL) {
    assert(divisible(n, 2));
    int* w;
    cs_malloc(w, n * sizeof(int));
    memset(w, 0, n*sizeof(int)); // w = (int*)cs_calloc(n, sizeof(int)); /* get workspace */
    return w;
}

// alloc/free a list of integers w, initialized to 0
#define allocTemporaryW(count) int wsz = nextEven((count)); int* w = allocZeroedIntegers(wsz, MEMPOOLPARAM); 
#define freeTemporaryW() cs_free(wsz * sizeof(int)); 

/* C = A'

memoryPool must be big enough to contain the following
cs_spalloc_size(n, m, Ap[n], 0) -- location of output
nextEven(m)*sizeof(int) -- temporary
*/
CSPARSEFUNC cs *cs_transpose(const cs * const A, MEMPOOL)
{
    assert(A && cs_is_compressed_col(A));

    const int m = A->m;
    const int n = A->n;
    int const * const Ai = A->i;
    int const * const Ap = A->p;
    real const * const Ax = A->x;

    cs *C; C = cs_spalloc(n, m, Ap[n], 0, MEMPOOLPARAM); /* allocate result */

    allocTemporaryW(m); /* get workspace */

    int* const Cp = C->p; int* const Ci = C->i; real* const Cx = C->x;
    assert(Cp && Ci && Cx);

    for (int p = 0; p < Ap[n]; p++) w[Ai[p]]++;	   /* row counts */
    cs_cumsum(Cp, w, m);				   /* row pointers */
    for (int j = 0; j < n; j++)
    {
        for (int p = Ap[j]; p < Ap[j + 1]; p++)
        {
            int q;
            Ci[q = w[Ai[p]]++] = j;	/* place A(i,j) as entry C(j,i) */
            Cx[q] = Ax[p];
        }
    }

    freeTemporaryW();

    return C;	/* success; free w and return C */
}

/* C = compressed-column form of a triplet matrix T

memoryPool must be big enough to contain the following
cs_spalloc_size(m, n, nz, 0) -- location of output
nextEven(n)* sizeof(int) -- temporary
*/
CSPARSEFUNC cs *cs_triplet(const cs * const T, MEMPOOL)
{
    assert(T && cs_is_triplet(T));/* check inputs */

    const int m = T->m;
    const int n = T->n;
    int const * const Ti = T->i;
    int const * const Tj = T->p;
    real const * const Tx = T->x;
    const int nz = T->nz;

    assert(m > 0 && n > 0);
    cs *C; C = cs_spalloc(m, n, nz, 0, memoryPool, memory_size);		/* allocate result */

    allocTemporaryW(n); /* get workspace */

    int* const Cp = C->p; int* const Ci = C->i; real* const Cx = C->x;
    assert(Cp && Ci && Cx);

    for (int k = 0; k < nz; k++) w[Tj[k]]++;		/* column counts */
    cs_cumsum(Cp, w, n);				/* column pointers */
    for (int k = 0; k < nz; k++)
    {
        int p;
        Ci[p = w[Tj[k]]++] = Ti[k];    /* A(i,j) is the pth entry in C */
        Cx[p] = Tx[k];
    }

    freeTemporaryW();
    
    return C;	    /* success; free w and return C */
}

/* add an entry to a triplet matrix; return 1 if ok, assertion failure otherwise */
CSPARSEFUNC int cs_entry(cs * const T, const int i, const int j, const real x)
{
    assert(cs_is_triplet(T));
    assert(i >= 0 && i < T->m && j >= 0 && j <= T->n); // cannot enlarge matrix
    assert(T->nz < T->nzmax); // cannot enlarge matrix
    assert(T->x);
    assertFinite(x);

    T->x[T->nz] = x;
    T->i[T->nz] = i;
    T->p[T->nz++] = j;
    return (1);
}



/* print a sparse matrix */
CSPARSEFUNC int cs_print(const cs * const A, int brief = 0)
{
    assert(A);
    int p, j, m, n, nzmax, nz, *Ap, *Ai;
    real *Ax;

    m = A->m; n = A->n; Ap = A->p; Ai = A->i; Ax = A->x;
    nzmax = A->nzmax; nz = A->nz;

    printf("CSparse %s\n",
#ifdef __CUDA_ARCH__
        "on CUDA"
#else
        "on CPU"
#endif
        );
    assert(m > 0 && n > 0);
    if (nz < 0)
    {
        printf("%d-by-%d, nzmax: %d nnz: %d\n", m, n, nzmax,
            Ap[n]);
        for (j = 0; j < n; j++)
        {
            printf("    col %d : locations %d to %d\n", j, Ap[j], Ap[j + 1] - 1);
            for (p = Ap[j]; p < Ap[j + 1]; p++)
            {
                assert(Ai[p] >= 0 && Ai[p] < m);
                printf("      %d : %g\n", Ai[p], Ax ? Ax[p] : 1);
                if (brief && p > 20) { printf("  ...\n"); return (1); }
            }
        }
    }
    else
    {
        printf("triplet: %d-by-%d, nzmax: %d nnz: %d\n", m, n, nzmax, nz);
        assert(nz <= nzmax);
        for (p = 0; p < nz; p++)
        {
            printf("    %d %d : %g\n", Ai[p], Ap[p], Ax ? Ax[p] : 1);
            assert(Ai[p] >= 0 && Ap[p] >= 0);
            if (brief && p > 20) { printf("  ...\n"); return (1); }
        }
    }
    return (1);
}


/* y = alpha A x + beta y */
CSPARSEFUNC int cs_mv(real *y, real alpha, const cs *A, const real *x, real beta) {
    assert(A && x && y);	    /* check inputs */
    assertFinite(beta); 
    assertFinite(alpha);

    int p, j, n, *Ap, *Ai;
    real *Ax;
    n = A->n; Ap = A->p; Ai = A->i; Ax = A->x;

    // the height of A is the height of y. Premultiply y with beta, then proceed as before, including the alpha factor when needed 
    // TODO (can we do better?)
    // Common special cases
    if (beta == 0)
        memset(y, 0, sizeof(real) * A->m);
    else
        for (int i = 0; i < A->m; i++) y[i] *= beta;

    if (alpha == 1)
        for (j = 0; j < n; j++) for (p = Ap[j]; p < Ap[j + 1]; p++) y[Ai[p]] += Ax[p] * x[j];
    else if (alpha != 0) // TODO instead of deciding this at runtime, let the developer choose the right function xD
        for (j = 0; j < n; j++) for (p = Ap[j]; p < Ap[j + 1]; p++) y[Ai[p]] += alpha * Ax[p] * x[j];
    // if alpha = 0, we are done

    return (1);
}
// ---

// for conjgrad/sparse leastsquares:

// infrastructure like CusparseSolver

struct vector {
    real* x;
    int n;


    CSPARSEFUNC static void print(real* x, int n) {
        for (int i = 0; i < n; i++)
            printf("%f ", x[i]);
        printf("\n");

    }
    CSPARSEFUNC void print() {
        print(x, n);
    }
};

CSPARSEFUNC vector vector_wrapper(real* x, int n) {
    vector v;
    v.n = n;
    v.x = x;
    return v;
}

CSPARSEFUNC vector vector_allocate(int n, MEMPOOL) {
    vector v;
    v.n = n;
    cs_malloc(v.x, sizeof(real) * nextEven(v.n));
    return v;
}

CSPARSEFUNC vector vector_copy(const vector& other, MEMPOOL) {
    vector v;
    v.n = other.n;
    cs_malloc(v.x, sizeof(real) * nextEven(v.n));
    memcpy(v.x, other.x, sizeof(real) * v.n);
    return v;
}

struct matrix {
    const cs* const mat; // in compressed column form (transpose does not work with triplets)

    __declspec(property(get = getRows)) int rows;
    CSPARSEFUNC int getRows() const {
        return mat->m;
    }
    __declspec(property(get = getCols)) int cols;
    CSPARSEFUNC int getCols() const {
        return mat->n;
    }


    CSPARSEFUNC matrix(const cs* const mat) : mat(mat) {
        assert(!cs_is_triplet(mat));
        assert(mat->m && mat->n);
    }

    CSPARSEFUNC void print() {
        cs_print(mat, 0);
    }
};


// result = <x, y>, aka x.y or x^T y (the dot-product of x and y)
CSPARSEFUNC real dot(const vector& x, const vector& y) {
    assert(y.n == x.n);
    real r = 0;
    for (int i = 0; i < x.n; i++) r += x.x[i] * y.x[i];
    return r;
}

// y = alpha * x + y
CSPARSEFUNC void axpy(vector& y, const real alpha, const vector& x) {
    assert(y.n == x.n);
    for (int i = 0; i < x.n; i++) y.x[i] += alpha * x.x[i];
}

// y = x + y
CSPARSEFUNC void axpy(vector& y, const vector& x) {
    axpy(y, 1, x);
}

// x *= alpha
CSPARSEFUNC void scal(vector& x, const real alpha) {
    for (int i = 0; i < x.n; i++) x.x[i] *= alpha;
}

// y = alpha A x + beta y
CSPARSEFUNC void mv(vector& y, const real alpha, const matrix& A, const vector& x, const real beta) {
    assert(A.mat->m && A.mat->n);
    assert(y.n == A.mat->m);
    assert(x.n == A.mat->n);
    cs_mv(y.x, alpha, A.mat, x.x, beta);
}

// y = A x
CSPARSEFUNC void mv(vector& y, const matrix& A, const vector& x) {
    mv(y, 1, A, x, 0);
}

CSPARSEFUNC matrix transpose(const matrix& A, MEMPOOL) {
    return matrix(cs_transpose(A.mat, MEMPOOLPARAM));
}

#define memoryPush() const auto old_memoryPool = memoryPool; const auto old_memory_size = memory_size; //savepoint: anything allocated after this can be freed again
#define memoryPop() {memoryPool = old_memoryPool; memory_size = old_memory_size;} // free anything allocated since memory push

// core algorithm, adapted from CusparseSolver, originally copied from wikipedia
/* required operations:
- new vector of given size
- copy/assign vector
- mv_T, mv (matrix (transpose) times vector) -- because I did not come up with a transposing-multiply operation, I just compute AT once instead of using mv_T
- scal (scaling)
- axpy // y = alpha * x + y
*/
//function [x] = conjgrad_normal(A,b,x)
/*The conjugate gradient method can be applied to an arbitrary n-by-m matrix by applying it to normal equations ATA and right-hand side vector ATb, since ATA is a symmetric positive-semidefinite matrix for any A. The result is conjugate gradient on the normal equations (CGNR).
ATAx = ATb
As an iterative method, it is not necessary to form ATA explicitly in memory but only to perform the matrix-vector and transpose matrix-vector multiplications.

x is an n-vector in this case still
*/
CSPARSEFUNC void conjgrad_normal(
    const matrix& A,
    const vector& b,
    vector& x,
    MEMPOOL) {
    memoryPush(); //savepoint: anything allocated after this can be freed again

    int m = A.rows, n = A.cols;

    matrix AT = transpose(A, MEMPOOLPARAM); // TODO implement an mv that does transposing in-place

    vector t = vector_allocate(m, MEMPOOLPARAM);

    vector r = vector_allocate(n, MEMPOOLPARAM); mv(r, AT, b); mv(t, A, x); mv(r, -1, AT, t, 1);//r=A^T*b; t = A*x; r = -A^T*t + r;//r=A^T*b-A^T*A*x;

    vector p = vector_copy(r, MEMPOOLPARAM);//p=r;

    real rsold = dot(r, r);//rsold=r'*r;

    vector Ap = vector_allocate(A.cols, MEMPOOLPARAM);

    for (int i = 1; i <= b.n; i++) {
        mv(t, A, p); mv(Ap, AT, t);//t = A*p;Ap=A^T*t;//Ap=A^T*A*p;
        real alpha = rsold / (dot(p, Ap));//alpha=rsold/(p'*Ap);
        axpy(x, alpha, p);//x = alpha p + x;//x=x+alpha*p;
        axpy(r, -alpha, Ap);//r = -alpha*Ap + r;//r=r-alpha*Ap;
        real rsnew = dot(r, r);//rsnew=r'*r;
        if (sqrt(rsnew) < 1e-5) break; // error tolerance, might also limit amount of iterations or check change in rsnew to rsold...
        real beta = (rsnew / rsold);
        scal(p, beta); axpy(p, r);//p*=(rsnew/rsold); p = r + p;//p=r+(rsnew/rsold)*p;
        rsold = rsnew;//rsold=rsnew;
    }

    memoryPop(); // free anything allocated since memory push
}

// solving least-squares problems

/* x=A\b 

Uses memory pool to allocate transposed copy of A and four vectors with size m or n
*/
CSPARSEFUNC int cs_cg(const cs *A, real *b, real *x, MEMPOOL) {
    auto xv = vector_wrapper(x, A->n);
    conjgrad_normal(matrix(A), vector_wrapper(b, A->m), xv, MEMPOOLPARAM);
    return 1;
}
