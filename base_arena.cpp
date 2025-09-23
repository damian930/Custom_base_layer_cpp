#ifndef D_BASE_ARENA_CPP
#define D_BASE_ARENA_CPP

#include "base_arena.h"


///////////////////////////////////////////////////////////
// Damian: This part should be outside of here, somewhere in the platform independet layer 
//

#include <windows.h> 

// reserve mem
// commit mem 
// release mem

// use ways to make the os control the access fro the mem arena just allocated before it was committedc

#define AreTypesEqual(type1, type2) 1

void OS_Win32_abort(void)
{
    ExitProcess(1);
}

U32 OS_Win32_get_mem_page_size()
{
    SYSTEM_INFO info = {};
    GetSystemInfo(&info);
    return info.dwPageSize;
}

void OS_Win32_reserve_mem(U8* mem, U32* mem_size)
{
    StaticAssert(AreTypesEqual(DWORD, U32), "Win32 DWORD is not U32 as was expected.");

    U32 page_size = OS_Win32_get_mem_page_size();
    U32 pages_used = (U32)(*mem_size / page_size);
    if (pages_used == 0) {  
        *mem_size = page_size;
    }
    else if (pages_used > 1) {
        *mem_size = ((pages_used + 1) * page_size); 
    }

    mem = (U8*)VirtualAlloc(
        Null,
        *mem_size,
        MEM_COMMIT,
        PAGE_NOACCESS
    );

    if (mem == Null)
    {
        OS_Win32_abort();
    }
}
///////////////////////////////////////////////////////////

// Damian: Arena stuff

Arena* arena_alloc(U32 mem_size)
{
    U8* mem = 0;
    OS_Win32_reserve_mem(mem, &mem_size);
    
    // Align the arena bytes as well
    Arena* arena = (Arena*)mem;
    arena->base = (U8*)mem + ArenaMaxSizeInBytes;
    arena->pos  = ArenaMaxSizeInBytes;
    arena->cap  = mem_size;

    return arena;
}

void arena_uninit(Arena* arena)
{
    arena->base = 0;
    arena->base = 0;
    arena->base = 0;
}




#endif 


















