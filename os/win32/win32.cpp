#ifndef DAMIAN_OS_WIN32_CPP
#define DAMIAN_OS_WIN32_CPP

#include "base/base_include.h"
#include "os/win32/win32.h"

#include <windows.h>

global_ Win32_data win32_data;

void win32_init()
{
    if (!win32_data.is_initialised)
    {
        win32_data.is_initialised = true;
        
        SYSTEM_INFO sys_info = {};
        GetSystemInfo(&sys_info);
        win32_data.page_size = sys_info.dwPageSize;
        win32_data.allocation_granularity = sys_info.dwAllocationGranularity;
    }
    
}

void win32_abort(void)
{
    ExitProcess(1);
}

// TODO: a static assert macro here that makes sure that DWORD is the same as U32 would be nice to have

// -- Damian: memory stuff

void* win32_mem_reserve(U32* n_bytes_to_reserve)
{
    // Windows does tell us that allocations are align on some boundary that
    // we can gen from the system info call. Thos that values represents the 
    // vram adresses, i am not going to care about it here.
    // But i will care about the data we reserve to be exactly align to a page boundary

    U32 bytes_till_page_boundary = (*n_bytes_to_reserve + win32_data.page_size - 1);
    bytes_till_page_boundary = bytes_till_page_boundary % win32_data.page_size; 
    *n_bytes_to_reserve += bytes_till_page_boundary;
    void* mem = VirtualAlloc(0, *n_bytes_to_reserve, MEM_RESERVE, PAGE_NOACCESS);
    return mem;
}

void win32_mem_commit(void* mem_p, U32* n_bytes_to_commit)
{
    // Since win32 commits pages by aligning then to some boundary, i am doing it here
    U32 bytes_till_page_boundary = (*n_bytes_to_commit + win32_data.page_size - 1);
    bytes_till_page_boundary = bytes_till_page_boundary % win32_data.page_size; 
    *n_bytes_to_commit += bytes_till_page_boundary;
    void* succ = VirtualAlloc(mem_p, *n_bytes_to_commit, MEM_COMMIT, PAGE_READWRITE);
    // TODO: do some with this succ check here
    Assert(succ);
}

void win32_mem_protect(void* mem_p, U32 n_bytes_to_protect)
{
    // Use VirtualProtect here
    NotImplemented;
}

void win32_mem_decomit()
{
    // Windows decomits memory the same way, by pages
    // This means that the page of the pointer we pass in will be decomited 
    // and the page that might be touched by (pointed + "size to decomit")

    NotImplemented;
    
    // BOOL succ = VirtualFree();
    // Assert(succ);
}

void win32_mem_release(void* ptr)
{
    BOOL succ = VirtualFree(ptr, 0, MEM_RELEASE);
    Assert(succ);
}

// -- Damian: file system stuff

Win32_file win32_open_file(Arena* arena, Str8 file_name, U32 file_open_settings)
{
    U32 win32_file_access_rights        = 0;
    U32 win32_file_share_mode           = 0;
    U32 win32_file_creating_disposition = 0;
    U32 win32_file_attributes           = 0;

    if (file_open_settings & (U32)File_open_setting::Read_access) {
        win32_file_access_rights |= GENERIC_READ;
    }
    if (file_open_settings & (U32)File_open_setting::Write_access) {
        win32_file_access_rights |= GENERIC_WRITE;
    }
    
    win32_file_share_mode = 0; // NOTE: we dont allow any subprocesses to access this file

    if (file_open_settings & (U32)File_open_setting::Open_existing) {
        win32_file_creating_disposition |= OPEN_EXISTING;
    }
    if (file_open_settings & (U32)File_open_setting::Create_new) {
        win32_file_creating_disposition |= CREATE_NEW;
    }

    Temp_arena* temp = arena_temp_begin(arena);
    Str8 file_name_null_terminated = str8_from_str8(temp->arena, file_name);

    // TODO: see namig files, path, namespaces to see how win32 deals with maxpath size for older version
    HANDLE handle = CreateFileA(
        (char*)file_name_null_terminated.str,
        win32_file_access_rights,
        win32_file_share_mode,
        NULL, // This means that this handle cannot be inherited by child processed by the process that opened this handle
        win32_file_creating_disposition,
        win32_file_attributes,
        Null
    );

    if (handle == INVALID_HANDLE_VALUE) {
        Assert(false) // TODO: do some about this
    }
    arena_temp_end(temp);
    
    Win32_file result = {handle};
    return result;;
}

void win32_close_file(Win32_file file)
{
    Assert(file.handle != INVALID_HANDLE_VALUE);
    CloseHandle(file.handle);
    file.handle = INVALID_HANDLE_VALUE;
}

Str8 win32_file_read(Arena* arena, Win32_file file)
{
    // Get file size
    // Allocate that much for string
    // Mem copy 
    // Return
    LARGE_INTEGER file_size = {};
    if (GetFileSizeEx(file.handle, &file_size))
    {
        U64 size = file_size.QuadPart;
        if (SetFilePointerEx(file.handle, LARGE_INTEGER{}, Null, FILE_BEGIN))
        {
            U8* buffer = ArenaPushArr(arena, U8, size);
            DWORD bytes_read = 0;

            // NOTE: ReadFile takes in an unsigned long, which is an uint, whitch has the max values of 4,294,967,295 == 4Gb
            if (ReadFile(file.handle, (void*)buffer, size, &bytes_read, Null))
            {
                Assert(bytes_read == size); // TODO: this has to not be an assert;
                Str8 str = {buffer, size};
                return str;
            }
        }
    }
    Assert(false);
}

// TODO: these will have to be implemented
// Write to file
// Read range from file

#endif
















