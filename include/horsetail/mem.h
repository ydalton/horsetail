#ifndef _HORSETAIL_MEM_H_
#define _HORSETAIL_MEM_H_

#include "horsetail/horsetail.h"

HT_BEGIN_DECLS

typedef enum
{
    MEM_ALLOC_TAG_NONE = 0,
    MEM_ALLOC_TAG_ARRAY,
    MEM_ALLOC_TAG_RESOURCE,
    MEM_ALLOC_TAG_FILE,
    MEM_ALLOC_TAG_ARENA,
    MEM_ALLOC_TAG_OTHER,
} MemAllocTag;

void *MemAlloc(usize size, MemAllocTag tag);
void *MemRealloc(void *memory, usize size);
void MemFree(void *ptr);

struct _MemArena;
typedef struct _MemArena MemArena;

void MemArena_Init(MemArena *arena, usize size);
void *MemArena_Alloc(MemArena *arena, usize size);
void MemArena_Reset(MemArena *arena);
void MemArena_DeInit(MemArena *arena);

struct _MemArena
{
    void *base;
    usize size;
    usize offset;
    #ifdef __cplusplus
    inline void Init(usize size)
    {
        MemArena_Init(this, size);
    }
    inline void Reset(void)
    {
        MemArena_Reset(this);
    }
    inline void DeInit(void)
    {
        MemArena_DeInit(this);
    }
    #endif
};

HT_END_DECLS

#endif
