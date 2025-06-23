#ifndef _HORSETAIL_MEM_H_
#define _HORSETAIL_MEM_H_

#include "horsetail/horsetail.h"

typedef enum
{
    MEM_ALLOC_TAG_NONE = 0,
    MEM_ALLOC_TAG_ARRAY,
    MEM_ALLOC_TAG_RESOURCE,
    MEM_ALLOC_TAG_FILE,
    MEM_ALLOC_TAG_OTHER,
} MemAllocTag;

void *MemAlloc(usize size, MemAllocTag tag);
void *MemRealloc(void *memory, usize size);
void MemFree(void *ptr);

#endif
