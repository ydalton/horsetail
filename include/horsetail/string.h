#ifndef _HORSETAIL_STRING_H_
#define _HORSETAIL_STRING_H_

#include "horsetail/horsetail.h"

HT_BEGIN_DECLS

void HtCopyString(char *dest, const char *src, usize max);
void HtCopyMemory(void *dest, const void *src, usize size);

HT_END_DECLS

#endif
