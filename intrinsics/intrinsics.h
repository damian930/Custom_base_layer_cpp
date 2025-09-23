#ifndef INTRINSICS_H
#define INTRINSICS_H

// TODO: this should be done inside base somewhere
///////////////////////////////////////////////////////////
// Damian: getting some compiler defined here
//
#define COMPILER_MSVC 0
#ifdef _MSC_VER
    #undef COMPILER_MSVC
    #define COMPILER_MSVC 1
#endif
// --------------------------------------------------------

#include <intrin.h>
#include "base/base_include.h"

// Damian: Example: 0b100100 -> returns true, idx -> 2 
B32 find_idx_of_first_least_significant_set_bit(U32 value, U32* idx);














#endif




































