#ifndef D_BASE_ARENA_CPP
#define D_BASE_ARENA_CPP

#include "base_arena.h"
#include "os/win32/win32.h"

#define AreTypesEqual(type1, type2) NotImplemented

// Damian: Arena stuff

Arena* arena_alloc(U32 mem_size)
{
    U32 bytes_to_reserve = Kilobytes_U32(10);    
    void* reserved_mem = win32_mem_reserve(&bytes_to_reserve);
    
    U32 bytes_to_commit = Kilobytes_U32(1);
    win32_mem_commit(reserved_mem, &bytes_to_commit);
    
    U8* mem      = (U8*)reserved_mem;
    Arena* arena = (Arena*)mem;
    arena->mem_reserved = bytes_to_reserve;
    arena->mem_commited = bytes_to_commit;
    arena->base_pos     = mem;
    arena->current_pos  = ArenaMaxSizeInBytes;
    
    return arena;
}

void arena_release(Arena* arena)
{
    win32_mem_release(arena->base_pos);
    arena = 0;
}

U8* arena_push_nozero(Arena* arena, U32 size)
{
    // Since windows commits on page boundary, and our commit is always on page boundary,
    // then we have to get to the next page for windows to round down to the nearest start of page
    // and then commit 
    
    // TODO: check if we have run out of reserved mem    
    U8* base = (U8*)arena;
    if (size >= arena->mem_commited)
    {
        win32_mem_commit(base + arena->mem_commited, &size);
        arena->mem_commited += size;
    }

    U8* return_pos = arena->base_pos + arena->current_pos;
    arena->current_pos += size;
    return return_pos;
}

U8* arena_push(Arena* arena, U32 size)
{
    U8* mem = arena_push_nozero(arena, size);
    MemSet(mem, 0, size);
    return mem;
}

Temp_arena* arena_temp_begin(Arena* arena)
{
    U64 start_pos = arena->current_pos;
    Temp_arena* temp = ArenaPush(arena, Temp_arena);
    temp->arena = arena;
    temp->start_pos = start_pos;
    return temp;
}

void arena_temp_end(Temp_arena* temp)
{
    temp->arena->current_pos = temp->start_pos;
    temp->arena = 0;
    temp->start_pos = 0;
}

#endif 


















