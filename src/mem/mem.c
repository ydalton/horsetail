#include <stdlib.h>

#include "horsetail/mem.h"

void *MemAlloc(usize size, MemAllocTag tag)
{
    HT_UNUSED(tag);

    return malloc(size);
}

void MemFree(void *ptr)
{
    free(ptr);
}
