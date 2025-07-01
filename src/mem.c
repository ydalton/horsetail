#include "horsetail/horsetail.h"
#include "horsetail/mem.h"
#include "horsetail/impl.h"

void MemInit(void)
{
    HtLog("Mem: initialized\n");
}

/* TODO: own implementations */

void *MemAlloc(usize size, MemAllocTag tag)
{
    void *memory = NULL;
    HT_UNUSED(tag);

    memory = ImplMemAlloc(size);
    HtZeroMemory(memory, size);

    return memory;
}

void MemFree(void *memory)
{
    ImplMemFree(memory);
}

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
