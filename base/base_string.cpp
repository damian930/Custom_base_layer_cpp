#ifndef D_BASE_STRING_CPP
#define D_BASE_STRING_CPP

#include "base_string.h"

Str8 str8_from_c_str(Arena* arena, const char* c_string, U64 c_string_len)
{
    U8* new_str = ArenaPushArr(arena, U8, c_string_len);
    Str8 result = {};
    result.str = new_str;
    result.len = c_string_len - 1;
    *(new_str + result.len) = 0;
    MemCopy(result.str, c_string, result.len); 
    // The operation above might fail if pages havet been commited yet
    // TODO: deal with this`
    return result;
}

Str8 str8_from_str8(Arena* arena, Str8 str)
{
    U8* new_str = ArenaPushArr(arena, U8, str.len);
    Str8 result = {};
    result.str = new_str;
    result.len = str.len;
    *(new_str + result.len + 1) = 0;
    MemCopy(result.str, str.str, str.len); 
    // The operation above might fail if pages havet been commited yet
    // TODO: deal with this
    return result;
}

Str8 str8_buffer(Arena* arena, U64 len)
{
    Str8 str = {};
    str.str = ArenaPushArr(arena, U8, len);
    str.len = len;
    return str;
}

void str8_push_front_str8(Arena* arena, Str8_list* list, Str8 str)
{
    Str8_node* new_node = ArenaPush(arena, Str8_node);
    new_node->next = 0;
    new_node->str  = str;
    
    QueuePushFront(list, new_node);
    list->string_count += 1;
    list->char_count += str.len;
}

void str8_push_front_c_str(Arena* arena, Str8_list* list, char* c_str, U64 c_str_len)
{
    Str8 str = str8_from_c_str(arena, c_str, c_str_len);
    str8_push_front_str8(arena, list, str);
}
#define Str8PushFrontClit(arena_p, list_p, clit) ( str8_push_front_c_str(arena_p, list_p, (char*)clit, ArrayCount(clit)) )

void str8_push_back_str8(Arena* arena, Str8_list* list, Str8 str)
{
    Str8_node* new_node = ArenaPush(arena, Str8_node);
    new_node->next = 0;
    new_node->str  = str;
    
    QueuePushBack(list, new_node);
    list->string_count += 1;
    list->char_count += str.len;
}

void str8_push_back_c_str(Arena* arena, Str8_list* list, char* c_str, U64 c_str_len)
{
    Str8 str = str8_from_c_str(arena, c_str, c_str_len);
    str8_push_back_str8(arena, list, str);
}
#define Str8PushBackClit(arena_p, list_p, clit) ( str8_push_back_c_str(arena_p, list_p, (char*)clit, ArrayCount(clit)) )

Str8 str8_from_list(Arena* arena, Str8_list* list)
{
    Str8 result = {};
    B32 first_node = true;
    for (Str8_node* node = list->first; node != 0; node = node->next)
    {
        Str8 copy = str8_from_str8(arena, node->str);
        if (first_node)
        {
            first_node = false;
            result = copy;
        }
        else 
        {
            result.len += copy.len;
        }

    }
    return result;    
}

Str8 str8_from_U32(Arena* arena, U32 value)
{
    // TODO: do this better (19th September 2025 12:33)
    char buffer[50];
    int number_written = sprintf(buffer, "%d", value);
    number_written += 1; // Accout the null term
    Assert(number_written < ArrayCount(buffer));
    
    Str8 result = str8_from_c_str(arena, buffer, number_written);
    return result;
}



#endif
















