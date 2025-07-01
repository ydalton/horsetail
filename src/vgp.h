#ifndef _HORSETAIL_VGP_H_
#define _HORSETAIL_VGP_H_

#include "horsetail/vg.h"

HT_BEGIN_DECLS

void VgpLogRendererInfo(void);
void VgpBeginFrame(void);
void VgpEndFrame(void);
void VgpOnResize(const VgDisplaySize *displaySize);

HT_END_DECLS

#endif
