#ifndef _HORSETAIL_UTIL_H_
#define _HORSETAIL_UTIL_H_

#ifndef _HORSETAIL_H_
#error "Do not include this file seperately. Include horsetail.h"
#endif

const char *HtResultToString(HtResult result);
void HtZeroMemory(void *ptr, usize size);

#endif
