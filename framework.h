#pragma once 
#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>

#include <sal.h>
/*
c.f. https://msdn.microsoft.com/en-us/library/hh916382.aspx

SAL Basics
SAL defines four basic kinds of parameters, which are categorized by usage pattern.


Input to called function
_In_
Data is passed to the called function, and is treated as read-only.
    The parameter must be valid (non NULL) and the value pointed to will not be modified.
    The function will only *read* from the *single-element* buffer.
    The caller must provide the buffer and initialize it.
    _In_ specifies "read-only". A common mistake is to apply _In_ to a parameter that should have the _Inout_ annotation instead.
    _In_ is allowed but ignored by the analyzer on non-pointer scalars.
    void InCallee(_In_ int *pInt)
    {
    int i = *pInt;
    }

Input to called function, and output to caller
_Inout_
Usable data is passed into the function and potentially is modified.
    The pointer must point to valid initialized data before the call, and even if it changes, it must still have a valid value on return. The annotation specifies that the function may freely read from and write to the one-element buffer. The caller must provide the buffer and initialize it.

    void InOutCallee(_Inout_ int *pInt)
    {
    int i = *pInt; // can read
    *pInt = 6; // can write
    }

    Visual Studio Code Analysis validates that callers pass a non-NULL pointer to an initialized buffer for pInt, and that, before return, pInt is still non-NULL and the buffer is initialized.

Output to caller
_Out_
The caller only provides space for the called function to write to. The called function writes data into that space.
    supports a common scenario in which a non-NULL pointer that points to an element buffer is passed in and the function initializes the element. The caller doesn’t have to initialize the buffer before the call; the called function promises to initialize it before it returns.
    void GoodOutCallee(_Out_ int *pInt)
    {
    *pInt = 5;
    }
    void BadOutCallee(_Out_ int *pInt)
    {
    // Did not initialize pInt buffer before returning!
    }

Output of pointer to caller
_Outptr_
Like Output to caller. The value that's returned by the called function is a pointer.
    _Outptr_ is used to annotate a parameter that's intended to return a pointer. The parameter itself should not be NULL, and the called function returns a non-NULL pointer in it *and that pointer points to initialized data* (*).

    Visual Studio Code Analysis validates that the caller passes a non-NULL pointer for *pInt, and that the buffer is initialized by the function before it returns.

    void GoodOutPtrCallee(_Outptr_ int **pInt)
    {
    int *pInt2 = new int;
    *pInt2 = 5;

    *pInt = pInt2;
    }

    void BadOutPtrCallee(_Outptr_ int **pInt)
    {
    int *pInt2 = new int;
    // Did not initialize pInt2 and or pInt to point to valid data buffer before returning! (*)
    *pInt = pInt2;
    }
---
Optional
    void GoodInOptCallee(_In_opt_ int *pInt)
    {
       if(pInt != NULL) {
          int i = *pInt;
       }
    }

    void GoodOutOptCallee(_Out_opt_ int *pInt)
    {
    if (pInt != NULL) {
    *pInt = 5;
    }
    }

    void GoodInOutOptCallee(_Inout_opt_ int *pInt)
    {
    if(pInt != NULL) {
    int i = *pInt;
    *pInt = 6;
    }
    }

    void BadInOutOptCallee(_Inout_opt_ int *pInt)
    {
    int i = *pInt; // Dereferencing NULL pointer ‘pInt’
    *pInt = 6;
    }

    void GoodOutPtrOptCallee(_Outptr_opt_ int **pInt)
    {
    int *pInt2 = new int;
    *pInt2 = 6;

    if(pInt != NULL) {
    *pInt = pInt2;
    }
    }

    void BadOutPtrOptCallee(_Outptr_opt_ int **pInt)
    {
    int *pInt2 = new int;
    *pInt2 = 6;
    *pInt = pInt2; // Dereferencing NULL pointer ‘pInt’
    }
*/

#include <paulwl.h>

#include <cuda.h>
#include <cuda_runtime_api.h>
#include <cuda_runtime.h>
#include <device_functions.h>
#include <device_launch_parameters.h>
#pragma comment(lib,"cudart")

#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>
#include <stdio.h>
#include <stdint.h>
typedef unsigned int uint;
#include <limits.h>
#include <array>
#include <string> 
#include <vector> 
#include <map>
#include <unordered_map> 

#include <tuple>
#include <string>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <iostream>
#include <string>
#include <exception>
#include <iterator>
#include <memory>

#define OSTREAM(CLASSNAME) friend std::ostream& operator<<(std::ostream& os, const CLASSNAME& o)

#include <paul.h> 


#include <assert.h>

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
#define FUNCTION(ret, name, args, usage) /* usage */ __host__ __device__ ret name args

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
#include "$WSTPWrappingCDefinesCUDA.h"


// todo put elsewhere, use CONSTANT() to be able to read them from outside -- this is currently not possible because interplay with the // preprocessor is not implemented in the WSTP wrapper code
/**/
CONSTANTD int lengthz =
#include "lengthz.cpp" // generated
;

CONSTANTD int lengthfz =
#include "lengthfz.cpp" // generated
;

typedef float real;