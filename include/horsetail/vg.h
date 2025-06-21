#ifndef _HORSETAIL_VG_H_
#define _HORSETAIL_VG_H_

#include "horsetail/defs.h"

#define VG_DISPLAY_DEFAULT_NAME       "Horsetail"
#define VG_DISPLAY_DEFAULT_WIDTH      800
#define VG_DISPLAY_DEFAULT_HEIGHT     600

typedef struct
{
    i32 width;
    i32 height;
} VgDisplaySize;

void VgInit(void);
void VgUpdate(void);
void VgShutdown(void);

HtBool VgGetDisplaySize(VgDisplaySize *outDisplaySize);
HtBool VgSetDisplaySize(const VgDisplaySize *displaySize);

#endif
