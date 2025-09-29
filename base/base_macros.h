#ifndef D_BASE_MACROS_H
#define D_BASE_MACROS_H

#include "base_type_redefenitions.h"
#include <stdio.h>
#include <string.h>

#define namespaced_enum enum class 
// NOTE: (damian, 4th September 2025):
//  Starting enums with value of 1 is gereat,
//  since then there is never a moment of confusion between enum value 0
//  and unnitialised state of 0
//  This is especially great if "{0} init strategy" is used in the code base.

#define Bytes_U32(value)     ((U32) value)
#define Kilobytes_U32(value) ((U32) 1024 * Bytes_U32(value))
#define Megabytes_U32(value) ((U32) 1024 * Kilobytes_U32(value))
#define Gigabytes_U32(value) ((U32) 1024 * Megabytes_U32(value))
#define Terabytes_U32(value) ((U32) 1024 * Gigabytes_U32(value))

#define MsInSec ((U32)1000)

// TODO: add comp time variable support for assert and other macros to expand into different things
#define Assert(expr) do { if (!(expr)) {*((U8*)0) = 69;} } while(false);
#define StaticAssert(value, clit) static_assert(value, clit);

#define InvalidCodePath Assert(false);
#define DebugStopHere do { U32 __dbg_stop_here__ = 0; } while(false);
#define NotImplemented Assert(false)

#define ArrayCount(static_arr) (sizeof(static_arr) / sizeof(static_arr[0]))

#define ToggleBool(bool) do { bool = (bool ? false : true); } while(false);

///////////////////////////////////////////////////////////
// Damian: Mem stuff
//
#define MemSet(dest_p, byte_value, mem_size) \
    do { memset((void*)dest_p, byte_value, mem_size); } while(false);
#define MemCopy(dest_p, src_p, n_bytes) \
    do { memcpy((void*)dest_p, (void*)src_p, n_bytes); } while(false);
#define MemZeroOut(mem_p, mem_size) \
    do { MemSet(mem_p, 0, mem_size); } while(false);

#define Swap(type, x, y) \
    do { type swapper = x; x = y; y = swapper; } while(false);

///////////////////////////////////////////////////////////
// Damian: Loop stuff
//
#define ForEachIndex(type, it_var_name, max_index) \
    for (type it_var_name = 0; it_var_name < max_index; it_var_name += 1) 

#define DefereLoop(start, end) for ( int __i__ = (start, 0); __i__ == 0; __i__ += 1, end)

///////////////////////////////////////////////////////////
// Damian: Generic macros for custom built data struct manipulation
//
#define StackPush_Name(list, new_node, name_for_first_in_list, name_for_next_in_node) \
            if (list->name_for_first_in_list == 0) {     \
                list->name_for_first_in_list = new_node; \
            } else {                                     \
                new_node->name_for_next_in_node = list->name_for_first_in_list; \
                list->name_for_first_in_list = new_node;                        \
            }

#define QueuePushFront_Name(queue, new_node, name_for_first_in_queue, name_for_last_in_queue, name_for_next_in_node) \
            if (queue->name_for_first_in_queue == 0) {     \
                queue->name_for_first_in_queue = new_node; \
                queue->name_for_last_in_queue = new_node;  \
            } else {                                       \
                new_node->name_for_next_in_node = list->name_for_first_in_queue; \
                queue->name_for_first_in_queue = new_node;                       \
            }

#define QueuePushBack_Name(queue, new_node, name_for_first_in_queue, name_for_last_in_queue, name_for_next_in_node) \
            if (queue->name_for_first_in_queue == 0) {     \
                queue->name_for_first_in_queue = new_node; \
                queue->name_for_last_in_queue = new_node;  \
            } else {                                       \
               queue->name_for_last_in_queue->name_for_next_in_node = new_node; \
               queue->name_for_last_in_queue = new_node;                        \
            }


#define StackPush(list, new_node) StackPush_Name(list, new_node, first, next)
#define QueuePushFront(list, new_node) QueuePushFront_Name(list, new_node, first, last, next)
#define QueuePushBack(list, new_node) QueuePushBack_Name(list, new_node, first, last, next)



#endif




















