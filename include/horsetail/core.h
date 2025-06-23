#ifndef _HORSETAIL_CORE_H_
#define _HORSETAIL_CORE_H_

#include "horsetail/defs.h"

void HtMain(void);

/* subsystem init functions */
void LgInit(void);
void EnInit(void);

/* subsystem handler functions */
HtBool LgHandleEvent();

/* subsystem update functions */
void LgUpdate();
void EnUpdate();

#endif
