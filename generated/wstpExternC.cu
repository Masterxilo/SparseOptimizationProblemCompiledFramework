void setPartitions(size_t newPartitionsCount);

extern "C" void setPartitions_()
{
WSGet(long long, newPartitionsCount, Integer64);
setPartitions(newPartitionsCount);
WL_RETURN_VOID();
}

void receiveSharedOptimizationData(float const * const xI, size_t const xLength);

extern "C" void receiveSharedOptimizationData_()
{
WSGetList(float, xI, xI_length, Real32);
int xLength;
xLength = xI_length;
receiveSharedOptimizationData(xI, xLength);
WL_RETURN_VOID();
WSReleaseList(xI, xI_length, Real32);
}

void receiveOptimizationData(int const partition, int const * const sparseDerivativeZtoYIndicesI, size_t const sparseDerivativeZtoYIndicesLength, int const * const xIndicesI, size_t const xIndicesLength, int const * const yIndicesI, size_t const yIndicesLength);

extern "C" void receiveOptimizationData_()
{
WSGet(int, partition, Integer32);
WSGetList(int, sparseDerivativeZtoYIndicesI, sparseDerivativeZtoYIndicesI_length, Integer32);
WSGetList(int, xIndicesI, xIndicesI_length, Integer32);
WSGetList(int, yIndicesI, yIndicesI_length, Integer32);
int sparseDerivativeZtoYIndicesLength;
sparseDerivativeZtoYIndicesLength = sparseDerivativeZtoYIndicesI_length;
int xIndicesLength;
xIndicesLength = xIndicesI_length;
int yIndicesLength;
yIndicesLength = yIndicesI_length;
receiveOptimizationData(partition, sparseDerivativeZtoYIndicesI, sparseDerivativeZtoYIndicesLength, xIndicesI, xIndicesLength, yIndicesI, yIndicesLength);
WL_RETURN_VOID();
WSReleaseList(sparseDerivativeZtoYIndicesI, sparseDerivativeZtoYIndicesI_length, Integer32);
WSReleaseList(xIndicesI, xIndicesI_length, Integer32);
WSReleaseList(yIndicesI, yIndicesI_length, Integer32);
}

__host__ __device__ void f(float const * const input, float * const out);

extern "C" void f_()
{
WSGetList(float, input, input_length, Real32);
float * out;
out = tmalloc<float>(lengthfz);
f(input, out);
WSPutList(Real32, out, lengthfz);
WSReleaseList(input, input_length, Real32);
memoryFree(out);
}

__global__ void KERNEL_f(float const * const input, float * const out)
{
f(input, out);
}

extern "C" void f_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
WSGetList(float, input, input_length, Real32);
float * input_in;
input_in = mallocmemcpy(input, input_length);
float * out;
out = tmalloc<float>(lengthfz);
CUDAKERNEL_LAUNCH(KERNEL_f, gridDim, blockDim, input_in, out);
WSPutList(Real32, out, lengthfz);
WSReleaseList(input, input_length, Real32);
memoryFree(input_in);
memoryFree(out);
}

__host__ __device__ void df(unsigned int const i, float const * const input, float * const out);

extern "C" void df_()
{
WSGet(int, i, Integer32);
WSGetList(float, input, input_length, Real32);
float * out;
out = tmalloc<float>(lengthfz);
df(i, input, out);
WSPutList(Real32, out, lengthfz);
WSReleaseList(input, input_length, Real32);
memoryFree(out);
}

__global__ void KERNEL_df(unsigned int const i, float const * const input, float * const out)
{
df(i, input, out);
}

extern "C" void df_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
WSGet(int, i, Integer32);
WSGetList(float, input, input_length, Real32);
float * input_in;
input_in = mallocmemcpy(input, input_length);
float * out;
out = tmalloc<float>(lengthfz);
CUDAKERNEL_LAUNCH(KERNEL_df, gridDim, blockDim, i, input_in, out);
WSPutList(Real32, out, lengthfz);
WSReleaseList(input, input_length, Real32);
memoryFree(input_in);
memoryFree(out);
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

__host__ __device__ void printv(float const * v, size_t n);

extern "C" void printv_()
{
WSGetList(float, v, v_length, Real32);
int n;
n = v_length;
printv(v, n);
WL_RETURN_VOID();
WSReleaseList(v, v_length, Real32);
}

__global__ void KERNEL_printv(float const * v, size_t n)
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

__host__ __device__ void getY(int partition, float * const outY, int lengthY);

extern "C" void getY_()
{
WSGet(int, partition, Integer32);
WSGet(int, lengthY, Integer32);
float * outY;
outY = tmalloc<float>(lengthY);
getY(partition, outY, lengthY);
WSPutList(Real32, outY, lengthY);
memoryFree(outY);
}

__global__ void KERNEL_getY(int partition, float * const outY, int lengthY)
{
getY(partition, outY, lengthY);
}

extern "C" void getY_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
WSGet(int, partition, Integer32);
WSGet(int, lengthY, Integer32);
float * outY;
outY = tmalloc<float>(lengthY);
CUDAKERNEL_LAUNCH(KERNEL_getY, gridDim, blockDim, partition, outY, lengthY);
WSPutList(Real32, outY, lengthY);
memoryFree(outY);
}

__host__ __device__ void buildFxAndJFxAndSolveRepeatedly(int const partition, int const iterations);

extern "C" void buildFxAndJFxAndSolveRepeatedly_()
{
WSGet(int, partition, Integer32);
WSGet(int, iterations, Integer32);
buildFxAndJFxAndSolveRepeatedly(partition, iterations);
WL_RETURN_VOID();
}

__global__ void KERNEL_buildFxAndJFxAndSolveRepeatedly(int const partition, int const iterations)
{
buildFxAndJFxAndSolveRepeatedly(partition, iterations);
}

extern "C" void buildFxAndJFxAndSolveRepeatedly_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
WSGet(int, partition, Integer32);
WSGet(int, iterations, Integer32);
CUDAKERNEL_LAUNCH(KERNEL_buildFxAndJFxAndSolveRepeatedly, gridDim, blockDim, partition, iterations);
WL_RETURN_VOID();
}

__host__ __device__ void buildFxAndJFxAndSolveRepeatedlyThreadIdPartition(int const iterations);

extern "C" void buildFxAndJFxAndSolveRepeatedlyThreadIdPartition_()
{
WSGet(int, iterations, Integer32);
buildFxAndJFxAndSolveRepeatedlyThreadIdPartition(iterations);
WL_RETURN_VOID();
}

__global__ void KERNEL_buildFxAndJFxAndSolveRepeatedlyThreadIdPartition(int const iterations)
{
buildFxAndJFxAndSolveRepeatedlyThreadIdPartition(iterations);
}

extern "C" void buildFxAndJFxAndSolveRepeatedlyThreadIdPartition_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
WSGet(int, iterations, Integer32);
CUDAKERNEL_LAUNCH(KERNEL_buildFxAndJFxAndSolveRepeatedlyThreadIdPartition, gridDim, blockDim, iterations);
WL_RETURN_VOID();
}

__host__ __device__ void receiveAndPrintOptimizationData(int const lengthz, int const lengthfz, float const * const x, size_t const xLength, int const * const sparseDerivativeZtoYIndices, size_t const sparseDerivativeZtoYIndicesLength, int const * const xIndices, size_t const xIndicesLength, int const * const yIndices, size_t const yIndicesLength);

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

__global__ void KERNEL_receiveAndPrintOptimizationData(int const lengthz, int const lengthfz, float const * const x, size_t const xLength, int const * const sparseDerivativeZtoYIndices, size_t const sparseDerivativeZtoYIndicesLength, int const * const xIndices, size_t const xIndicesLength, int const * const yIndices, size_t const yIndicesLength)
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

__host__ __device__ void makeAndPrintSparseMatrix(size_t const m, size_t const n, float * x, size_t xlen, int * ij, size_t const ijlen);

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

__global__ void KERNEL_makeAndPrintSparseMatrix(size_t const m, size_t const n, float * x, size_t xlen, int * ij, size_t const ijlen)
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

__host__ __device__ float addf(float x, float y);

extern "C" void addf_()
{
WSGet(float, x, Real32);
WSGet(float, y, Real32);
float _result_;
_result_ = addf(x, y);
WSPut(Real32, _result_);
}

__global__ void KERNEL_addf(float x, float y, float * _returns_)
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

__host__ __device__ void mainc();

extern "C" void mainc_()
{
mainc();
WL_RETURN_VOID();
}

__global__ void KERNEL_mainc()
{
mainc();
}

extern "C" void mainc_CUDA()
{
WSGet(int, gridDim, Integer32);
WSGet(int, blockDim, Integer32);
CUDAKERNEL_LAUNCH(KERNEL_mainc, gridDim, blockDim);
WL_RETURN_VOID();
}

extern int dprintEnabled;

extern "C" void dprintEnabled_get()
{
WSPut(Integer32, dprintEnabled);
}

extern int xx;

extern "C" void xx_get()
{
WSPut(Integer32, xx);
}

extern float a;

extern "C" void a_get()
{
WSPut(Real32, a);
}

extern float b;

extern "C" void b_get()
{
WSPut(Real32, b);
}

extern float yy;

extern "C" void yy_get()
{
WSPut(Real32, yy);
}

extern float * x;

extern int lengthx;

extern "C" void x_get()
{
WSPutList(Real32, x, lengthx);
}

extern "C" void dprintEnabled_set()
{
WSGetInteger32(stdlink,&dprintEnabled);
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

