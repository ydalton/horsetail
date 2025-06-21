#ifndef _HORSETAIL_MEM_H_
#define _HORSETAIL_MEM_H_

#include "horsetail/horsetail.h"

typedef enum
{
    MEM_ALLOC_TAG_OTHER
} MemAllocTag;

void *MemAlloc(usize size, MemAllocTag tag);
void MemFree(void *ptr);

#endif
