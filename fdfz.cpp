#define double real // $CFormDefines works with double, but can be forced to an arbitrary floating point type like this
#include "$CFormDefines.cpp"
#undef double


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