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
