#ifndef _HORSETAIL_VG_H_
#define _HORSETAIL_VG_H_

#include "horsetail/horsetail.h"
#include "horsetail/math.h"

#define VG_DISPLAY_DEFAULT_NAME       "Horsetail"
#define VG_DISPLAY_DEFAULT_WIDTH      800
#define VG_DISPLAY_DEFAULT_HEIGHT     600

HT_BEGIN_DECLS

typedef struct
{
    i32 width;
    i32 height;
} VgDisplaySize;

struct _VgCamera;
typedef struct _VgCamera VgCamera;

void VgInit(void);
void VgUpdate(void);
void VgShutdown(void);

HtBool VgGetDisplaySize(VgDisplaySize *outDisplaySize);
HtBool VgSetDisplaySize(const VgDisplaySize *displaySize);

VgCamera *VgGetCamera(void);
void VgCamera_Move(VgCamera *camera, vec3 movement);

struct _VgCamera {
    mat4 projection;
    mat4 view;
#ifdef __cplusplus
    inline void Move(vec3 movement)
    {
        VgCamera_Move(this, movement);
    }
#endif
};

HT_END_DECLS;

#endif
