#ifndef _HORSETAIL_CORE_H_
#define _HORSETAIL_CORE_H_

#include "horsetail/defs.h"

void HtMain(void);
void HtError(const char *fmt, ...);
void HtLog(const char *fmt, ...);

/* subsystem handler functions */
HtBool LgHandleEvent();

/* subsystem update functions */
void LgUpdate();

#endif
