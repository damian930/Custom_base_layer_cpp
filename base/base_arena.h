#ifndef D_BASE_ARENA_H
#define D_BASE_ARENA_H

#include "base_type_redefenitions.h"
#include "base_macros.h"

// TODO: add alignment
struct Arena {
    U32 mem_reserved;
    U32 mem_commited;

    U8* base_pos;
    U64 current_pos;
};
#define ArenaMaxSizeInBytes 64
StaticAssert(sizeof(Arena) < ArenaMaxSizeInBytes, "Arena size is bigger than was expected.");

Arena* arena_alloc(U32 mem_size);
void arena_release(Arena* arena);

U8* arena_push_nozero(Arena* arena, U64 size);
U8* arena_push(Arena* arena, U32 size);

#define ArenaPush(arena_p, type) (type*) arena_push(arena_p, sizeof(type))
#define ArenaPushArr(arena_p, type, count) (type*) arena_push(arena_p, sizeof(type) * count)

struct Temp_arena {
    Arena* arena;
    U64 start_pos;
};

Temp_arena* arena_temp_begin(Arena* arena);
void arena_temp_end(Temp_arena* temp);
#endif




















































