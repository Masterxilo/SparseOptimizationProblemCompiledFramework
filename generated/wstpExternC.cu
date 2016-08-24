#include "framework.h"
void receiveOptimizationData(real const * const xI, size_t const xLength, int const * const sparseDerivativeZtoYIndicesI, size_t const sparseDerivativeZtoYIndicesLength, int const * const xIndicesI, size_t const xIndicesLength, int const * const yIndicesI, size_t const yIndicesLength);

extern "C" void receiveOptimizationData_()
{
WSGetList(float, xI, xI_length, Real32);
WSGetList(int, sparseDerivativeZtoYIndicesI, sparseDerivativeZtoYIndicesI_length, Integer32);
WSGetList(int, xIndicesI, xIndicesI_length, Integer32);
WSGetList(int, yIndicesI, yIndicesI_length, Integer32);
int xLength;
xLength = xI_length;
int sparseDerivativeZtoYIndicesLength;
sparseDerivativeZtoYIndicesLength = sparseDerivativeZtoYIndicesI_length;
int xIndicesLength;
xIndicesLength = xIndicesI_length;
int yIndicesLength;
yIndicesLength = yIndicesI_length;
receiveOptimizationData(xI, xLength, sparseDerivativeZtoYIndicesI, sparseDerivativeZtoYIndicesLength, xIndicesI, xIndicesLength, yIndicesI, yIndicesLength);
WL_RETURN_VOID();
WSReleaseList(xI, xI_length, Real32);
WSReleaseList(sparseDerivativeZtoYIndicesI, sparseDerivativeZtoYIndicesI_length, Integer32);
WSReleaseList(xIndicesI, xIndicesI_length, Integer32);
WSReleaseList(yIndicesI, yIndicesI_length, Integer32);
}

void receiveOptimizationDataBuildFxAndJFxAndSolveRepeatedly(real const * const xI, size_t const xLength, int const * const sparseDerivativeZtoYIndicesI, size_t const sparseDerivativeZtoYIndicesLength, int const * const xIndicesI, size_t const xIndicesLength, int const * const yIndicesI, size_t const yIndicesLength, int const iterations);

extern "C" void receiveOptimizationDataBuildFxAndJFxAndSolveRepeatedly_()
{
WSGetList(float, xI, xI_length, Real32);
WSGetList(int, sparseDerivativeZtoYIndicesI, sparseDerivativeZtoYIndicesI_length, Integer32);
WSGetList(int, xIndicesI, xIndicesI_length, Integer32);
WSGetList(int, yIndicesI, yIndicesI_length, Integer32);
WSGet(int, iterations, Integer32);
int xLength;
xLength = xI_length;
int sparseDerivativeZtoYIndicesLength;
sparseDerivativeZtoYIndicesLength = sparseDerivativeZtoYIndicesI_length;
int xIndicesLength;
xIndicesLength = xIndicesI_length;
int yIndicesLength;
yIndicesLength = yIndicesI_length;
receiveOptimizationDataBuildFxAndJFxAndSolveRepeatedly(xI, xLength, sparseDerivativeZtoYIndicesI, sparseDerivativeZtoYIndicesLength, xIndicesI, xIndicesLength, yIndicesI, yIndicesLength, iterations);
WL_RETURN_VOID();
WSReleaseList(xI, xI_length, Real32);
WSReleaseList(sparseDerivativeZtoYIndicesI, sparseDerivativeZtoYIndicesI_length, Integer32);
WSReleaseList(xIndicesI, xIndicesI_length, Integer32);
WSReleaseList(yIndicesI, yIndicesI_length, Integer32);
}

__host__ __device__ int lengthzGet();

extern "C" void lengthzGet_()
{
int _result_;
_result_ = lengthzGet();
WSPut(Integer32, _result_);
}

__global__ void KERNEL_lengthzGet(int * _returns_)
{
_returns_[linear_global_threadId()] = lengthzGet();
}

extern "C" void lengthzGet_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
int * _returns_;
_returns_ = tmalloc<int>(gridDim * blockDim);
CUDAKERNEL_LAUNCH(KERNEL_lengthzGet, gridDim, blockDim, _returns_);
WSPutList(Integer32, _returns_, gridDim * blockDim);
memoryFree(_returns_);
}

__host__ __device__ int lengthfzGet();

extern "C" void lengthfzGet_()
{
int _result_;
_result_ = lengthfzGet();
WSPut(Integer32, _result_);
}

__global__ void KERNEL_lengthfzGet(int * _returns_)
{
_returns_[linear_global_threadId()] = lengthfzGet();
}

extern "C" void lengthfzGet_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
int * _returns_;
_returns_ = tmalloc<int>(gridDim * blockDim);
CUDAKERNEL_LAUNCH(KERNEL_lengthfzGet, gridDim, blockDim, _returns_);
WSPutList(Integer32, _returns_, gridDim * blockDim);
memoryFree(_returns_);
}

__host__ __device__ void print(char const * const x);

extern "C" void print_()
{
WSGetCString(x);
print(x);
WL_RETURN_VOID();
WSReleaseCString(x);
}

__global__ void KERNEL_print(char const * const x)
{
print(x);
}

extern "C" void print_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
WSGetCString(x);
CUDAKERNEL_LAUNCH(KERNEL_print, gridDim, blockDim, x);
WL_RETURN_VOID();
WSReleaseCString(x);
}

__host__ __device__ void printv(real const * v, size_t n);

extern "C" void printv_()
{
WSGetList(float, v, v_length, Real32);
int n;
n = v_length;
printv(v, n);
WL_RETURN_VOID();
WSReleaseList(v, v_length, Real32);
}

__global__ void KERNEL_printv(real const * v, size_t n)
{
printv(v, n);
}

extern "C" void printv_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
WSGetList(float, v, v_length, Real32);
float * v_in;
v_in = mallocmemcpy(v, v_length);
int n;
n = v_length;
CUDAKERNEL_LAUNCH(KERNEL_printv, gridDim, blockDim, v_in, n);
WL_RETURN_VOID();
WSReleaseList(v, v_length, Real32);
memoryFree(v_in);
}

__host__ __device__ void printd(int const * v, size_t n);

extern "C" void printd_()
{
WSGetList(int, v, v_length, Integer32);
int n;
n = v_length;
printd(v, n);
WL_RETURN_VOID();
WSReleaseList(v, v_length, Integer32);
}

__global__ void KERNEL_printd(int const * v, size_t n)
{
printd(v, n);
}

extern "C" void printd_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
WSGetList(int, v, v_length, Integer32);
int * v_in;
v_in = mallocmemcpy(v, v_length);
int n;
n = v_length;
CUDAKERNEL_LAUNCH(KERNEL_printd, gridDim, blockDim, v_in, n);
WL_RETURN_VOID();
WSReleaseList(v, v_length, Integer32);
memoryFree(v_in);
}

__host__ __device__ void assertEachInRange(int const * v, size_t len, int const min, int const max);

extern "C" void assertEachInRange_()
{
WSGetList(int, v, v_length, Integer32);
WSGet(int, min, Integer32);
WSGet(int, max, Integer32);
int len;
len = v_length;
assertEachInRange(v, len, min, max);
WL_RETURN_VOID();
WSReleaseList(v, v_length, Integer32);
}

__global__ void KERNEL_assertEachInRange(int const * v, size_t len, int const min, int const max)
{
assertEachInRange(v, len, min, max);
}

extern "C" void assertEachInRange_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
WSGetList(int, v, v_length, Integer32);
WSGet(int, min, Integer32);
WSGet(int, max, Integer32);
int * v_in;
v_in = mallocmemcpy(v, v_length);
int len;
len = v_length;
CUDAKERNEL_LAUNCH(KERNEL_assertEachInRange, gridDim, blockDim, v_in, len, min, max);
WL_RETURN_VOID();
WSReleaseList(v, v_length, Integer32);
memoryFree(v_in);
}

__host__ __device__ void axpyWithReindexing(real * const targetBase, size_t const targetLength, real const a, real const * const addedValues, int const * const targetIndices, size_t const targetIndicesAndAddedValuesLength);

extern "C" void axpyWithReindexing_()
{
WSGetList(float, targetBase, targetBase_length, Real32);
WSGet(float, a, Real32);
WSGetList(float, addedValues, addedValues_length, Real32);
WSGetList(int, targetIndices, targetIndices_length, Integer32);
int targetLength;
targetLength = targetBase_length;
int targetIndicesAndAddedValuesLength;
targetIndicesAndAddedValuesLength = addedValues_length;
checkAllEqual(targetIndices_length, addedValues_length);
float * targetBase_inout;
targetBase_inout = mallocmemcpy(targetBase, targetLength);
axpyWithReindexing(targetBase_inout, targetLength, a, addedValues, targetIndices, targetIndicesAndAddedValuesLength);
WSPutList(Real32, targetBase_inout, targetLength);
WSReleaseList(targetBase, targetBase_length, Real32);
WSReleaseList(addedValues, addedValues_length, Real32);
WSReleaseList(targetIndices, targetIndices_length, Integer32);
memoryFree(targetBase_inout);
}

__global__ void KERNEL_axpyWithReindexing(real * const targetBase_inout, size_t const targetLength, real const a, real const * const addedValues, int const * const targetIndices, size_t const targetIndicesAndAddedValuesLength)
{
axpyWithReindexing(targetBase_inout, targetLength, a, addedValues, targetIndices, targetIndicesAndAddedValuesLength);
}

extern "C" void axpyWithReindexing_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
WSGetList(float, targetBase, targetBase_length, Real32);
WSGet(float, a, Real32);
WSGetList(float, addedValues, addedValues_length, Real32);
WSGetList(int, targetIndices, targetIndices_length, Integer32);
float * addedValues_in;
addedValues_in = mallocmemcpy(addedValues, addedValues_length);
int * targetIndices_in;
targetIndices_in = mallocmemcpy(targetIndices, targetIndices_length);
int targetLength;
targetLength = targetBase_length;
int targetIndicesAndAddedValuesLength;
targetIndicesAndAddedValuesLength = addedValues_length;
checkAllEqual(targetIndices_length, addedValues_length);
float * targetBase_inout;
targetBase_inout = mallocmemcpy(targetBase, targetLength);
CUDAKERNEL_LAUNCH(KERNEL_axpyWithReindexing, gridDim, blockDim, targetBase_inout, targetLength, a, addedValues_in, targetIndices_in, targetIndicesAndAddedValuesLength);
WSPutList(Real32, targetBase_inout, targetLength);
WSReleaseList(targetBase, targetBase_length, Real32);
WSReleaseList(addedValues, addedValues_length, Real32);
WSReleaseList(targetIndices, targetIndices_length, Integer32);
memoryFree(addedValues_in);
memoryFree(targetIndices_in);
memoryFree(targetBase_inout);
}

__host__ __device__ void extract(real * const target, real const * const source, size_t const sourceLength, int const * const sourceIndices, size_t const sourceIndicesAndTargetLength);

extern "C" void extract_()
{
WSGetList(float, source, source_length, Real32);
WSGetList(int, sourceIndices, sourceIndices_length, Integer32);
int sourceLength;
sourceLength = source_length;
int sourceIndicesAndTargetLength;
sourceIndicesAndTargetLength = sourceIndices_length;
float * target;
target = tmalloc<float>(sourceIndicesAndTargetLength);
extract(target, source, sourceLength, sourceIndices, sourceIndicesAndTargetLength);
WSPutList(Real32, target, sourceIndicesAndTargetLength);
WSReleaseList(source, source_length, Real32);
WSReleaseList(sourceIndices, sourceIndices_length, Integer32);
memoryFree(target);
}

__global__ void KERNEL_extract(real * const target, real const * const source, size_t const sourceLength, int const * const sourceIndices, size_t const sourceIndicesAndTargetLength)
{
extract(target, source, sourceLength, sourceIndices, sourceIndicesAndTargetLength);
}

extern "C" void extract_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
WSGetList(float, source, source_length, Real32);
WSGetList(int, sourceIndices, sourceIndices_length, Integer32);
float * source_in;
source_in = mallocmemcpy(source, source_length);
int * sourceIndices_in;
sourceIndices_in = mallocmemcpy(sourceIndices, sourceIndices_length);
int sourceLength;
sourceLength = source_length;
int sourceIndicesAndTargetLength;
sourceIndicesAndTargetLength = sourceIndices_length;
float * target;
target = tmalloc<float>(sourceIndicesAndTargetLength);
CUDAKERNEL_LAUNCH(KERNEL_extract, gridDim, blockDim, target, source_in, sourceLength, sourceIndices_in, sourceIndicesAndTargetLength);
WSPutList(Real32, target, sourceIndicesAndTargetLength);
WSReleaseList(source, source_length, Real32);
WSReleaseList(sourceIndices, sourceIndices_length, Integer32);
memoryFree(source_in);
memoryFree(sourceIndices_in);
memoryFree(target);
}

__host__ __device__ void writeFx(size_t const i, real const val);

extern "C" void writeFx_()
{
WSGet(long long, i, Integer64);
WSGet(float, val, Real32);
writeFx(i, val);
WL_RETURN_VOID();
}

__global__ void KERNEL_writeFx(size_t const i, real const val)
{
writeFx(i, val);
}

extern "C" void writeFx_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
WSGet(long long, i, Integer64);
WSGet(float, val, Real32);
CUDAKERNEL_LAUNCH(KERNEL_writeFx, gridDim, blockDim, i, val);
WL_RETURN_VOID();
}

__host__ __device__ void readZ(real * z, size_t const rowz);

extern "C" void readZ_()
{
WSGet(long long, rowz, Integer64);
float * z;
z = tmalloc<float>(lengthz);
readZ(z, rowz);
WSPutList(Real32, z, lengthz);
memoryFree(z);
}

__global__ void KERNEL_readZ(real * z, size_t const rowz)
{
readZ(z, rowz);
}

extern "C" void readZ_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
WSGet(long long, rowz, Integer64);
float * z;
z = tmalloc<float>(lengthz);
CUDAKERNEL_LAUNCH(KERNEL_readZ, gridDim, blockDim, z, rowz);
WSPutList(Real32, z, lengthz);
memoryFree(z);
}

__host__ __device__ void readZandSetFxRow(real * z, size_t const rowz, size_t const rowfz);

extern "C" void readZandSetFxRow_()
{
WSGet(long long, rowz, Integer64);
WSGet(long long, rowfz, Integer64);
float * z;
z = tmalloc<float>(lengthz);
readZandSetFxRow(z, rowz, rowfz);
WSPutList(Real32, z, lengthz);
memoryFree(z);
}

__global__ void KERNEL_readZandSetFxRow(real * z, size_t const rowz, size_t const rowfz)
{
readZandSetFxRow(z, rowz, rowfz);
}

extern "C" void readZandSetFxRow_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
WSGet(long long, rowz, Integer64);
WSGet(long long, rowfz, Integer64);
float * z;
z = tmalloc<float>(lengthz);
CUDAKERNEL_LAUNCH(KERNEL_readZandSetFxRow, gridDim, blockDim, z, rowz, rowfz);
WSPutList(Real32, z, lengthz);
memoryFree(z);
}

__host__ __device__ void setFxRow(size_t const rowz, size_t const rowfz);

extern "C" void setFxRow_()
{
WSGet(long long, rowz, Integer64);
WSGet(long long, rowfz, Integer64);
setFxRow(rowz, rowfz);
WL_RETURN_VOID();
}

__global__ void KERNEL_setFxRow(size_t const rowz, size_t const rowfz)
{
setFxRow(rowz, rowfz);
}

extern "C" void setFxRow_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
WSGet(long long, rowz, Integer64);
WSGet(long long, rowfz, Integer64);
CUDAKERNEL_LAUNCH(KERNEL_setFxRow, gridDim, blockDim, rowz, rowfz);
WL_RETURN_VOID();
}

__host__ __device__ void buildFx();

extern "C" void buildFx_()
{
buildFx();
WL_RETURN_VOID();
}

__global__ void KERNEL_buildFx()
{
buildFx();
}

extern "C" void buildFx_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
CUDAKERNEL_LAUNCH(KERNEL_buildFx, gridDim, blockDim);
WL_RETURN_VOID();
}

__host__ __device__ real norm2Fx();

extern "C" void norm2Fx_()
{
real _result_;
_result_ = norm2Fx();
WSPut(Real32, _result_);
}

__global__ void KERNEL_norm2Fx(float * _returns_)
{
_returns_[linear_global_threadId()] = norm2Fx();
}

extern "C" void norm2Fx_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
float * _returns_;
_returns_ = tmalloc<float>(gridDim * blockDim);
CUDAKERNEL_LAUNCH(KERNEL_norm2Fx, gridDim, blockDim, _returns_);
WSPutList(Real32, _returns_, gridDim * blockDim);
memoryFree(_returns_);
}

__host__ __device__ float addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBefore();

extern "C" void addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBefore_()
{
float _result_;
_result_ = addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBefore();
WSPut(Real32, _result_);
}

__global__ void KERNEL_addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBefore(float * _returns_)
{
_returns_[linear_global_threadId()] = addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBefore();
}

extern "C" void addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBefore_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
float * _returns_;
_returns_ = tmalloc<float>(gridDim * blockDim);
CUDAKERNEL_LAUNCH(KERNEL_addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBefore, gridDim, blockDim, _returns_);
WSPutList(Real32, _returns_, gridDim * blockDim);
memoryFree(_returns_);
}

__host__ __device__ void getY(real * const outY, int lengthY);

extern "C" void getY_()
{
WSGet(int, lengthY, Integer32);
float * outY;
outY = tmalloc<float>(lengthY);
getY(outY, lengthY);
WSPutList(Real32, outY, lengthY);
memoryFree(outY);
}

__global__ void KERNEL_getY(real * const outY, int lengthY)
{
getY(outY, lengthY);
}

extern "C" void getY_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
WSGet(int, lengthY, Integer32);
float * outY;
outY = tmalloc<float>(lengthY);
CUDAKERNEL_LAUNCH(KERNEL_getY, gridDim, blockDim, outY, lengthY);
WSPutList(Real32, outY, lengthY);
memoryFree(outY);
}

__host__ __device__ void buildFxAndJFxAndSolveRepeatedly(int const iterations);

extern "C" void buildFxAndJFxAndSolveRepeatedly_()
{
WSGet(int, iterations, Integer32);
buildFxAndJFxAndSolveRepeatedly(iterations);
WL_RETURN_VOID();
}

__global__ void KERNEL_buildFxAndJFxAndSolveRepeatedly(int const iterations)
{
buildFxAndJFxAndSolveRepeatedly(iterations);
}

extern "C" void buildFxAndJFxAndSolveRepeatedly_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
WSGet(int, iterations, Integer32);
CUDAKERNEL_LAUNCH(KERNEL_buildFxAndJFxAndSolveRepeatedly, gridDim, blockDim, iterations);
WL_RETURN_VOID();
}

__host__ __device__ void receiveAndPrintOptimizationData(int const lengthz, int const lengthfz, real const * const x, size_t const xLength, int const * const sparseDerivativeZtoYIndices, size_t const sparseDerivativeZtoYIndicesLength, int const * const xIndices, size_t const xIndicesLength, int const * const yIndices, size_t const yIndicesLength);

extern "C" void receiveAndPrintOptimizationData_()
{
WSGet(int, lengthz, Integer32);
WSGet(int, lengthfz, Integer32);
WSGetList(float, x, x_length, Real32);
WSGetList(int, sparseDerivativeZtoYIndices, sparseDerivativeZtoYIndices_length, Integer32);
WSGetList(int, xIndices, xIndices_length, Integer32);
WSGetList(int, yIndices, yIndices_length, Integer32);
int xLength;
xLength = x_length;
int sparseDerivativeZtoYIndicesLength;
sparseDerivativeZtoYIndicesLength = sparseDerivativeZtoYIndices_length;
int xIndicesLength;
xIndicesLength = xIndices_length;
int yIndicesLength;
yIndicesLength = yIndices_length;
receiveAndPrintOptimizationData(lengthz, lengthfz, x, xLength, sparseDerivativeZtoYIndices, sparseDerivativeZtoYIndicesLength, xIndices, xIndicesLength, yIndices, yIndicesLength);
WL_RETURN_VOID();
WSReleaseList(x, x_length, Real32);
WSReleaseList(sparseDerivativeZtoYIndices, sparseDerivativeZtoYIndices_length, Integer32);
WSReleaseList(xIndices, xIndices_length, Integer32);
WSReleaseList(yIndices, yIndices_length, Integer32);
}

__global__ void KERNEL_receiveAndPrintOptimizationData(int const lengthz, int const lengthfz, real const * const x, size_t const xLength, int const * const sparseDerivativeZtoYIndices, size_t const sparseDerivativeZtoYIndicesLength, int const * const xIndices, size_t const xIndicesLength, int const * const yIndices, size_t const yIndicesLength)
{
receiveAndPrintOptimizationData(lengthz, lengthfz, x, xLength, sparseDerivativeZtoYIndices, sparseDerivativeZtoYIndicesLength, xIndices, xIndicesLength, yIndices, yIndicesLength);
}

extern "C" void receiveAndPrintOptimizationData_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
WSGet(int, lengthz, Integer32);
WSGet(int, lengthfz, Integer32);
WSGetList(float, x, x_length, Real32);
WSGetList(int, sparseDerivativeZtoYIndices, sparseDerivativeZtoYIndices_length, Integer32);
WSGetList(int, xIndices, xIndices_length, Integer32);
WSGetList(int, yIndices, yIndices_length, Integer32);
float * x_in;
x_in = mallocmemcpy(x, x_length);
int * sparseDerivativeZtoYIndices_in;
sparseDerivativeZtoYIndices_in = mallocmemcpy(sparseDerivativeZtoYIndices, sparseDerivativeZtoYIndices_length);
int * xIndices_in;
xIndices_in = mallocmemcpy(xIndices, xIndices_length);
int * yIndices_in;
yIndices_in = mallocmemcpy(yIndices, yIndices_length);
int xLength;
xLength = x_length;
int sparseDerivativeZtoYIndicesLength;
sparseDerivativeZtoYIndicesLength = sparseDerivativeZtoYIndices_length;
int xIndicesLength;
xIndicesLength = xIndices_length;
int yIndicesLength;
yIndicesLength = yIndices_length;
CUDAKERNEL_LAUNCH(KERNEL_receiveAndPrintOptimizationData, gridDim, blockDim, lengthz, lengthfz, x_in, xLength, sparseDerivativeZtoYIndices_in, sparseDerivativeZtoYIndicesLength, xIndices_in, xIndicesLength, yIndices_in, yIndicesLength);
WL_RETURN_VOID();
WSReleaseList(x, x_length, Real32);
WSReleaseList(sparseDerivativeZtoYIndices, sparseDerivativeZtoYIndices_length, Integer32);
WSReleaseList(xIndices, xIndices_length, Integer32);
WSReleaseList(yIndices, yIndices_length, Integer32);
memoryFree(x_in);
memoryFree(sparseDerivativeZtoYIndices_in);
memoryFree(xIndices_in);
memoryFree(yIndices_in);
}

__host__ __device__ void makeAndPrintSparseMatrix(size_t const m, size_t const n, real * x, size_t xlen, int * ij, size_t const ijlen);

extern "C" void makeAndPrintSparseMatrix_()
{
WSGet(long long, m, Integer64);
WSGet(long long, n, Integer64);
WSGetList(float, x, x_length, Real32);
WSGetList(int, ij, ij_length, Integer32);
int xlen;
xlen = x_length;
int ijlen;
ijlen = ij_length;
makeAndPrintSparseMatrix(m, n, x, xlen, ij, ijlen);
WL_RETURN_VOID();
WSReleaseList(x, x_length, Real32);
WSReleaseList(ij, ij_length, Integer32);
}

__global__ void KERNEL_makeAndPrintSparseMatrix(size_t const m, size_t const n, real * x, size_t xlen, int * ij, size_t const ijlen)
{
makeAndPrintSparseMatrix(m, n, x, xlen, ij, ijlen);
}

extern "C" void makeAndPrintSparseMatrix_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
WSGet(long long, m, Integer64);
WSGet(long long, n, Integer64);
WSGetList(float, x, x_length, Real32);
WSGetList(int, ij, ij_length, Integer32);
float * x_in;
x_in = mallocmemcpy(x, x_length);
int * ij_in;
ij_in = mallocmemcpy(ij, ij_length);
int xlen;
xlen = x_length;
int ijlen;
ijlen = ij_length;
CUDAKERNEL_LAUNCH(KERNEL_makeAndPrintSparseMatrix, gridDim, blockDim, m, n, x_in, xlen, ij_in, ijlen);
WL_RETURN_VOID();
WSReleaseList(x, x_length, Real32);
WSReleaseList(ij, ij_length, Integer32);
memoryFree(x_in);
memoryFree(ij_in);
}

__host__ __device__ void testMain();

extern "C" void testMain_()
{
testMain();
WL_RETURN_VOID();
}

__global__ void KERNEL_testMain()
{
testMain();
}

extern "C" void testMain_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
CUDAKERNEL_LAUNCH(KERNEL_testMain, gridDim, blockDim);
WL_RETURN_VOID();
}

__host__ __device__ void xx43();

extern "C" void xx43_()
{
xx43();
WL_RETURN_VOID();
}

__global__ void KERNEL_xx43()
{
xx43();
}

extern "C" void xx43_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
CUDAKERNEL_LAUNCH(KERNEL_xx43, gridDim, blockDim);
WL_RETURN_VOID();
}

__host__ __device__ int get42();

extern "C" void get42_()
{
int _result_;
_result_ = get42();
WSPut(Integer32, _result_);
}

__global__ void KERNEL_get42(int * _returns_)
{
_returns_[linear_global_threadId()] = get42();
}

extern "C" void get42_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
int * _returns_;
_returns_ = tmalloc<int>(gridDim * blockDim);
CUDAKERNEL_LAUNCH(KERNEL_get42, gridDim, blockDim, _returns_);
WSPutList(Integer32, _returns_, gridDim * blockDim);
memoryFree(_returns_);
}

__host__ __device__ int add(int x, int y);

extern "C" void add_()
{
WSGet(int, x, Integer32);
WSGet(int, y, Integer32);
int _result_;
_result_ = add(x, y);
WSPut(Integer32, _result_);
}

__global__ void KERNEL_add(int x, int y, int * _returns_)
{
_returns_[linear_global_threadId()] = add(x, y);
}

extern "C" void add_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
WSGet(int, x, Integer32);
WSGet(int, y, Integer32);
int * _returns_;
_returns_ = tmalloc<int>(gridDim * blockDim);
CUDAKERNEL_LAUNCH(KERNEL_add, gridDim, blockDim, x, y, _returns_);
WSPutList(Integer32, _returns_, gridDim * blockDim);
memoryFree(_returns_);
}

__host__ __device__ real addf(real x, real y);

extern "C" void addf_()
{
WSGet(float, x, Real32);
WSGet(float, y, Real32);
real _result_;
_result_ = addf(x, y);
WSPut(Real32, _result_);
}

__global__ void KERNEL_addf(real x, real y, float * _returns_)
{
_returns_[linear_global_threadId()] = addf(x, y);
}

extern "C" void addf_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
WSGet(float, x, Real32);
WSGet(float, y, Real32);
float * _returns_;
_returns_ = tmalloc<float>(gridDim * blockDim);
CUDAKERNEL_LAUNCH(KERNEL_addf, gridDim, blockDim, x, y, _returns_);
WSPutList(Real32, _returns_, gridDim * blockDim);
memoryFree(_returns_);
}

__host__ __device__ int multiout(int * x, int l);

extern "C" void multiout_()
{
WSGetList(int, x, x_length, Integer32);
int l;
l = x_length;
int * x_inout;
x_inout = mallocmemcpy(x, l);
int _result_;
_result_ = multiout(x_inout, l);
WSPutFunction(stdlink, "Association", 2);
WSPutFunction(stdlink, "Rule", 2);
WSPutCString("return");
WSPut(Integer32, _result_);
WSPutFunction(stdlink, "Rule", 2);
WSPutCString("x");
WSPutList(Integer32, x_inout, l);
WSReleaseList(x, x_length, Integer32);
memoryFree(x_inout);
}

__global__ void KERNEL_multiout(int * x_inout, int l, int * _returns_)
{
_returns_[linear_global_threadId()] = multiout(x_inout, l);
}

extern "C" void multiout_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
WSGetList(int, x, x_length, Integer32);
int l;
l = x_length;
int * x_inout;
x_inout = mallocmemcpy(x, l);
int * _returns_;
_returns_ = tmalloc<int>(gridDim * blockDim);
CUDAKERNEL_LAUNCH(KERNEL_multiout, gridDim, blockDim, x_inout, l, _returns_);
WSPutFunction(stdlink, "Association", 2);
WSPutFunction(stdlink, "Rule", 2);
WSPutCString("x");
WSPutList(Integer32, x_inout, l);
WSPutFunction(stdlink, "Rule", 2);
WSPutCString("returns");
WSPutList(Integer32, _returns_, gridDim * blockDim);
WSReleaseList(x, x_length, Integer32);
memoryFree(x_inout);
memoryFree(_returns_);
}

extern int dprintEnabled;

extern "C" void dprintEnabled_get()
{
WSPut(Integer32, dprintEnabled);
}

extern int lengthP;

extern "C" void lengthP_get()
{
WSPut(Integer32, lengthP);
}

extern int xx;

extern "C" void xx_get()
{
WSPut(Integer32, xx);
}

extern real a;

extern "C" void a_get()
{
WSPut(Real32, a);
}

extern real b;

extern "C" void b_get()
{
WSPut(Real32, b);
}

extern real yy;

extern "C" void yy_get()
{
WSPut(Real32, yy);
}

extern real * x;

extern int lengthx;

extern "C" void x_get()
{
WSPutList(Real32, x, lengthx);
}

extern real * minusFx;

extern int lengthFx;

extern "C" void minusFx_get()
{
WSPutList(Real32, minusFx, lengthFx);
}

extern real * h;

extern int lengthY;

extern "C" void h_get()
{
WSPutList(Real32, h, lengthY);
}

extern int * yIndices;

extern int lengthY;

extern "C" void yIndices_get()
{
WSPutList(Integer32, yIndices, lengthY);
}

extern "C" void dprintEnabled_set()
{
WSGetInteger32(stdlink,&dprintEnabled);
WL_RETURN_VOID();
}

extern "C" void lengthP_set()
{
WSGetInteger32(stdlink,&lengthP);
WL_RETURN_VOID();
}

extern "C" void xx_set()
{
WSGetInteger32(stdlink,&xx);
WL_RETURN_VOID();
}

extern "C" void a_set()
{
WSGetReal32(stdlink,&a);
WL_RETURN_VOID();
}

extern "C" void b_set()
{
WSGetReal32(stdlink,&b);
WL_RETURN_VOID();
}

extern "C" void yy_set()
{
WSGetReal32(stdlink,&yy);
WL_RETURN_VOID();
}

extern "C" void x_set()
{
WSGetList(float, x_in, x_in_length, Real32);
freemalloctmemcpy(&x, x_in, x_in_length);
lengthx = x_in_length;
WL_RETURN_VOID();
WSReleaseList(x_in, x_in_length, Real32);
}

extern "C" void minusFx_set()
{
WSGetList(float, minusFx_in, minusFx_in_length, Real32);
freemalloctmemcpy(&minusFx, minusFx_in, minusFx_in_length);
lengthFx = minusFx_in_length;
WL_RETURN_VOID();
WSReleaseList(minusFx_in, minusFx_in_length, Real32);
}

extern "C" void h_set()
{
WSGetList(float, h_in, h_in_length, Real32);
freemalloctmemcpy(&h, h_in, h_in_length);
lengthY = h_in_length;
WL_RETURN_VOID();
WSReleaseList(h_in, h_in_length, Real32);
}

extern "C" void yIndices_set()
{
WSGetList(int, yIndices_in, yIndices_in_length, Integer32);
freemalloctmemcpy(&yIndices, yIndices_in, yIndices_in_length);
lengthY = yIndices_in_length;
WL_RETURN_VOID();
WSReleaseList(yIndices_in, yIndices_in_length, Integer32);
}

