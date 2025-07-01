#include "horsetail/rs.h"
#include "horsetail/vg.h"

#include "vg_gl.h"

struct _VgMesh
{
    VgGLArrayBuffer arrayBuffer;
};

HtResult VgLoadMesh(const char *path, const char *identifier)
{
    HtResource *resource = NULL;

    HT_UNUSED(path);
    HT_UNUSED(identifier);

    return HT_ERROR_UNIMPLEMENTED;
}

VgMesh *VgGetMesh(const char *identifier)
{
    HT_UNUSED(identifier);
    return NULL;
}
