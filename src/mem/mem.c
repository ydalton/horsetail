#include <stdlib.h>

#include "horsetail/horsetail.h"
#include "horsetail/mem.h"

void MemInit(void)
{
    HtLog("Mem: initialized\n");
}

void *MemAlloc(usize size, MemAllocTag tag)
{
    HT_UNUSED(tag);

    return malloc(size);
}

void MemFree(void *ptr)
{
    free(ptr);
}
