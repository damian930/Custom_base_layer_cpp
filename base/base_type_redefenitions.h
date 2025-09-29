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
// NOTE: this had underscore to it, sice i like to use cout insted of printf
//       and to include cout i need to include iostream, and it has its own global macro  

#define namespaced_enum enum class

#define Null NULL




#endif






























