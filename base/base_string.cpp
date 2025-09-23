#ifndef D_BASE_STRING_CPP
#define D_BASE_STRING_CPP

#include "base_string.h"

Str8 string8_null_terminate(Arena* arena, Str8 str8)
{
    Str8 result = {};
    result.str = Null;
    result.len = str8.len + 1;

    result.str = ArenaPushArr(arena, U8, result.len);
    MemCopy(result.str, str8.str, str8.len);
    result.str[result.len - 1] = '\0';

    return result;
}


#endif
















