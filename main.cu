/*
This program solves least-squares problems with energies of the form

    \sum_{P \in Q} \sum_{p \in P} ||f(select_p(x))||_2^2

Q gives a partitioning of the domain. In the simplest case, there is only one partition.

The solution to this may or may not be close to the solution to

    \sum_{p \in \Cup Q} ||f(select_p(x))||_2^2

*/

/*
SOPCompiled WL-library, c++ side.

Note: superceded by the SOPCompiled c++ interface/implementation.
TODO use that from here.

Compile with nvcc, after building the generated files with frameworkBuild.nb
(only needs to rerun when the external interface changes)

To make this CUDA debuggable, be sure to adjust then environment:

NSIGHT_CUDA_DEBUGGER=1

SetEnvironment["NSIGHT_CUDA_DEBUGGER" -> "1"]

Except for paul.h, standard/windows/cuda headers and generated files, this file is self-contained.
Generated required files:
    $CFormDefines
    f,df.cpp
    length(f)z.cpp
The Wolfram WSTP interface (WSTPMain.c, wstpExternC.cu, WSTPTemplateFile.tm) are optional.

TODO currently nvcc compilation seems to fail when df is present in the template file/wstp interface (linking error undefined reference to _Z*...df...). Just remove it from there.
The SOPCompiled interface only uses a handful of functions from here anyways (receive* and solve* basically)
*/

/*

Paul's CUDA/WSTP-Mathematica/C agnostic framework begins

FUNCTION declared functions can be called from Mathematica and CUDA whenever possible.

CPU_FUNCTION and CUDA_FUNCTION denote functions that use features only available on either platform (e.g. dues to CUDA API limitations or extensions)

Only primitive types can be passed back and forth automatically as of now.

*/

#include <paul.h>

#ifdef USE_WOLFRAM_LANGUAGE_INTERFACE

#define WL_WSTP_MAIN        // undefine to use main below to debug without mathematica 
#define WL_ALLOC_CONSOLE
#define WL_WSTP_PRE_MAIN
#include <paulwl.h> 

#endif












// todo put elsewhere, use CONSTANT() to be able to read them from outside -- this is currently not possible because interplay with the // preprocessor is not implemented in the WSTP wrapper code
/**/
CONSTANTD int lengthz =
#include "lengthz.cpp" /* generated for each problem */
;

CONSTANTD int lengthfz =
#include "lengthfz.cpp" /* generated for each problem */
;

#include "$WSTPWrappingCDefinesCUDA.h" /* generated for interface, used also for memory management & CUDA_CHECK_ERRORS*/

#ifdef USE_WOLFRAM_LANGUAGE_INTERFACE

#ifdef WL_WSTP_MAIN
#ifdef __CUDACC__
#include "wstpExternC.cu"              /* generated for interface */
#else
#include "wstpExternC.c"
#endif
#endif

#endif

#include "$CFormDefines.cpp"  /* generated for problem, rarely changes */  // Required for including *working* definitions of f and df -- this defines what times(x,y) etc. mean
#define x(i) input[i] /* definitions of f/df use x(i) to refer to input[], c.f. RIFunctionCForm* */

// TODO support these (_In_reads_(lengthz)) kinds of constant-sized vectors in the WSTP wrapper code
// TODO the wstp wrapper code should not be able to produce a caller for this because it does not know the length of input
// should not accept just anything
FUNCTION(void, f, (
    _In_reads_(lengthz) const float* const input,
    _Out_writes_all_(lengthfz) 
    float* const out
    ), "the local energy fvector computing function") {
#include "f.cpp" /* generated for each problem, depends on $CFormDefines*/
}

FUNCTION(void, df, (
    _In_range_(0, lengthz - 1) unsigned int const i,
    _In_reads_(lengthz) float const * const input,
    _Out_writes_all_(lengthfz)   
    float * const out
    ), "the derivatives along the i-th variable of the local energy fvector computing function") {
#include "df.cpp" /* generated for each problem, depends on $CFormDefines */
}
#undef x











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
    printJ,
    (csparse* J),
    "prints a sparse matrix"
    ){
    if (dprintEnabled) cs_print(J);
}







#define copy mallocmemcpy

FUNCTION(int, lengthzGet, (), "lengthz"){ return lengthz; }
FUNCTION(int, lengthfzGet, (), "lengthfz") { return lengthfz; }



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
	runTests();
#if __CUDACC__
    int const mb = 400;
    printf("setting cuda malloc heap size to %d mb\n", mb);
    cudaDeviceSetLimit(cudaLimitMallocHeapSize, mb * 1000 * 1000); // basically the only memory we will use, so have some!
    CUDA_CHECK_ERRORS();
#endif
}
// TODO easily exceeded with lots of partitions on big scenes - small partitions don't need that much memory

// --- end of memory pool stuff ---


// one separate SOP (for one P in Q), shares only "x" with the global problem
// has custom y, p and values derived from that
// pointers are to __managed__ memory
// F() is another function for each partition P. It is defined as (f(s_p(x)))_{p in P}
struct SOPPartition {
    float* minusFx; size_t lengthFx; // "-F(x)"
    float* h; size_t lengthY; // "h, the update to y (subset of x, the parameters currently optimized over)"

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

FUNCTION(void, writeJFx, (csparse* const J, const size_t i, const size_t j, const float x),
    "set J(i, j) = x"
    ) {
    assert(J);
    assert(cs_is_triplet(J));
    assert(i < J->m && j < J->n);
    assert(J->nz + 1 <= J->nzmax); // matrix should not become overful
    assertFinite(x);

    cs_entry(J, i, j, x);
}

FUNCTION(void, writeFx, (SOPPartition* const sop, const size_t i, const float val), "F(x)_i = val") {
    assert(i < sop->lengthFx);
    assert(sop->minusFx);
    assertFinite(val);

    sop->minusFx[i] = -val;
}

GLOBALDYNAMICARRAY(
    float, x, lengthx,
    "stores the current data fvector 'x' which is updated to reduce the energy ||F(x)||^2"
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
float* x
int* xIndices (a list of indices into x, lengthfz * n many)
int* sparseDerivativeZtoYIndices (a list of n lists of integers of the structure {k   (deriveby - k integers from 0 to argcount(f)-1) (store at - k integers from 0 to y_length-1)

This creates the fvector
Fx
and the sparse matrix
JFx

By calling

void writeFx(int i, float val)
void writeJFx(int i, int j, float val)

using only elementary C constructs
*/
// TODO move these functions to SOPPartition instead of passing the pointer all the time
FUNCTION(void, readZ, (
    SOPPartition* const sop,
    _Out_writes_all_(lengthz) float* z,
    const size_t rowz
    ), "z = x[[xIndices[[rowz;;rowz+lengthz-1]]]]"){
    assert(divisible(rowz, lengthz));

    extract_by_indices(z, x, lengthx, sop->xIndices + rowz, lengthz); // z = x[[xIndices]]
}

FUNCTION(void, readZandSetFxRow, (
    SOPPartition* const sop,
    _Out_writes_all_(lengthz) float* z,
    const size_t rowz,
    const size_t rowfz
    ), "compute and store Fx[[rowfz;;rowfz+lengthfz-1]] = f(z) and return the z = x[[xIndices[[rowz;;rowz+lengthz-1]]]] required for that"){
    assert(divisible(rowz, lengthz));
    assert(divisible(rowfz, lengthfz));

    readZ(sop, z, rowz); // z = x[[xIndices]]

    float fz[lengthfz];
    f(z, fz); // fz = f(z)

    DO(i, lengthfz) writeFx(sop, rowfz + i, fz[i]); // Fx[[rowfz;;rowfz+lengthfz-1]] = fz
}

FUNCTION(void, setFxRow, (
    SOPPartition* const sop,
    const size_t rowz,
    const size_t rowfz
    ), "compute and store Fx[[rowfz;;rowfz+lengthfz-1]]"){
    float z[lengthz];
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

FUNCTION(void, buildFxandJFx, (SOPPartition* const sop, csparse* const J, bool buildFx),
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
        float z[lengthz];
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

            float localJColumn[lengthfz];
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
    (SOPPartition* const sop, csparse const * const J, _In_ AllocationAligned8State mem),
    "assumes x, -Fx and J have been built"
    "computes the adjustment fvector h, which is the least-squares solution to the system"
    "Jh = -Fx"
    ""
    "Allocates temporaries in mem"
    ) {
    assert(J && x && sop && sop->minusFx && sop->h);
    assert(cs_is_compressed_col(J));

    printf("sparse leastSquares (cg) %d x %d... (this might take a while)\n",
        J->m, J->n);

    assert(sop->lengthY > 0);

    // h must be initialized -- initial guess -- use 0
    memset(sop->h, 0, sizeof(float) * sop->lengthY); // not lengthFx! -- in page writing error -- use struct fvector to keep fvector always with its length (existing solutions?)

    cs_cg(J, sop->minusFx, sop->h, mem);

    dprintf("h:\n"); printv(sop->h, sop->lengthY);
    assertFinite(sop->h, (unsigned int)sop->lengthY);
}

FUNCTION(
    float,
    norm2Fx,
    (SOPPartition const * const sop), "Assuming F(x) is computed, returns ||F(x)||_2^2"
    ) {
    assert(sop->minusFx);
    float x = 0;
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
    const float norm2Fatx0 = norm2Fx(sop);
    dprintf("||F[x0]||_2^2 = %f\n", norm2Fatx0);

    // add full h
    float lambda = 1.;
    dprintf("x = "); printv(x, lengthx);
    axpyWithReindexing(x, lengthx, lambda, sop->h, (unsigned int*)sop->yIndices, sop->lengthY); // xv = x0 + h
    dprintf("x = x0 + h = "); printv(x, lengthx); 

    buildFx(sop);
    float norm2Faty0 = norm2Fx(sop);
    dprintf("||F[x0 + h]||_2^2 = %f\n", norm2Faty0);


    // Reduce step-size if chosen step does not lead to reduction by subtracting lambda * h
    size_t n = 0; // safety net, limit iterations
    while (norm2Faty0 > norm2Fatx0 && n++ < 20) {
        lambda /= 2.;
        axpyWithReindexing(x, lengthx, -lambda, sop->h, (unsigned int*)sop->yIndices, sop->lengthY); // xv -= lambda * h // note the -!

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
    _Out_writes_all_(lengthY) float* const outY,
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
	extract_by_indices(outY, ::x
		, (int)::lengthx, (int*)sop->yIndices, (int)sop->lengthY // TODO should be unsigned
		);
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
    _In_reads_(xLength) const float* const xI, const size_t xLength
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

    sop->minusFx = tmalloc<float>(sop->lengthFx);

    sop->h = tmalloc<float>(sop->lengthY);
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

	aa8_malloc_raii mem(8 * 1000 * 1000);
    dprintf("allocating sparse matrix for %d entries\n", maxNNZ);
    csparse* J = cs_spalloc(sop->lengthFx, sop->lengthY, maxNNZ, 1, mem.aa8_state); // might run out of memory here

    dprintf("buildFxandJFx\n");
    buildFxandJFx(sop, J, buildFx);

    dprintf("used %d of %d allocated spaces in J\n", J->nz, J->nzmax);
    assert(J->nz > 0); // there must be at least one (nonzero) entry in the jacobian, otherwise we have taken the derivative only over variables no ocurring (or no variables at all!)

    J = cs_triplet(J, mem.aa8_state); // "optimizes storage of J, after which it may no longer be modified" 
    // TODO recycle memory

    // State
    dprintf("-F(x):\n");
    printv(sop->minusFx, sop->lengthFx);
    dprintf("JF(x):\n");
    printJ(J);

    // Solve
    dprintf("solve:\n");
    solve(sop, J, mem.aa8_state); // TODO allocates even more memory
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
    printf("\n=== buildFxAndJFxAndSolveRepeatedly %d times in partition %d of %d ===\n", iterations, partition, partitions);
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

    printf("\n=== Starting work on partition %d in the thread of the same id ===\n", linear_global_threadId());
    buildFxAndJFxAndSolveRepeatedly(linear_global_threadId(), iterations);
}

// Prototyping functions

FUNCTION(void,
    receiveAndPrintOptimizationData,
    (
    const int lengthz,
    const int lengthfz,

    _In_reads_(xLength) const float* const x, const size_t xLength,
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
    assertEachInRange(xIndices, xIndicesLength, 0, (int)xLength - 1);

    dprintf("yIndices:\n");
    printd(yIndices, yIndicesLength);
    assertEachInRange(yIndices, yIndicesLength, 0, (int)xLength - 1);
}



FUNCTION(
    void,
    makeAndPrintSparseMatrix,
    (
    _In_ const size_t m,
    _In_ const size_t n,
    _In_reads_(xlen) float* x,
    size_t xlen,

    _In_reads_(ijlen) int* ij,
    const size_t ijlen
    ),
    "Creates a sparse matrix from a list of values and a list of pairs of (i, j) indices specifying where to put the corresponding values (triplet form) then cs_prints it to stdout both in column form and vanilla."
	""
	"The matrix should be fairly small because the required intermediate storage is on the stack."
    "Note: This is a prototyping function without any further purpose"
    ) {
    assert(2 * xlen == ijlen);
    assert(xlen <= m*n); // don't allow repeated entries

	char _mem[1000 * 10];
	auto mem = aa8_make(_mem);
    csparse* const A = cs_spalloc(m, n, xlen, 1, mem);

    while (xlen--) {
        int i = *ij++;
        int j = *ij++;
        cs_entry(A, i, j, *x++);
    }

    cs_print(A);

    printf("compress and print again:\n");
    const csparse* const B = cs_triplet(A, mem);
    cs_print(B);
    printf("done--\n");
}

TEST(makeAndPrintSparseMatrix1) {
	unsigned int const count = 1;
	float x[] = { 1. };
	int ij[] = { 0, 0 };
	makeAndPrintSparseMatrix(1, 1, x, count, ij, 2 * count);
}







// Misc


FUNCTION(void, testMain, (), "collection of some tests") {
    dprintf("-- sparse optimize solver --\n");
    dprintf("Compiled with:\n");
    dprintf("lengthz: %d\n", lengthz);
    dprintf("lengthfz: %d\n", lengthfz);

    dprintf("POST begins:\n");

    // expect i: 0-9
    FOR(int,i,0,10,1)
        dprintf("i: %d\n", i);

	int i = 0;
	REPEAT(10)
		dprintf("rep i: %d\n", i++);
}



GLOBAL(int, xx, 0, "xx");
GLOBAL(float, a, 0, "a");
GLOBAL(float, b, 0, "b");
GLOBAL(float, yy, 0, "yy");

FUNCTION(void, xx43, (), "sets xx to 43") {
    xx = 43;
}

FUNCTION(int, get42, (), "returns the answer to the universe life and everything") {
    return 42;
}

FUNCTION(int, add, (int x, int y), "x + y") {
    return x + y;
}

FUNCTION(float, addf, (float x, float y), "x + y with floats") {
    return x + y;
}

FUNCTION(int, multiout, (_Inout_updates_(l) int* x, int l), "returns more than one thing: when called via WSTP this will return an Association with all results") {
    *x = 0;
    return 1;
}



// this can be compiled as a program rather as well as a Wolfram Language LinkedLibrary
#ifndef WL_WSTP_MAIN 
int main() {
    //mainc<<<1,1>>>();
    //cudaDeviceSynchronize();
#if __CUDACC__
    auto e = 74; printf("cudaGetLastError %d %s %s\n", e, cudaGetErrorName((cudaError_t)e), cudaGetErrorString((cudaError_t)e));
#endif
    return 0;
}
#endif