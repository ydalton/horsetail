#ifndef _HORSETAIL_PRIVATE_H_
#define _HORSETAIL_PRIVATE_H_

#include "horsetail/horsetail.h"

HT_BEGIN_DECLS

void HtMain(void);

/* subsystem init functions */
void LgInit(void);
void EnInit(void);
void ClkInit(void);

/* subsystem handler functions */
HtBool LgHandleEvent(HtEvent *event);
HtBool InHandleEvent(HtEvent *event);

/* subsystem update functions */
void ClkUpdate(void);
void LgUpdate(void);
void EnUpdate(void);

HT_END_DECLS

#endif
