#ifndef _HORSETAIL_VGP_H_
#define _HORSETAIL_VGP_H_

#include "horsetail/vg.h"

void VgpLogRendererInfo(void);
void VgpBeginFrame(void);
void VgpEndFrame(void);
void VgpOnResize(const VgDisplaySize *displaySize);

#endif
