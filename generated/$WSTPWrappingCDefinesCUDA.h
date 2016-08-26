
#define memoryAllocate(ptr, sizeInBytes) {cudaDeviceSynchronize();cudaMallocManaged(&ptr, (sizeInBytes));cudaDeviceSynchronize();assert(ptr);CUDA_CHECK_ERRORS();}
#define memoryFree(ptr) {cudaDeviceSynchronize();cudaFree(ptr);cudaDeviceSynchronize();CUDA_CHECK_ERRORS();}

#pragma once

#ifdef __CUDACC__
__host__ __device__ 
#endif

inline int linear_global_threadId() {
#ifdef __CUDA_ARCH__
    return blockDim.x * blockIdx.x + threadIdx.x;
#else
    return 0;
#endif
}

#include <paulwl.h>
#include <assert.h>

#ifdef __CUDACC__
#define INLINEFUNCTION inline __host__
#else
#define INLINEFUNCTION inline
#endif

#define CUDA_CHECK_ERRORS() {auto e = cudaGetLastError(); printf("cudaGetLastError %d %s %s\n", e, cudaGetErrorName(e), cudaGetErrorString(e));}
#ifdef __CUDACC__
#include <time.h>
#define CUDAKERNEL_LAUNCH(name, griddim, blockdim, ...) {auto t0 = clock(); name<<<griddim, blockdim>>>(__VA_ARGS__); cudaDeviceSynchronize();printf("%s finished in %f s\n",#name,(double)(clock()-t0)/CLOCKS_PER_SEC);CUDA_CHECK_ERRORS();}
#else
#define CUDAKERNEL_LAUNCH(name, griddim, blockdim, ...) 
#endif

template<typename T>
INLINEFUNCTION T* tmalloc(const size_t n) {
assert(n);
    T* out;
    memoryAllocate(out, sizeof(T) * n);
    return out;
}

template<typename T>
INLINEFUNCTION T* tmalloczeroed(const size_t n) {
assert(n);
    T* out;
    memoryAllocate(out, sizeof(T) * n);
    memset(out, 0, sizeof(T) * n);
    return out;
}

template<typename T>
INLINEFUNCTION T* mallocmemcpy(T const * const x, const size_t n) {
assert(n);
    auto out = tmalloc<T>(n);
    memcpy(out, x, sizeof(T) * n);
    return out;
}
#define checkAllEqual(a,b) assert(a == b)

// note: lists should be treated read-only
#define WSGetList(basetype, varname, lengthvar, wstype) basetype * varname; int lengthvar; WSGet##wstype##List(stdlink, &varname, &lengthvar);

#define WSReleaseList(varname, lengthvar, wstype) {WSRelease##wstype##List(stdlink, varname, lengthvar);}

// note: strings should be treated read-only

#define WSPutCString(cstr) WSPutString(stdlink, cstr)

#define WSGetCString(varname) char * varname; WSGetString(stdlink, (const char**)&varname);
#define WSReleaseCString(varname) {WSReleaseString(stdlink, varname);}

#define WSGet(basetype, varname, wstype) basetype varname; WSGet##wstype(stdlink, &varname);

#define WSPutList(wstype, what, len) {WSPut##wstype##List(stdlink, what, len);}
#define WSPut(wstype, what) {WSPut##wstype(stdlink, what);}


#include <string.h>
#include <memory.h>
void freemallocstrcpy(char** dest, const char* const src) {
    if (*dest) memoryFree(*dest);
    auto sz = strlen(src) + 1;
    memoryAllocate(*dest, sz);
    strcpy(*dest, src);
}

template<typename T>
void freemalloctmemcpy(T** dest, const T* const src, int n)  {
assert(n);
    if (*dest) memoryFree(*dest);

    auto sz = sizeof(T) * n;

    memoryAllocate(*dest, sz);
    memcpy(*dest, src, sz);
}
