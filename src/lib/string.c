#include <string.h>

#include "horsetail/string.h"

/* TODO: own implementations */

void HtCopyString(char *dest, const char *src, usize max)
{
    strncpy(dest, src, max);
}

void HtCopyMemory(void *dest, const void *src, usize size)
{
    memcpy(dest, src, size);
}
