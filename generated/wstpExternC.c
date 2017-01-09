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

void f(float const * const input, float * const out);

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

void df(unsigned int const i, float const * const input, float * const out);

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

void print(char const * const x);

extern "C" void print_()
{
WSGetCString(x);
print(x);
WL_RETURN_VOID();
WSReleaseCString(x);
}

void printd(int const * v, size_t n);

extern "C" void printd_()
{
WSGetList(int, v, v_length, Integer32);
int n;
n = v_length;
printd(v, n);
WL_RETURN_VOID();
WSReleaseList(v, v_length, Integer32);
}

void printv(float const * v, size_t n);

extern "C" void printv_()
{
WSGetList(float, v, v_length, Real32);
int n;
n = v_length;
printv(v, n);
WL_RETURN_VOID();
WSReleaseList(v, v_length, Real32);
}

int lengthzGet();

extern "C" void lengthzGet_()
{
int _result_;
_result_ = lengthzGet();
WSPut(Integer32, _result_);
}

int lengthfzGet();

extern "C" void lengthfzGet_()
{
int _result_;
_result_ = lengthfzGet();
WSPut(Integer32, _result_);
}

void getY(int partition, float * const outY, int lengthY);

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

void buildFxAndJFxAndSolveRepeatedly(int const partition, int const iterations);

extern "C" void buildFxAndJFxAndSolveRepeatedly_()
{
WSGet(int, partition, Integer32);
WSGet(int, iterations, Integer32);
buildFxAndJFxAndSolveRepeatedly(partition, iterations);
WL_RETURN_VOID();
}

void buildFxAndJFxAndSolveRepeatedlyThreadIdPartition(int const iterations);

extern "C" void buildFxAndJFxAndSolveRepeatedlyThreadIdPartition_()
{
WSGet(int, iterations, Integer32);
buildFxAndJFxAndSolveRepeatedlyThreadIdPartition(iterations);
WL_RETURN_VOID();
}

void receiveAndPrintOptimizationData(int const lengthz, int const lengthfz, float const * const x, size_t const xLength, int const * const sparseDerivativeZtoYIndices, size_t const sparseDerivativeZtoYIndicesLength, int const * const xIndices, size_t const xIndicesLength, int const * const yIndices, size_t const yIndicesLength);

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

void makeAndPrintSparseMatrix(size_t const m, size_t const n, float * x, size_t xlen, int * ij, size_t const ijlen);

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

void testMain();

extern "C" void testMain_()
{
testMain();
WL_RETURN_VOID();
}

void xx43();

extern "C" void xx43_()
{
xx43();
WL_RETURN_VOID();
}

int get42();

extern "C" void get42_()
{
int _result_;
_result_ = get42();
WSPut(Integer32, _result_);
}

int add(int x, int y);

extern "C" void add_()
{
WSGet(int, x, Integer32);
WSGet(int, y, Integer32);
int _result_;
_result_ = add(x, y);
WSPut(Integer32, _result_);
}

float addf(float x, float y);

extern "C" void addf_()
{
WSGet(float, x, Real32);
WSGet(float, y, Real32);
float _result_;
_result_ = addf(x, y);
WSPut(Real32, _result_);
}

int multiout(int * x, int l);

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

void mainc();

extern "C" void mainc_()
{

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

