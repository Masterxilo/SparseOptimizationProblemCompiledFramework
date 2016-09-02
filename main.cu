/*
This program solves least-squares problems with energies of the form

    \sum_{P \in Q} \sum_{p \in P} ||f(select_p(x))||_2^2

Q gives a partitioning of the domain. In the simplest case, there is only one partition.

The solution to this may or may not be close to the solution to

    \sum_{p \in \Cup Q} ||f(select_p(x))||_2^2

*/

/*
Compile with nvcc, after building the generated files with frameworkBuild.nb
(only needs to rerun when the external interface changes)

To make this CUDA debuggable, be sure to adjust then environment:

NSIGHT_CUDA_DEBUGGER=1

SetEnvironment["NSIGHT_CUDA_DEBUGGER" -> "1"]

Except for paul.h, standard/windows/cuda headers and generated files, this file is self-contained
*/

#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>
#include <stdio.h>
#include <memory.h> // just memset, but not malloc/free

#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>

#include <sal.h> // c.f. sal.txt

#include <cuda.h>
#include <cuda_runtime_api.h>
#include <cuda_runtime.h>
#include <device_functions.h>
#include <device_launch_parameters.h>
#pragma comment(lib,"cudart")

/*

Paul's CUDA/WSTP-Mathematica/C agnostic framework begins

FUNCTION declared functions can be called from Mathematica and CUDA whenever possible.

CPU_FUNCTION and CUDA_FUNCTION denote functions that use features only available on either platform (e.g. dues to CUDA API limitations or extensions)

Only primitive types can be passed back and forth automatically as of now.

*/


#define WL_WSTP_MAIN        // undefine to use main below to debug without mathematica 
#define WL_ALLOC_CONSOLE
#define WL_WSTP_PRE_MAIN
#include <paulwl.h> 
#include <paul.h>


// Most global data, can be queries via State
#define GLOBAL(type, name, defaultValue, usage) __managed__ type name = defaultValue
#define GLOBALDYNAMICARRAY(elementtype, name, sizevar, usage) __managed__ elementtype* name = 0; __managed__ int sizevar = 0; // lengths are int because that's what WSTP expects -- it doesn't seem to support larger arrays (at least not sent at once) -- should be size_t

#define GLOBALDYNAMICARRAY_SHAREDLENGTH(elementtype, name, sizevar, usage) __managed__ elementtype* name = 0; // TODO would be nice if it was detected that the variable already exists

// Read-only global data
#ifdef __CUDA_ARCH__
#define CONSTANTD const __constant__ 
#else
#define CONSTANTD const 
#endif

#ifdef __CUDA_ARCH__
#define CONSTANT(type, name, value, usage) const __constant__ type name = value
#else
#define CONSTANT(type, name, value, usage) const type name = value
#endif

// Most functions, will have a CUDA-kernel version __global__ void name args, one which outputs to an array from each thread and one that doesn't
#define FUNCTION(ret, name, args, usage) /** usage */ __host__ __device__ ret name args
#define MEMBERFUNCTION(ret, name, args, usage) /** usage */ __host__ __device__ ret name args

// FOR with const iterating variable
// for (int i = 0; i < 10; i++) i+=10; is legal but bad
// FOR(int,i,0,10) i+=10; is illegal

// create a block executed once with decl in place, prefix version of {decl; ...}
#define BLOCK_DECLARE(decl) if (bool a__ = true) for (decl;a__;a__=false)

#define FOR(type, var, start, maxExclusive, inc) for (type var##_ = start; var##_ < maxExclusive; var##_ += inc) BLOCK_DECLARE(const type var = var##_)

#define FOR1(type, var, start, maxExclusive) FOR(type, var, start, maxExclusive, 1)
#define FOR01(type, var, maxExclusive) FOR(type, var, 0, maxExclusive, 1)
#define FOR01S(var, maxExclusive) FOR(size_t, var, 0, maxExclusive, 1)

// Like Mathematica's Do, but starts at 0 and goes to maxExclusive-1
#define DO(var, maxExclusive) FOR01S(var, maxExclusive) MAKE_CONST(var)

#define MAKE_CONST(var) BLOCK_DECLARE(auto var##_ = var) BLOCK_DECLARE(const auto var = var##_)

// Special:

// Denotes a function that uses GPU features (threadIdx, __shared__)
//#define CUDA_FUNCTION(ret, name, args) __device__ ret name args // threadIdx is defined as 1 for CPU functions, __shared__ is ignored

// can call CUDAKERNEL_LAUNCH
#define CPU_FUNCTION(ret, name, args, usage) ret name args





// can theoretically work with any floating point type
// memory alignment issues in CUDA have to be readdressed should this be changed to double
// if this is 8 bytes instead of 4, many nextEven calls could be saved
typedef float real; 






// todo put elsewhere, use CONSTANT() to be able to read them from outside -- this is currently not possible because interplay with the // preprocessor is not implemented in the WSTP wrapper code
/**/
CONSTANTD int lengthz =
#include "lengthz.cpp" /* generated for each problem */
;

CONSTANTD int lengthfz =
#include "lengthfz.cpp" /* generated for each problem */
;


#include "$WSTPWrappingCDefinesCUDA.h" /* generated for interface, used for memory management */
#ifdef WL_WSTP_MAIN
#include "wstpExternC.cu"              /* generated for interface */
#endif

#include "$CFormDefines.cpp"  /* generated for problem, rarely changes */  // Required for including *working* definitions of f and df -- this defines what times(x,y) etc. mean
#define x(i) input[i] /* definitions of f/df use x(i) to refer to input[], c.f. RIFunctionCForm* */

// TODO support these (_In_reads_(lengthz)) kinds of constant-sized vectors in the WSTP wrapper code
// TODO the wstp wrapper code should not be able to produce a caller for this because it does not know the length of input
// should not accept just anything
FUNCTION(void, f, (
    _In_reads_(lengthz) const real* const input,
    _Out_writes_(lengthfz) real* const out
    ), "the local energy vector computing function") {
#include "f.cpp" /* generated for each problem, depends on $CFormDefines*/
}
FUNCTION(void, df, (int const i,
    _In_reads_(lengthz) real const * const input,
    _Out_writes_(lengthfz) real * const out
    ), "the derivatives along the i-th variable of the local energy vector computing function") {
#include "df.cpp" /* generated for each problem */
}
#undef x

/*
CSPARSE
A Concise Sparse Matrix Package in C

http://people.sc.fsu.edu/~jburkardt/c_src/csparse/csparse.html

CSparse Version 1.2.0 Copyright (c) Timothy A. Davis, 2006

reduced to only the things needed for sparse conjugate gradient method

by Paul Frischknecht, August 2016

and for running on CUDA, with a user-supplied memory-pool

modified & used without permission
*/


/* --- primary CSparse routines and data structures ------------------------- */
struct cs    /* matrix in compressed-column or triplet form . must be aligned on 8 bytes */
{
    int nzmax;	/* maximum number of entries allocated for triplet. Actual number of entries for compressed col. > 0 */
    int m;	    /* number of rows > 0 */

    int n;	    /* number of columns  > 0 */
    int nz;	    /* # of entries in triplet matrix, NZ_COMPRESSED_COLUMN_INDICATOR for compressed-col, >= 0 otherwise */

    // Note: this order preserves 8-byte pointer (64 bit) alignment, DO NOT CHANGE
    // all pointers are always valid
    int *p;	    /* column pointers (size n+1) or col indices (size nzmax) */

    int *i;	    /* row indices, size nzmax */

    real *x;	/* numerical values, size nzmax*/

};

FUNCTION(bool,cs_is_triplet,(const cs *A), "whether A is a triplet matrix") {
    assert(A);
    return A->nz >= 0;
}

const int NZ_COMPRESSED_COLUMN_INDICATOR = -1;

FUNCTION(bool,cs_is_compressed_col,(const cs *A),"whether A is a crompressed-column form matrix") {
    assert(A);
    assert(A->m >= 1 && A->n >= 1);
    return A->nz == NZ_COMPRESSED_COLUMN_INDICATOR;
}



// hacky arbitrary memory-management by passing
// reduces memory_size and increases memoryPool on use
#define MEMPOOL char*& memoryPool, int& memory_size // the function taking these modifies memoryPool to point to the remaining free memory
#define MEMPOOLPARAM memoryPool, memory_size 


FUNCTION(char* ,cs_malloc_,(char*& memoryPool, int& memory_size, size_t sz), 
"allocate new stuff. can only allocate multiples of 8 bytes to preserve alignment of pointers in cs. Use nextEven to round up when allocating 4 byte stuff (e.g. int)"){
    assert(memory_size >= sz);
    assert(aligned(memoryPool, 8));
    assert(divisible(sz, 8));
    auto out = memoryPool;
    memoryPool += sz;
    memory_size -= sz;
    return out;
}

#define cs_malloc(varname, sz) {(varname) = (decltype(varname))cs_malloc_(MEMPOOLPARAM, (sz));}

FUNCTION(void ,cs_free_,(char*& memoryPool, int& memory_size, size_t sz) ,"free the last allocated thing of given size"){
    assert(divisible(sz, 8));
    assert(aligned(memoryPool, 8));
    memoryPool -= sz;
    memory_size += sz;
}

#define cs_free(sz) {cs_free_(MEMPOOLPARAM, (sz));}


FUNCTION(int,cs_spalloc_size,(size_t m, size_t n, size_t nzmax, bool triplet),
"amount of bytes a sparse matrix with the given characteristics will occupy"){
    return sizeof(cs) + nextEven(triplet ? nzmax : n + 1) * sizeof(int) + nextEven(nzmax) *  (sizeof(int) + sizeof(real));
}


FUNCTION(cs *,cs_spalloc,(size_t m, size_t n, size_t nzmax, bool triplet, MEMPOOL),
    "allocates a sparse matrix using memory starting at memoryPool,"
    "uses exactly"
    "sizeof(cs) + cs_spalloc_size(m, n, nzmax, triplet) BYTES"
    "of the pool"
    )
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


FUNCTION(int, cs_cumsum, (_Inout_updates_all_(n + 1) int *p, _Inout_updates_all_(n) int *c, const int n),
    "p [0..n] = cumulative sum of c [0..n-1], and then copy p [0..n-1] into c "
    )
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

FUNCTION(int*,allocZeroedIntegers,(const int n, MEMPOOL),"Allocate n integers set to 0. Implements calloc(n, sizeof(int)). n must be even") {
    assert(divisible(n, 2));
    int* w;
    cs_malloc(w, n * sizeof(int));
    memset(w, 0, n*sizeof(int)); // w = (int*)cs_calloc(n, sizeof(int)); /* get workspace */
    return w;
}

// alloc/free a list of integers w, initialized to 0
#define allocTemporaryW(count) int wsz = nextEven((count)); int* w = allocZeroedIntegers(wsz, MEMPOOLPARAM); 
#define freeTemporaryW() cs_free(wsz * sizeof(int)); 


FUNCTION(cs *,cs_transpose,(const cs * const A, MEMPOOL),
    "C = A'"
    ""
    "memoryPool must be big enough to contain the following:"
    "cs_spalloc_size(n, m, Ap[n], 0) --location of output"
    "nextEven(m)*sizeof(int) --temporary")
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

FUNCTION(cs *,cs_triplet,(const cs * const T, MEMPOOL),
    "C = compressed-column form of a triplet matrix T"
    ""
    "memoryPool must be big enough to contain the following"
    "cs_spalloc_size(m, n, nz, 0) --location of output"
    "nextEven(n)* sizeof(int) --temporary")
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

FUNCTION(int,cs_entry,(cs * const T, const int i, const int j, const real x),
    "add an entry to a triplet matrix; return 1 if ok, assertion failure otherwise ")
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


FUNCTION(int,cs_print,(const cs * const A, int brief = 0),"print a sparse matrix")
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


FUNCTION(int,cs_mv,(real * y, real alpha, const cs *  A, const real * x, real beta),
   "y = alpha A x + beta y"
   "the memory for y and x cannot overlap"
   "TODO implement a version that can transpose A implicitly")
{
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


// logging/debugging

GLOBAL(
    int,
    dprintEnabled,
    true,
    "if true, dprintf writes to stdout, otherwise dprintf does nothing"
    "It would be more efficient to compile with dprintf defined to nothing of course"
    "Default: true"
    );

#ifdef __CUDA_ARCH__
#define dprintf(formatstr, ...) {if (dprintEnabled) printf("CUDA " formatstr, __VA_ARGS__);}
#else
#define dprintf(formatstr, ...) {if (dprintEnabled) printf(formatstr, __VA_ARGS__);}
#endif

FUNCTION(void,
    print,
    (_In_z_ const char* const x),
    "prints a string to stdout"){
    printf("print: %s\n", x);
}


FUNCTION(
    void,
    printd,
    (_In_reads_(n) const int* v, size_t n),
    "dprints a vector of integers, space separated and newline terminated"
    ) {
    while (n--) dprintf("%d ", *v++); dprintf("\n");
}

FUNCTION(
    void,
    printJ,
    (cs* J),
    "prints a sparse matrix"
    ){
    if (dprintEnabled) cs_print(J);
}


// for conjgrad/sparse leastsquares:

// infrastructure like CusparseSolver

/*
Implementation note:
size_t n is not const because the implementation modifies it

changes to n are not visible outside anyways:
-> the last const spec is always an implementation detail, not a promise to the caller, but can indicate conceptual thinking
*/
FUNCTION(
    void,
    printv,
    (_In_reads_(n) const real* v, size_t n),
    "dprints a vector of doubles, space separated and newline terminated"
    ) {
    while (n--) dprintf("%f ", *v++); dprintf("\n");
}

struct vector {
    real* x;
    int n;

    MEMBERFUNCTION(void,print,(),"print this vector") {
        printv(x, n);
    }
};

FUNCTION(void, assertFinite, (_In_reads_(n) const real* const x, const int n), "assert that each element in v is finite") {
    for (int i = 0; i < n; i++)
        assertFinite(x[i]);
}

FUNCTION(void,assertFinite,(const vector& const v),"assert that each element in v is finite") {
    assertFinite(v.x, v.n);
}

FUNCTION(vector,vector_wrapper,(real* x, int n),"create a vector object pointing to existing memory for convenient accessing") {
    vector v;
    v.n = n;
    v.x = x;
    assertFinite(v);
    return v;
}

FUNCTION(vector,vector_allocate,(int n, MEMPOOL),"Create a new vector. uninitialized: must be written before it is read!") {
    vector v;
    v.n = n;
    cs_malloc(v.x, sizeof(real) * nextEven(v.n));
    return v;
}

FUNCTION(vector,vector_copy,(const vector& other, MEMPOOL),"create a copy of other") {
    vector v;
    v.n = other.n;
    cs_malloc(v.x, sizeof(real) * nextEven(v.n));
    memcpy(v.x, other.x, sizeof(real) * v.n);
    assertFinite(v);
    return v;
}

struct matrix {
    const cs* const mat; // in compressed column form (transpose does not work with triplets)

    __declspec(property(get = getRows)) int rows;
    MEMBERFUNCTION(int,getRows,(),"m") const {
        return mat->m;
    }
    __declspec(property(get = getCols)) int cols;
    MEMBERFUNCTION(int, getCols, (), "n") const {
        return mat->n;
    }


    MEMBERFUNCTION(,matrix,(const cs* const mat),"construct a matrix wrapper") : mat(mat) {
        assert(!cs_is_triplet(mat));
        assert(mat->m && mat->n);
        assertFinite(mat->x, mat->nz);
    }

    MEMBERFUNCTION(void,print,() ,"print this matrix"){
        cs_print(mat, 0);
    }
};


FUNCTION(real,dot,(const vector& x, const vector& y), "result = <x, y>, aka x.y or x^T y (the dot-product of x and y)"){
    assert(y.n == x.n);
    real r = 0;
    for (int i = 0; i < x.n; i++) r += x.x[i] * y.x[i];
    return r;
}

FUNCTION(void,axpy,(vector& y, const real alpha, const vector& x),"y = alpha * x + y") {
    assert(y.n == x.n);
    for (int i = 0; i < x.n; i++) y.x[i] += alpha * x.x[i];
}

FUNCTION(void,axpy,(vector& y, const vector& x),"y = x + y") {
    axpy(y, 1, x);
}

FUNCTION(void,scal,(vector& x, const real alpha),"x *= alpha"){
    for (int i = 0; i < x.n; i++) x.x[i] *= alpha;
}

FUNCTION(void,mv,(vector& y, const real alpha, const matrix& A, const vector& x, const real beta),
"y = alpha A x + beta y"){
    assert(A.mat->m && A.mat->n);
    assert(y.n == A.mat->m);
    assert(x.n == A.mat->n);
    cs_mv(y.x, alpha, A.mat, x.x, beta);
}

FUNCTION(void,mv,(vector& y, const matrix& A, const vector& x), "y = A x"){
    mv(y, 1, A, x, 0);
}

FUNCTION(matrix,transpose,(const matrix& A, MEMPOOL),"A^T") {
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

x is used as the initial guess -- it may be 0 but must in any case contain valid numbers
*/
FUNCTION(void,conjgrad_normal,(
    const matrix& A,
    const vector& b,
    vector& x,
    MEMPOOL),
    "x = A\b"
    )
    {
    memoryPush(); //savepoint: anything allocated after this can be freed again

    int m = A.rows, n = A.cols;

    matrix AT = transpose(A, MEMPOOLPARAM); // TODO implement an mv that does transposing in-place

    vector t = vector_allocate(m, MEMPOOLPARAM);

    vector r = vector_allocate(n, MEMPOOLPARAM); mv(r, AT, b); mv(t, A, x); mv(r, -1, AT, t, 1);//r=A^T*b; t = A*x; r = -A^T*t + r;//r=A^T*b-A^T*A*x;

    vector p = vector_copy(r, MEMPOOLPARAM);//p=r;

    real rsold = dot(r, r);//rsold=r'*r;
    if (sqrt(rsold) < 1e-5) goto end; // low residual: solution found

    vector Ap = vector_allocate(A.cols, MEMPOOLPARAM);

    for (int i = 1; i <= b.n; i++) {
        mv(t, A, p); mv(Ap, AT, t);//t = A*p;Ap=A^T*t;//Ap=A^T*A*p;

        if (abs(dot(p, Ap)) < 1e-9) { printf("conjgrad_normal emergency exit\n"); break; }// avoid almost division by 0
        real alpha = rsold / (dot(p, Ap));//alpha=rsold/(p'*Ap);

        axpy(x, alpha, p);//x = alpha p + x;//x=x+alpha*p;
        axpy(r, -alpha, Ap);//r = -alpha*Ap + r;//r=r-alpha*Ap;
        real rsnew = dot(r, r);//rsnew=r'*r;
        if (sqrt(rsnew) < 1e-5) break; // error tolerance, might also limit amount of iterations or check change in rsnew to rsold...
        real beta = (rsnew / rsold);
        scal(p, beta); axpy(p, r);//p*=(rsnew/rsold); p = r + p;//p=r+(rsnew/rsold)*p;
        rsold = rsnew;//rsold=rsnew;
    }

end:
    memoryPop(); // free anything allocated since memory push
}

// solving least-squares problems
FUNCTION(int, cs_cg, (const cs * const A, _In_reads_(A->m) const real * const b, _Inout_updates_all_(A->n) real *x, MEMPOOL),
"x=A\b"
"current value of x is used as initial guess"
"Uses memory pool to allocate transposed copy of A and four vectors with size m or n")
{
    assert(A && b && x && memoryPool && memory_size > 0);

    auto xv = vector_wrapper(x, A->n);
    conjgrad_normal(matrix(A), vector_wrapper((real*)b, A->m), xv, MEMPOOLPARAM);

    return 1;
}

/*

CSPARSE library end

*/



#define copy mallocmemcpy

FUNCTION(int, lengthzGet, (), "lengthz"){ return lengthz; }
FUNCTION(int, lengthfzGet, (), "lengthfz") { return lengthfz; }


// pure functions, utilities

FUNCTION(
    void,
    assertEachInRange,
    (
    _In_reads_(len) const int* v, 
    size_t len, 
    const int min,
    const int max
    ),
    "computes the same as BoolEval[min <= v <= max]"
    ) {
    assert(v);
    while (len--) { // Note: len reduced once more, gets gigantic if len was already 0
        assert(min <= *v && *v <= max);
        v++;
    }
}

FUNCTION(
    void,

    axpyWithReindexing,

    (
    _Inout_updates_(targetLength) real* const targetBase,
    const size_t targetLength,
    real const a,

    _In_reads_(targetIndicesAndAddedValuesLength) const real* const addedValues,
    _In_reads_(targetIndicesAndAddedValuesLength) const int* const targetIndices,
    const size_t targetIndicesAndAddedValuesLength
    ),
    "targetBase[[targetIndices]] += a * addedValues. Repeated indices are not supported, so addedValues cannot be longer than the target."
    "Note that not necessarily all of target is updated (_Inout_updates_, not _Inout_updates_all_)"

    ) {
    assert(targetLength); // targetLength - 1 overflows otherwise
    assertFinite(a);
    assert(targetIndicesAndAddedValuesLength <= targetLength);
    dprintf("axpyWithReindexing %f %d %d\n", a, targetLength, targetIndicesAndAddedValuesLength);

    dprintf("target before:\n"); printv(targetBase, targetLength);
    dprintf("targetIndices:\n"); printd(targetIndices, targetIndicesAndAddedValuesLength);
    dprintf("addedValues:\n"); printv(addedValues, targetIndicesAndAddedValuesLength);
    
    assertEachInRange(targetIndices, targetIndicesAndAddedValuesLength, 0, targetLength - 1);

    DO(j, targetIndicesAndAddedValuesLength)
        assertFinite(targetBase[targetIndices[j]] += addedValues[j] * a);

    dprintf("target after:\n"); printv(targetBase, targetLength);
}

FUNCTION(void, extract, (
    _Out_writes_all_ (sourceIndicesAndTargetLength) real* const target,

    _In_reads_(sourceLength) const real* const source,
    const size_t sourceLength,

    _In_reads_(sourceIndicesAndTargetLength) const int* const sourceIndices,
    const size_t sourceIndicesAndTargetLength
    ),
    "target = source[[sourceIndices]]. Note that all of target is initialized (_Out_writes_all_)"
    ) {
    assertEachInRange(sourceIndices, sourceIndicesAndTargetLength, 0, sourceLength - 1);

    DO(i, sourceIndicesAndTargetLength)
        target[i] = source[sourceIndices[i]];
}

// SparseOptimizationProblem library

// --- Memory pool passed to the csparse library ---

// this is ideally some __shared__ memory in CUDA: In CUDA (I think) 
// C-style "stack" memory is first register based but then spills to main memory
// (is shared memory also used for the registers? Just another way to access the register file?)
// this memory does not need to be manually freed

// DEBUG TODO moved memory to global space for debugging -- move to __shared__ again.
// down the stack, no two functions should be calling SOMEMEM at the same time!

//__managed__ char memory[40000/*"Maximum Shared Memory Per Block" -> 49152*/ * 1000]; // TODO could allocate 8 byte sized type, should be aligned then (?)
//__managed__ bool claimedMemory = false; // makes sure that SOMEMEM is only called by one function on the stack

// "A default heap of eight megabytes is allocated if any program uses malloc() without explicitly specifying the heap size." -- want more 

void preWsMain() { // using a constructor to do this seems not to work
    int const mb = 100;
    dprintf("setting cuda malloc heap size to %d mb\n", mb);
    cudaDeviceSetLimit(cudaLimitMallocHeapSize, mb * 1000 * 1000); // basically the only memory we will use, so have some!
    CUDA_CHECK_ERRORS();
}

#define SOMEMEM() \
    const size_t memory_size = 4000  * 1000;\
    char* const memory = (char*)malloc(memory_size);/*use global memory afterall*/\
    char* mem = (char*)(((unsigned long long)memory+7) & (~ 0x7ull)); /* align on 8 byte boundary */\
    assert(aligned(mem, 8) && after(mem, memory));\
    int memsz = memory_size - 8;/*be safe*/ \
    assert(memsz>0);\
    bool claimedMemory = true;\
    dprintf("allocated %d bytes at %p using malloc\n", memory_size, memory);\
    assert(memory); /*attempting to access a null pointer just gives a kernel launch failure on GPU most of the time - at least when debugger cannot be attached */

#define FREESOMEMEM() {assert(claimedMemory); claimedMemory = false; free(memory); mem = 0;}


#define SOMEMEMP mem, memsz

// --- end of memory pool stuff ---


// one separate SOP (for one P in Q), shares only "x" with the global problem
// has custom y, p and values derived from that
// pointers are to __managed__ memory
// F() is another function for each partition P. It is defined as (f(s_p(x)))_{p in P}
struct SOPPartition {
    real* minusFx; size_t lengthFx; // "-F(x)"
    real* h; size_t lengthY; // "h, the update to y (subset of x, the parameters currently optimized over)"

    /*
    "amount of 'points' at which the function f is evaluated."
    "lengthP * lengthz is the length of xIndices, "
    "and sparseDerivativeZtoYIndices contains lengthP sequences of the form (k [k many z indices] [k many y indices]) "
    */
    size_t lengthP;

    // integer matrix of dimensions lengthz x lengthP, indexing into x to find the values to pass to f
    int* xIndices;

    // Used to construct J, c.f. SOPJF
    int* sparseDerivativeZtoYIndices; // serialized form of this ragged array

    /*
    "the indices into x that indicate where the y are"
    "needed to write out the final update h to the parameters"
    */
    int* yIndices; /* lengthY */
};



GLOBALDYNAMICARRAY(
    SOPPartition, partitionTable, partitions,
    "partitions of the SOPD, allocated on call to setPartitions");

FUNCTION(void, writeJFx, (cs* const J, const size_t i, const size_t j, const real x),
    "set J(i, j) = x"
    ) {
    assert(J);
    assert(cs_is_triplet(J));
    assert(i < J->m && j < J->n);
    assert(J->nz + 1 <= J->nzmax); // matrix should not become overful
    assertFinite(x);

    cs_entry(J, i, j, x);
}

FUNCTION(void, writeFx, (SOPPartition* const sop, const size_t i, const real val), "F(x)_i = val") {
    assert(i < sop->lengthFx);
    assert(sop->minusFx);
    assertFinite(val);

    sop->minusFx[i] = -val;
}

GLOBALDYNAMICARRAY(
    real, x, lengthx,
    "stores the current data vector 'x' which is updated to reduce the energy ||F(x)||^2"
    );



// -----------------------
/*
Given access to :

int lengthP
int lengthY
const int lengthz (compile-time constant)
const int lengthfz (compile-time constant)
f(fz_out, z)
df(i, fz_out, z)
real* x
int* xIndices (a list of indices into x, lengthfz * n many)
int* sparseDerivativeZtoYIndices (a list of n lists of integers of the structure {k   (deriveby - k integers from 0 to argcount(f)-1) (store at - k integers from 0 to y_length-1)

This creates the vector
Fx
and the sparse matrix
JFx

By calling

void writeFx(int i, real val)
void writeJFx(int i, int j, real val)

using only elementary C constructs
*/
// TODO move these functions to SOPPartition instead of passing the pointer all the time
FUNCTION(void, readZ, (
    SOPPartition* const sop,
    _Out_writes_all_(lengthz) real* z,
    const size_t rowz
    ), "z = x[[xIndices[[rowz;;rowz+lengthz-1]]]]"){
    assert(divisible(rowz, lengthz));

    extract(z, x, lengthx, sop->xIndices + rowz, lengthz); // z = x[[xIndices]]
}

FUNCTION(void, readZandSetFxRow, (
    SOPPartition* const sop,
    _Out_writes_all_(lengthz) real* z,
    const size_t rowz,
    const size_t rowfz
    ), "compute and store Fx[[rowfz;;rowfz+lengthfz-1]] = f(z) and return the z = x[[xIndices[[rowz;;rowz+lengthz-1]]]] required for that"){
    assert(divisible(rowz, lengthz));
    assert(divisible(rowfz, lengthfz));

    readZ(sop, z, rowz); // z = x[[xIndices]]

    real fz[lengthfz];
    f(z, fz); // fz = f(z)

    DO(i, lengthfz) writeFx(sop, rowfz + i, fz[i]); // Fx[[rowfz;;rowfz+lengthfz-1]] = fz
}

FUNCTION(void, setFxRow, (
    SOPPartition* const sop,
    const size_t rowz,
    const size_t rowfz
    ), "compute and store Fx[[rowfz;;rowfz+lengthfz-1]]"){
    real z[lengthz];
    readZandSetFxRow(sop, z, rowz, rowfz);
}

FUNCTION(void, buildFx, (SOPPartition* const sop), "from the current x, computes just F(x)"){
    size_t rowz = 0;
    size_t rowfz = 0;

    FOR(size_t, i, 0, sop->lengthP, (rowz += lengthz, rowfz += lengthfz, 1)) MAKE_CONST(rowz) MAKE_CONST(rowfz) {
        DBG_UNREFERENCED_LOCAL_VARIABLE(i);
        setFxRow(sop, rowz, rowfz);
    }
}

FUNCTION(void, buildFxandJFx, (SOPPartition* const sop, cs* const J, bool buildFx),
    "from the current x, computes F(x) [if buildFx == true] and JF(x)"
    "Note that J is stored into the matrix pointed to"
    "this J must by in triplet form and have allocated enough space to fill in the computed df"
    ) {
    assert(cs_is_triplet(J));
    auto* currentSparseDerivativeZtoYIndices = sop->sparseDerivativeZtoYIndices;
    size_t rowz = 0;
    size_t rowfz = 0;

    FOR(size_t, i, 0, sop->lengthP, (rowz += lengthz, rowfz += lengthfz, 1)) MAKE_CONST(rowz) MAKE_CONST(rowfz) {
        DBG_UNREFERENCED_LOCAL_VARIABLE(i);
        real z[lengthz];
        if (buildFx)
            readZandSetFxRow(sop, z, rowz, rowfz);
        else
            readZ(sop, z, rowz);

        // deserialize sparseDerivativeZtoYIndices, c.f. flattenSparseDerivativeZtoYIndices
        // convert back to two lists of integers of the same length (K)
        const int K = *currentSparseDerivativeZtoYIndices++;
        assert(K <= lengthz);
        const int* const zIndices = currentSparseDerivativeZtoYIndices; currentSparseDerivativeZtoYIndices += K;
        const int* const yIndices = currentSparseDerivativeZtoYIndices; currentSparseDerivativeZtoYIndices += K;

        // construct & insert localJ columnwise
        DO(k, K) {
            const int zIndex = zIndices[k];
            const int yIndex = yIndices[k];

            assert(zIndex < lengthz);
            assert(yIndex < sop->lengthY);

            real localJColumn[lengthfz];
            df(zIndex, z, localJColumn);

            // put in the right place (starting at rowfz, column yIndex)
            DO(j, lengthfz) {
                writeJFx(J, rowfz + j, yIndex, localJColumn[j]);
            }
        }
    }
}
// -----------------------

// Core algorithms

FUNCTION(void,
    solve,
    (SOPPartition* const sop, cs const * const J, MEMPOOL),
    "assumes x, -Fx and J have been built"
    "computes the adjustment vector h, which is the least-squares solution to the system"
    "Jh = -Fx"
    ) {
    assert(J && x && sop && sop->minusFx && sop->h);
    assert(cs_is_compressed_col(J));

    dprintf("sparse leastSquares (cg) %d x %d... (this might take a while)\n",
        J->m, J->n);

    assert(sop->lengthY > 0);

    // h must be initialized -- initial guess -- use 0
    memset(sop->h, 0, sizeof(real) * sop->lengthY); // not lengthFx! -- in page writing error -- use struct vector to keep vector always with its length (existing solutions?)

    cs_cg(J, sop->minusFx, sop->h, MEMPOOLPARAM);

    dprintf("h:\n"); printv(sop->h, sop->lengthY);
    assertFinite(sop->h, sop->lengthY);
}

FUNCTION(
    real,
    norm2Fx,
    (SOPPartition const * const sop), "Assuming F(x) is computed, returns ||F(x)||_2^2"
    ) {
    assert(sop->minusFx);
    real x = 0;
    DO(i, sop->lengthFx) x += sop->minusFx[i] * sop->minusFx[i];
    return assertFinite(x);
}

FUNCTION(
    float,
    addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBefore,
    (SOPPartition * const sop),
    "scales h such that F(x0 + h) < F(x) in the 2-norm and updates x = x0 + h"
    "returns total energy delta achieved which should be negative but might not be when the iteration count is exceeded"
    ) {
    assert(sop);
    assert(sop->yIndices);
    assert(sop->minusFx);
    assert(x);

    // determine old norm
    const real norm2Fatx0 = norm2Fx(sop);
    dprintf("||F[x0]||_2^2 = %f\n", norm2Fatx0);

    // add full h
    real lambda = 1.;
    dprintf("x = "); printv(x, lengthx);
    axpyWithReindexing(x, lengthx, lambda, sop->h, sop->yIndices, sop->lengthY); // xv = x0 + h
    dprintf("x = x0 + h = "); printv(x, lengthx); 

    buildFx(sop);
    real norm2Faty0 = norm2Fx(sop);
    dprintf("||F[x0 + h]||_2^2 = %f\n", norm2Faty0);


    // Reduce step-size if chosen step does not lead to reduction by subtracting lambda * h
    size_t n = 0; // safety net, limit iterations
    while (norm2Faty0 > norm2Fatx0 && n++ < 20) {
        lambda /= 2.;
        axpyWithReindexing(x, lengthx, -lambda, sop->h, sop->yIndices, sop->lengthY); // xv -= lambda * h // note the -!

        dprintf("x = "); printv(x, lengthx); 

        buildFx(sop); // rebuild Fx after this change to x
        norm2Faty0 = norm2Fx(sop); // reevaluate norm
        dprintf("reduced stepsize, lambda =  %f, ||F[y0]||_2^2 = %f\n", lambda, norm2Faty0);
    }
    dprintf("optimization finishes, total energy change: %f\n", norm2Faty0-norm2Fatx0);
    /*assert(norm2Faty0 - norm2Fatx0 <= 0.);*/ // might not be true if early out was used
    return norm2Faty0 - norm2Fatx0;
}

// Interface

FUNCTION(
    void,
    getY,
    (
    int partition,
    _Out_writes_all_(lengthY) real* const outY,
    int lengthY
    ),
    "Extracts from x the elements that are y"
    "lengthY must match the length passed at initialization"
    "TODO make WSTP support having global variables specify the necessary array length, support non size_t lengths"
    "then we wouldn't need to supply the redundant lengthY here"
    )
{
    assert(partition >= 0 && partition < partitions);
    const SOPPartition* const sop = &partitionTable[partition];
    assert(x && sop && sop->yIndices && lengthx && sop->lengthY);
    assert(sop->lengthY <= lengthx);
    assert(lengthY == sop->lengthY);
    extract(outY, ::x, ::lengthx, sop->yIndices, sop->lengthY);
}

// TODO size_t not properly supported because of WSTP receiving only Integer64
CPU_FUNCTION(
    void, setPartitions, (size_t newPartitionsCount), "set the amount of partitions") {

    // free old stuff first
    assert(partitions >= 0);
    DO(i, partitions) {
        SOPPartition* const sop = &partitionTable[i];

        memoryFree(sop->sparseDerivativeZtoYIndices);
        memoryFree(sop->xIndices);
        memoryFree(sop->yIndices);
        memoryFree(sop->minusFx);
        memoryFree(sop->h);
    }
    memoryFree(partitionTable);

    // allocate
    ::partitions = newPartitionsCount;
    partitionTable = tmalloczeroed<SOPPartition>(partitions); // pointers not yet initialized
}

CPU_FUNCTION(
    void,
    receiveSharedOptimizationData,
    (
    _In_reads_(xLength) const real* const xI, const size_t xLength
    ),
    "Receives x"
    ) {
    memoryFree(x);
    ::x = copy(xI, xLength);
    ::lengthx = xLength;
}

// macro for indexing into partitionTable, sop = partitionTable[partition]
#define extractSop(partition) assert(partition >= 0 && partition < partitions); SOPPartition* const sop = &partitionTable[partition];

CPU_FUNCTION(
    void,
    receiveOptimizationData,
    (
    const int partition,
    _In_reads_(sparseDerivativeZtoYIndicesLength) const int* const sparseDerivativeZtoYIndicesI, const size_t sparseDerivativeZtoYIndicesLength,
    _In_reads_(xIndicesLength) const int* const xIndicesI, const size_t xIndicesLength,
    _In_reads_(yIndicesLength) const int* const yIndicesI, const size_t yIndicesLength
    ),
    "Receives sparseDerivativeZtoYIndices, xIndices and yIndices"
    "Appropriately sized vectors for receiving these data items are newly allocated in __managed__ memory, hence this is a CPU only function"
    ) {
    extractSop(partition);

    sop->sparseDerivativeZtoYIndices = copy(sparseDerivativeZtoYIndicesI, sparseDerivativeZtoYIndicesLength);
    sop->xIndices = copy(xIndicesI, xIndicesLength);
    sop->yIndices = copy(yIndicesI, yIndicesLength);

    assert(lengthz > 0);
    assert(divisible(xIndicesLength, lengthz));
    assert(lengthfz > 0);

    sop->lengthP = xIndicesLength / lengthz;
    sop->lengthY = yIndicesLength;
    sop->lengthFx = lengthfz * sop->lengthP;

    sop->minusFx = tmalloc<real>(sop->lengthFx);

    sop->h = tmalloc<real>(sop->lengthY);
}

FUNCTION(
    void,
    buildFxAndJFxAndSolve,
    (SOPPartition * const sop, bool buildFx),
    "using current data, builds JFx (and Fx) and solves the least squares problem"
    "optionally does not compute Fx, assuming it is current with the x data (true after every solve)"
    ""
    "Note that we must do the solving right here, because this function handles the memory needed by J"
    "the solution is then accessible in h for further processing (updating x at yIndices)"
    ""
    "sop is passed here, not partition. Use buildFxAndJFxAndSolveRepeatedly as the external interface"
    )
{
    // Build F and JF
    const size_t maxNNZ = (lengthfz*lengthz) * sop->lengthP; // very pessimistic estimate/overestimation: assume every derivative figures for every P -- usually not all of them will be needed
    // ^^ e.g. in vsfs the 3 color channels are all not optimized over, neither doriginal

    // consider using dynamic allocation in SOMEMEM!

    SOMEMEM(); 
    dprintf("allocating sparse matrix for %d entries\n", maxNNZ);
    cs* J = cs_spalloc(sop->lengthFx, sop->lengthY, maxNNZ, 1, SOMEMEMP); // might run out of memory here

    dprintf("buildFxandJFx\n");
    buildFxandJFx(sop, J, buildFx);

    dprintf("used %d of %d allocated spaces in J\n", J->nz, J->nzmax);
    assert(J->nz > 0); // there must be at least one (nonzero) entry in the jacobian, otherwise we have taken the derivative only over variables no ocurring (or no variables at all!)

    J = cs_triplet(J, SOMEMEMP); // "optimizes storage of J, after which it may no longer be modified" 
    // TODO recycle memory

    // State
    dprintf("-F(x):\n");
    printv(sop->minusFx, sop->lengthFx);
    dprintf("JF(x):\n");
    printJ(J);

    // Solve
    dprintf("solve:\n");
    solve(sop, J, SOMEMEMP); // TODO allocates even more memory

    FREESOMEMEM();
}

FUNCTION(
    void,
    buildFxAndJFxAndSolveRepeatedly,
    (const int partition, const int iterations),
    "using current data, builds JFx (and Fx) and solves the least squares problem"
    "then does a gradient descent step"
    "reapeats this whole process as often as desired"
    )
{ 
    extractSop(partition);

    // TODO we might want to do this externally
    dprintf("\n=== buildFxAndJFxAndSolveRepeatedly %d times in partition %d  ===\n", iterations, partition);
    assert(iterations > 0); // TODO iterations should be size_t
    
    DO(i, iterations) {
        bool buildFx = i == 0; // Fx is always up-to date after first iteration

        buildFxAndJFxAndSolve(sop, buildFx);
        const float delta = addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBefore(sop);
        if (delta > -0.001) {
            dprintf("delta was only %f, stopping optimization\n", delta);
            return;
        }
    }
}

FUNCTION(
    void,
    buildFxAndJFxAndSolveRepeatedlyThreadIdPartition,
    (const int iterations),
    "buildFxAndJFxAndSolveRepeatedly on the partition given by linear_global_threadId."
    "does nothing when linear_global_threadId is >= partitions"
    ""
    "TODO this should be the block id, threads in the same block should cooperate in the same partition"
    )
{
    if (linear_global_threadId() >= partitions) {
        dprintf("\n--- thread id %d has nothing to do  - there are only %d partitions\n", linear_global_threadId(), partitions);
        return;
    }

    dprintf("\n=== Starting work on partition %d in the thread of the same id ===\n", linear_global_threadId());
    buildFxAndJFxAndSolveRepeatedly(linear_global_threadId(), iterations);
}

// Prototyping functions

FUNCTION(void,
    receiveAndPrintOptimizationData,
    (
    const int lengthz,
    const int lengthfz,

    _In_reads_(xLength) const real* const x, const size_t xLength,
    _In_reads_(sparseDerivativeZtoYIndicesLength) const int* const sparseDerivativeZtoYIndices, const size_t sparseDerivativeZtoYIndicesLength,
    _In_reads_(xIndicesLength) const int* const xIndices, const size_t xIndicesLength,
    _In_reads_(yIndicesLength) const int* const yIndices, const size_t yIndicesLength
    ),
    "Receives x, sparseDerivativeZtoYIndices, xIndices and yIndices, checks and prints them,"
    "emulating arbitrary lengthz, lengthfz"
    "Note: lengthz, lengthfz are fixed at compile-time for other functions"
    "This is a prototyping function that does not allocate or copy anything"
    "use for testing"
    ) {

    const int lengthP = xIndicesLength / lengthz;
    const int lengthY = yIndicesLength;
    const int lengthFx = lengthfz * lengthP;
    const int maxNNZ = (lengthfz*lengthz) * lengthP; // could go down from lengthz to maximum k in sparseDerivativeZtoYIndices
     // or just the actual sum of all such k

    dprintf("lengthz: %d\n", lengthz);
    dprintf("lengthfz: %d\n", lengthfz);
    dprintf("lengthP: %d\n", lengthP);
    dprintf("lengthY: %d\n", lengthY);
    dprintf("lengthFx: %d\n", lengthFx);
    dprintf("maxNNZ: %d\n", maxNNZ);

    assert(lengthz > 0);
    assert(lengthfz > 0);
    assert(lengthY > 0);

    dprintf("x:\n");
    printv(x, xLength);

    dprintf("sparseDerivativeZtoYIndices:\n");
    const int* p = sparseDerivativeZtoYIndices;
    DO(i, lengthP) {
        DBG_UNREFERENCED_LOCAL_VARIABLE(i);
        int k = *p++; 
        assert(k <= lengthz);
        dprintf("---\n");
        printd(p, k); p += k;
        dprintf("-->\n");
        printd(p, k); p += k;
        dprintf("---\n");
    }
    assert(p == sparseDerivativeZtoYIndices + sparseDerivativeZtoYIndicesLength);

    dprintf("xIndices:\n");
    p = xIndices;
    DO(i, lengthP) {
        DBG_UNREFERENCED_LOCAL_VARIABLE(i);
        printd(p, lengthz);
        p += lengthz;
    }
    assert(p == xIndices + xIndicesLength);
    assertEachInRange(xIndices, xIndicesLength, 0, xLength - 1);

    dprintf("yIndices:\n");
    printd(yIndices, yIndicesLength);
    assertEachInRange(yIndices, yIndicesLength, 0, xLength - 1);
}



FUNCTION(
    void,
    makeAndPrintSparseMatrix,
    (
    const size_t m,
    const size_t n,
    _In_reads_(xlen) real* x,
    size_t xlen,
    _In_reads_(ijlen) int* ij,
    const size_t ijlen
    ),
    "Creates a sparse matrix from a list of values and a list of pairs of (i, j) indices specifying where to put the corresponding values (triplet form)"
    "Note: This is a prototyping function without any further purpose"
    ) {
    assert(2 * xlen == ijlen);
    assert(xlen <= m*n); // don't allow repeated entries

    SOMEMEM();
    cs* const A = cs_spalloc(m, n, xlen, 1, SOMEMEMP);

    while (xlen--) {
        int i = *ij++;
        int j = *ij++;
        cs_entry(A, i, j, *x++);
    }

    cs_print(A);

    printf("compress and print again:\n");
    const cs* const B = cs_triplet(A, SOMEMEMP);
    cs_print(B);
    printf("done--\n");


    FREESOMEMEM();
}








// Misc


FUNCTION(void, testMain, (), "collection of some tests") {
    dprintf("-- sparse optimize solver --\n");
    dprintf("Compiled with:\n");
    dprintf("lengthz: %d\n", lengthz);
    dprintf("lengthfz: %d\n", lengthfz);

    dprintf("POST begins:\n");
    real x[] = {1, 2};
    printv(x, 2);
    real y[] = {1};
    printv(y, 1);

    int to[] = {1};
    axpyWithReindexing(x, 2, 1., y, to, 1); // expect 1.000000 3.000000
    printv(x, 2); 

    real z[] = {0, 0};
    int from[] = {1, 0};
    extract(z, x, 2, from, 2); // expect 3.000000 1.000000
    printv(z, 2);

    // expect i: 0-9
    FOR(int,i,0,10,1)
        dprintf("i: %d\n", i);
}



GLOBAL(int, xx, 0, "xx");
GLOBAL(real, a, 0, "a");
GLOBAL(real, b, 0, "b");
GLOBAL(real, yy, 0, "yy");

FUNCTION(void, xx43, (), "sets xx to 43") {
    xx = 43;
}

FUNCTION(int, get42, (), "returns the answer to the universe life and everything") {
    return 42;
}

FUNCTION(int, add, (int x, int y), "x + y") {
    return x + y;
}

FUNCTION(real, addf, (real x, real y), "x + y with floats") {
    return x + y;
}


FUNCTION(int, multiout, (_Inout_updates_(l) int* x, int l), "returns more than one thing: when called via WSTP this will return an Association with all results") {
    *x = 0;
    return 1;
}
#ifndef WL_WSTP_MAIN 
__global__ void mainc() {

    int cij[] = {0, 0};
    int xlen = 1;
    real xc[] = {0.1};
    real* x = xc;
    int m = 1, n = 1;
    int* ij = cij;

    SOMEMEM();
    cs* A = cs_spalloc(m, n, xlen, 1, SOMEMEMP);

    while (xlen--) {
        int i = *ij++;
        int j = *ij++;
        cs_entry(A, i, j, *x++);
    }

    cs_print(A);

    printf("compress and print again:\n");
    A = cs_triplet(A, SOMEMEMP);
    cs_print(A);


    FREESOMEMEM();
    return;
}

int main() {
    //mainc<<<1,1>>>();
    //cudaDeviceSynchronize();
    auto e = 74; printf("cudaGetLastError %d %s %s\n", e, cudaGetErrorName((cudaError_t)e), cudaGetErrorString((cudaError_t)e));
    return;
}
#endif