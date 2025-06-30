#include "horsetail/mem.h"

void MemArena_Init(MemArena *arena, usize size)
{
    arena->base = MemAlloc(size, MEM_ALLOC_TAG_ARENA);
    arena->size = size;
    arena->offset = 0;
}

void *MemArena_Alloc(MemArena *arena, usize size)
{
    void *ptr = arena->base + arena->offset;
    arena->offset += size;
    return ptr;
}

void MemArena_Reset(MemArena *arena)
{
    HtZeroMemory(arena->base, arena->size);
    arena->offset = 0;
}

void MemArena_DeInit(MemArena *arena)
{
    MemFree(arena->base);
    HtZeroMemory(arena, sizeof(MemArena));
}
