#ifndef DAMIAN_OS_WIN32_H
#define DAMIAN_OS_WIN32_H

#include "base/base_include.h"

#include <windows.h>

struct Win32_data {
    B32 is_initialised;
    U32 page_size;
    U32 allocation_granularity;
};

void win32_init();
void win32_abort();

// TODO: a static assert macro here that makes sure that DWORD is the same as U32 would be nice to have

void* win32_mem_reserve(U32* n_bytes_to_reserve);
void win32_mem_commit(void* mem_p, U32* n_bytes_to_commit);
void win32_mem_protect(void* mem_p, U32 n_bytes_to_protect);
void win32_mem_decomit();
void win32_mem_release(void* ptr);

// -- Damian: file system stuff

struct Win32_file {
    void* handle;
};

// TODO: see if using a cpp namespaces enum is better and then using some sort of static type check for its values type
//       then it would be way harder to have an error of type mismatch or something, 
//       trying this might be nice if it helps to namespace these names
namespaced_enum File_open_setting : U32 {
    Read_access   = (1 << 0),
    Write_access  = (1 << 1),
    Open_existing = (1 << 2),
    Create_new    = (1 << 3),
};

// NOTE: i might want to return a bool if it was open to then be able to defere loop it.
//       file then can be create above and passed in as a param in.
Win32_file win32_open_file(Arena* arena, Str8 file_name, U32 file_open_settings);
void win32_close_file(Win32_file file);
Str8 win32_file_read(Arena* arena, Win32_file file);

// TODO: these will have to be implemented
// Write to file
// Read range from file

#endif