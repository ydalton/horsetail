#include "horsetail/vg.h"
#include "horsetail/rs.h"
#include "vg_gl.h"

struct _VgTexture
{
    VgGLTexture glTexture;
};

HtResult VgLoadTexture(const char *path, const char *identifier)
{
    HtResult result = HT_ERROR_GENERIC;
    HtResource *resource = NULL;

    if (!RsResourceIsLoaded(identifier))
    {
        result = RsLoadResource(path, HT_RESOURCE_TYPE_TEXTURE, identifier, &resource);
        if (result != HT_SUCCESS)
        {
            HtError("Could not load texture \"%s\" identifier %s\n", path, identifier);
        }
    }


    return HT_ERROR_GENERIC;
}

VgTexture *VgGetTexture(const char *identifier)
{
    HT_UNUSED(identifier);
    return NULL;
}
