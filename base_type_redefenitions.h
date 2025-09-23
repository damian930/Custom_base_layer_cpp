#ifndef D_BASE_TYPES_H
#define D_BASE_TYPES_H

#include <stdint.h>

typedef int8_t  S8;
typedef int16_t S16;
typedef int32_t  S32;
typedef int64_t  S64;

typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

typedef float F32;
typedef double F64;

typedef S32 B32;

#define local_persist static
#define file_private static
#define global_ static 

#define namespaced_enum enum class

#define Null NULL




#endif






























