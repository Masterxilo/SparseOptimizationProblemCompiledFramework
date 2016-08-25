/*
To make this debuggable, be sure to adjust then environment:
NSIGHT_CUDA_DEBUGGER=1
SetEnvironment["NSIGHT_CUDA_DEBUGGER" -> "1"]
*/

// WSTP interfacing
#define WL_WSTP_MAIN // undefine to use main below to debug without mathematica
#define WL_ALLOC_CONSOLE
#include "framework.h"

#include "wstpExternC.cu"

#include "csparseminimal.cpp"

#define copy mallocmemcpy


FUNCTION(int, lengthzGet, (), "lengthz"){ return lengthz; }
FUNCTION(int, lengthfzGet, (), "lengthfz") { return lengthfz; }

// logging/debugging

GLOBAL(
    int,
    dprintEnabled,
    true,
    "if true, dprintf writes to stdout, otherwise dprintf does nothing"
    "It would be more efficient to compile with dprintf defined to nothing of course"
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

/* size_t n not const because the implementation modifies it
changes not visible outside anyways:
the last const spec is always an implementation detail, but can indicate conceptual thinking */
FUNCTION(
    void,
    printv,
    (_In_reads_(n) const real* v, size_t n),
    "dprints a vector of doubles, space separated and newline terminated"
    ) {
    while (n--) dprintf("%f ", *v++); dprintf("\n");
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
    "prints the matrix J, (i.e. dF/dy (x)). Cannot be used externally."
    ){
    if (dprintEnabled) cs_print(J);
}


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
    while (len--) {
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
    "Note that not necessarily all of target is updated"

    ) {
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
    "target = source[[sourceIndices]]. Note that all of target is updated"
    ) {
    assertEachInRange(sourceIndices, sourceIndicesAndTargetLength, 0, sourceLength - 1);

    DO(i, sourceIndicesAndTargetLength)
        target[i] = source[sourceIndices[i]];
}

// SparseOptimizationProblem library

// --- Memory pool passed to the csparse library ---

// this is ideally some __shared__ memory in CUDA: C-style "stack" memory is first register based but then spills to main memory
// (is shared memory also used for the registers? Just another way to access the register file?)
// this memory does not need to be manually freed

// DEBUG TODO moved memory to global space for debugging -- move to __shared__ again.
// down the stack, no two functions should be calling SOMEMEM at the same time!

//__managed__ char memory[40000/*"Maximum Shared Memory Per Block" -> 49152*/ * 1000]; // TODO could allocate 8 byte sized type, should be aligned then (?)
//__managed__ bool claimedMemory = false;

#define SOMEMEM() \
    char memory[40000/*"Maximum Shared Memory Per Block" -> 49152*/ ];\
    char* mem = (char*)(((unsigned long long)memory+7) & (~ 0x7ull)); /* align on 8 byte boundary */\
    assert(aligned(mem, 8) && after(mem, memory));\
    int memsz = sizeof(memory)-8;/*be safe*/ \
    //assert(!claimedMemory); claimedMemory = true;

#define FREESOMEMEM() //claimedMemory = false;

#define SOMEMEMP mem, memsz

// --- ---

FUNCTION(void, writeJFx, (cs* const J, const size_t i, const size_t j, const real x),
    "set J(i, j) = x"
    ) {
    assert(J);
    assert(cs_is_triplet(J));
    assert(i < J->m && j < J->n);
    assert(J->nz + 1 <= J->nzmax);
    assertFinite(x);

    cs_entry(J, i, j, x);
}

FUNCTION(void, writeFx, (const size_t i, const real val), "F(x)_i = val") {
    assert(i < lengthFx);
    assert(minusFx);
    assertFinite(val);

    minusFx[i] = -val;
}

GLOBALDYNAMICARRAY(
    real, x, lengthx,
    "stores the current data vector 'x' which is updated to reduce the energy ||F(x)||^2"
    );

// Required for including definitions of f and df:
#include "$CFormDefines.cpp"
#define x(i) input[i]

// TODO generate them like that (FUNCTION), add parameters of length for in and out that are asserted
// but since its and output parameter it still cannot be called from WL --> 
//  make special declarations for such variables (microsoft has a standard annotation)

FUNCTION(void, f, (
    _In_reads_(lengthz) const real* const input, // TODO support these kinds of constant-sized vectors in the WSTP wrapper code
    _Out_writes_(lengthfz) real* const out), "the local energy vector computing function") {
#include "f.cpp" // generated
}
FUNCTION(void, df, (int const i,
    _In_reads_(lengthz) real const * const input,
    _Out_writes_(lengthfz) real * const out
    ), "the derivatives along the i-th variable of the local energy vector computing function") {
#include "df.cpp" // generated
}
#undef x

GLOBALDYNAMICARRAY(
    real, minusFx, lengthFx,
    "-F(x)"
    );

GLOBALDYNAMICARRAY(
    real, h, lengthY,
    "h, the update to y, subset of x, the parameters currently optimized over"
    );

// Could be const on GPU side

GLOBAL(
    int, lengthP, 0,
    "amount of 'points' at which the function f is evaluated."
    "lengthP * lengthz is the length of xIndices, "
    "and sparseDerivativeZtoYIndices contains lengthP sequences of the form (k [k many] [k many]) "
    );

// Could be const on GPU side
// integer matrix of dimensions lengthz x lengthP, indexing into x to find the values to pass to f
__managed__ int* xIndices = 0;

// Could be const on GPU side
// Used to construct J, c.f. SOPJF
__managed__ int* sparseDerivativeZtoYIndices = 0;

// Could be const on GPU side
GLOBALDYNAMICARRAY_SHAREDLENGTH(
    int, yIndices, lengthY,
    "the indices into x that indicate where the y are"
    );


// -----------------------
/*
Given access to (somehow):

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

FUNCTION(void, readZ, (
    _Out_writes_all_(lengthz) real* z,
    const size_t rowz
    ), "compute and store Fx[[rowfz;;rowfz+lengthfz-1]] = f(z) and return the z required for that"){
    assert(divisible(rowz, lengthz));

    extract(z, x, lengthx, xIndices + rowz, lengthz); // z = x[[xIndices]]
}

FUNCTION(void, readZandSetFxRow, (
    _Out_writes_all_(lengthz) real* z,
    const size_t rowz, 
    const size_t rowfz
    ), "compute and store Fx[[rowfz;;rowfz+lengthfz-1]] = f(z) and return the z required for that"){
    assert(divisible(rowz, lengthz));
    assert(divisible(rowfz, lengthfz));

    readZ(z, rowz); // z = x[[xIndices]]

    real fz[lengthfz];
    f(z, fz); // fz = f(z)

    DO(i, lengthfz) writeFx(rowfz + i, fz[i]); // Fx[[rowfz;;rowfz+lengthfz-1]] = fz
}

FUNCTION(void, setFxRow, (
    const size_t rowz,
    const size_t rowfz
    ), "compute and store Fx[[rowfz;;rowfz+lengthfz-1]]"){
    real z[lengthz];
    readZandSetFxRow(z, rowz, rowfz);
}

FUNCTION(void, buildFx,(), "from the current x, computes F(x)" ){
    size_t rowz = 0;
    size_t rowfz = 0;

    FOR(size_t, i, 0, lengthP, (rowz += lengthz, rowfz += lengthfz, 1)) MAKE_CONST(rowz) MAKE_CONST(rowfz) {
        DBG_UNREFERENCED_LOCAL_VARIABLE(i);
        setFxRow(rowz, rowfz);
    }
}

FUNCTION(void, buildFxandJFx, (cs* const J, bool buildFx), 
    "from the current x, computes F(x) and JF(x)"
    "note that J is stored into the matrix pointed to"
    "this J must have the right size is stored somewhere, in CUDA idally in shared memory"
    ) {
    auto* currentSparseDerivativeZtoYIndices = sparseDerivativeZtoYIndices;
    size_t rowz = 0;
    size_t rowfz = 0;

    FOR(size_t, i, 0, lengthP, (rowz += lengthz, rowfz += lengthfz, 1)) MAKE_CONST(rowz) MAKE_CONST(rowfz) {
        DBG_UNREFERENCED_LOCAL_VARIABLE(i);
        real z[lengthz];
        if (buildFx)
            readZandSetFxRow(z, rowz, rowfz);
        else
            readZ(z, rowz);

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
            assert(yIndex < lengthY);

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
    (cs const * const J, MEMPOOL),
    "assumes x, -Fx and J have been built"
    "computes the adjustment vector h, which is the least-squares solution to the system"
    "Jh = -Fx"
    ) {
    assert(J && x && minusFx && h);
    assert(cs_is_compressed_col(J));

    dprintf("sparse leastSquares (cg) %d x %d... (this might take a while)\n",
        J->m, J->n);

    assert(lengthY > 0);

    // h must be initialized -- initial guess -- use 0
    memset(h, 0, sizeof(real) * lengthFx);

    cs_cg(J, minusFx, h, MEMPOOLPARAM);

    dprintf("h:\n"); printv(h, lengthY);

}

FUNCTION(
    real,
    norm2Fx,
    (), "Assuming F(x) is computed, returns ||F(x)||_2^2" 
    ) {
    assert(minusFx);
    real x = 0;
    DO(i, lengthFx) x += minusFx[i] * minusFx[i];
    return assertFinite(x);
}

FUNCTION(
    float,
    addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBefore,
    (),
    "scales h such that F(x0 + h) < F(x) in the 2-norm and updates x = x0 + h"
    "returns total energy delta achieved which should be negative but might not be when the iteration count is exceeded"
    ) {
    assert(yIndices);
    assert(x);

    // determine old norm
    const real norm2Fatx0 = norm2Fx();
    dprintf("||F[x0]||_2^2 = %f\n", norm2Fatx0);

    // add full h
    real lambda = 1.;
    dprintf("x = "); printv(x, lengthx);
    axpyWithReindexing(x, lengthx, lambda, h, yIndices, lengthY); // xv = x0 + h
    dprintf("x = x0 + h = "); printv(x, lengthx); 

    buildFx();
    real norm2Faty0 = norm2Fx();
    dprintf("||F[x0 + h]||_2^2 = %f\n", norm2Faty0);


    // Reduce step-size if chosen step does not lead to reduction by subtracting lambda * h
    size_t n = 0; // safety net, limit iterations
    while (norm2Faty0 > norm2Fatx0 && n++ < 20) {
        lambda /= 2.;
        axpyWithReindexing(x, lengthx, -lambda, h, yIndices, lengthY); // xv -= lambda * h // note the -!

        dprintf("x = "); printv(x, lengthx); 

        buildFx();
        norm2Faty0 = norm2Fx(); // reevaluate norm
        dprintf("reduced stepsize, lambda =  %f, ||F[y0]||_2^2 = %f\n", lambda, norm2Faty0);
    }
    dprintf("optimization finishes, total energy change: %f\n", norm2Faty0-norm2Fatx0);
    /*assert(norm2Faty0 - norm2Fatx0 <= 0.);*/
    return norm2Faty0 - norm2Fatx0;
}

// Interface

FUNCTION(
    void,
    getY,
    (
    _Out_writes_all_(lengthY) real* const outY,
    int lengthY
    ),
    "Extracts from x the elements that are y"
    "lengthY must match the length passed at initialization"
    "TODO make WSTP support having global variables specify the necessary array length, support non size_t lengths"
    )
{
    assert(lengthY == ::lengthY);
    extract(outY, ::x, ::lengthx, ::yIndices, lengthY);
}

CPU_FUNCTION(
    void,
    receiveOptimizationData,
    (
    _In_reads_(xLength) const real* const xI, const size_t xLength,
    _In_reads_(sparseDerivativeZtoYIndicesLength) const int* const sparseDerivativeZtoYIndicesI, const size_t sparseDerivativeZtoYIndicesLength,
    _In_reads_(xIndicesLength) const int* const xIndicesI, const size_t xIndicesLength,
    _In_reads_(yIndicesLength) const int* const yIndicesI, const size_t yIndicesLength
    ),
    "Receives x, sparseDerivativeZtoYIndices, xIndices and yIndices"
    "Appropriately sized vectors for receiving these data items is allocated in __managed__ memory, hence this is a CPU only function"
    ) {
    // compiler seems confused when both are called x
    ::x = copy(xI, xLength); // TODO modifiable Lvalue problem
    ::sparseDerivativeZtoYIndices = copy(sparseDerivativeZtoYIndicesI, sparseDerivativeZtoYIndicesLength);
    ::xIndices = copy(xIndicesI, xIndicesLength);
    ::yIndices = copy(yIndicesI, yIndicesLength);

    ::lengthP = xIndicesLength / lengthz;
    ::lengthY = yIndicesLength;
    ::lengthFx = lengthfz * lengthP;
    ::lengthx = xLength;
    ::minusFx = tmalloc<real>(lengthFx);

    ::h = tmalloc<real>(lengthY);
}

FUNCTION(
    void,
    buildFxAndJFxAndSolve,
    (bool buildFx),
    "using current data, builds JFx (and Fx) and solves the least squares problem"
    "optionally does not compute Fx, assuming it is current with the x data (true after every solve)"
    ""
    "Note that we must do the solving right here, because this function handles the memory needed by J"
    "the solution is then accessible in h for further processing (updating x at yIndices)"
    )
{
    // Build F and JF
    const size_t maxNNZ = (lengthfz*lengthz) * lengthP;

    SOMEMEM();
    cs* J = cs_spalloc(lengthFx, lengthY, maxNNZ, 1, SOMEMEMP);

    buildFxandJFx(J, buildFx);

    J = cs_triplet(J, SOMEMEMP); // "optimizes storage of J, after which it may no longer be modified"

    dprintf("-F(x):\n");
    printv(minusFx, lengthFx);
    dprintf("JF(x):\n");
    printJ(J);

    dprintf("solve:\n");
    solve(J, SOMEMEMP);

    FREESOMEMEM();
}

FUNCTION(
    void,
    buildFxAndJFxAndSolveRepeatedly,
    (const int iterations),
    "using current data, builds JFx (and Fx) and solves the least squares problem"
    "then does a gradient descent step"
    "reapeats this whole process as often as desired"
    )
{ // TODO we might want to do this externally
    dprintf("buildFxAndJFxAndSolveRepeatedly %d times\n", iterations);
    assert(iterations > 0);
    
    DO(i, iterations) {
        bool buildFx = i == 0; // Fx is always up-to date after first iteration

        buildFxAndJFxAndSolve(buildFx);
        const float delta = addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBefore();
        if (delta > -0.001) {
            dprintf("delta was only %f, stopping optimization\n", delta);
            return;
        }
    }
}


CPU_FUNCTION(
    void,
    receiveOptimizationDataBuildFxAndJFxAndSolveRepeatedly,
    (
    _In_reads_(xLength) const real* const xI, const size_t xLength,
    _In_reads_(sparseDerivativeZtoYIndicesLength) const int* const sparseDerivativeZtoYIndicesI, const size_t sparseDerivativeZtoYIndicesLength,
    _In_reads_(xIndicesLength) const int* const xIndicesI, const size_t xIndicesLength,
    _In_reads_(yIndicesLength) const int* const yIndicesI, const size_t yIndicesLength,
    const int iterations
    ),
    "Receives x, sparseDerivativeZtoYIndices, xIndices and yIndices"
    "Appropriately sized vectors for receiving these data items is allocated in __managed__ memory, hence this is a CPU only function"
    "currently also builds F(x), JF(x), but that could also be done on the GPU later"
    "it also calls solve, because J is built in local memory so it would be lost later"
    ) {
    receiveOptimizationData(xI, xLength, sparseDerivativeZtoYIndicesI, sparseDerivativeZtoYIndicesLength,
        xIndicesI, xIndicesLength, yIndicesI, yIndicesLength);

    buildFxAndJFxAndSolveRepeatedly(iterations);
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

    dprintf("xIndices:\n");
    p = xIndices;
    DO(i, lengthP) {
        DBG_UNREFERENCED_LOCAL_VARIABLE(i);
        printd(p, lengthz);
        p += lengthz;
    }
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
    "Creates a sparse matrix from a list of values and a list of pairs of (i, j) indices specifying where to put the corresponding values. "
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


FUNCTION(int, multiout, (_Inout_updates_(l) int* x, int l), "return more than one thing") {
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