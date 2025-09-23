#ifndef D_BASE_ARENA_H
#define D_BASE_ARENA_H

#include "base_type_redefenitions.h"
#include "base_macros.h"

struct Arena {
    U8* base;
    U64 pos;
    U64 cap;
};
#define ArenaMaxSizeInBytes 64
StaticAssert(sizeof(Arena) < ArenaMaxSizeInBytes, "Arena size is bigger than was expected.");

Arena* arena_alloc(U32 mem_size);
void arena_release(Arena* arena);

void* arena_push_nozero(Arena* arena, U64 size);
void* arena_push(Arena* arena, U32 size);



#define ArenaPush(arena_p, type) (type*) arena_push(arena_p, sizeof(type))
#define ArenaPushArr(arena_p, type, count) (type*) arena_push(arena_p, sizeof(type) * count)









#endif




















































