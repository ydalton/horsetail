#ifndef _HORSETAIL_CORE_H_
#define _HORSETAIL_CORE_H_

#include "horsetail/defs.h"

void HtMain(void);
void HtError(const char *fmt, ...);

/* subsystem update functions */
HtBool LgHandleEvent();

#endif
