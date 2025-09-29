#ifndef D_BASE_STRING_H
#define D_BASE_STRING_H

#include "base_type_redefenitions.h"
#include "base_arena.h"

// NOTE: this is more of an approach RFJ uses with his strings.
//       he has them not null terminated always, but then when he created them inside an arena
//       he just makes the byte after the string null, this way he can use them right away 
//       after initting it on temp and then clearing the temp
//
//       i will see how it goes and if it resurlts in some dumb errors.
//       otherway would be to store a flag "is_null_terminated" inside the string
//       and if i then use it i know what to expect from it. I can then always remove it when needed.
//       this way i kinda explicitly have it be null terminated. 
//       i could also create a separate struct for it calles null terminated string, 
//       but that might be too much, but idk, will see. 
struct Str8 {
    U8* str;
    U64 len;
};

Str8 str8_from_c_str(Arena* arena, const char* c_string, U64 c_string_len);
Str8 str8_from_str8(Arena* arena, Str8 str);
Str8 str8_buffer(Arena* arena, U64 len);

#define Str8FromClit(arena_p, c_lit) str8_from_c_str(arena_p, c_lit, ArrayCount(c_lit))

struct Str8_node {
    Str8 str;
    Str8_node* next;
};

struct Str8_list {
    Str8_node* first;
    Str8_node* last;
    U64 string_count;
    U64 char_count;
};

// TODO: entertain this idea 
//        -- Str8_list list = flist("%str8 %n", some_str8, value);
//       it would be nicer to use this insted of repeated line of 
//        -- str8_push_back_str8(arena, &list, some_str8);

void str8_push_front_str8(Arena* arena, Str8_list* list, Str8 str);

void str8_push_front_c_str(Arena* arena, Str8_list* list, char* c_str, U64 c_str_len);
#define Str8PushFrontClit(arena_p, list_p, clit) ( str8_push_front_c_str(arena_p, list_p, (char*)clit, ArrayCount(clit)) )

void str8_push_back_str8(Arena* arena, Str8_list* list, Str8 str);

void str8_push_back_c_str(Arena* arena, Str8_list* list, char* c_str, U64 c_str_len);
#define Str8PushBackClit(arena_p, list_p, clit) ( str8_push_back_c_str(arena_p, list_p, (char*)clit, ArrayCount(clit)) )

Str8 str8_from_list(Arena* arena, Str8_list* list);
Str8 str8_from_U32(Arena* arena, U32 value);

#endif





























