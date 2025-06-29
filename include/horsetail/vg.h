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
struct _VgTexture;
struct _VgMesh;

typedef struct _VgCamera VgCamera;
typedef struct _VgTexture VgTexture;
typedef struct _VgMesh VgMesh;

HtBool VgGetDisplaySize(VgDisplaySize *outDisplaySize);
HtBool VgSetDisplaySize(const VgDisplaySize *displaySize);

HtResult VgLoadTexture(const char *path, const char *identifier);
VgTexture *VgGetTexture(const char *identifier);

HtResult VgLoadMesh(const char *path, const char *identifier);
VgMesh *VgGetMesh(const char *path);

VgCamera *VgGetCamera(void);
void VgCamera_Move(VgCamera *camera, vec3 movement);

typedef struct _VgObject
{
    mat4 modelMatrix;
    VgTexture *texture;
    VgMesh *mesh;
} VgObject;

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
