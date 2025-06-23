#include "horsetail/rs.h"
#include "horsetail/mem.h"

#include "vendor/stb_image.h"

void RsInit(void)
{
    HtLog("Rs: initialized");
}

HtResult RsLoadResource(const char *path, HtResourceType resourceType, const char *identifier, HtResource **outResource)
{
    HtResource *resource = NULL;
    HtResult result = HT_ERROR_GENERIC;
    HtFile file = {0};
    
    HtAssert(outResource != NULL);
    HT_UNUSED(identifier);

    resource = MemAlloc(sizeof(HtResource), MEM_ALLOC_TAG_RESOURCE);
    if (resource == NULL)
    {
        return HT_ERROR_NO_MEMORY;
    }

    result = FsLoadFile(path, &file);
    HtAssert(result == HT_SUCCESS);
    HtCopyMemory(&resource->file, &file, sizeof(HtFile));
    HtCopyString(resource->identifier, identifier, sizeof(resource->identifier));
    
    /* do some resource type specific stuff */
    switch (resourceType)
    {
        case HT_RESOURCE_TYPE_IMAGE:
            {
                int width;
                int height;

                stbi_load_from_memory(resource->file.data,
                                      resource->file.size,
                                      &width,
                                      &height,
                                      NULL,
                                      4);

                resource->image.width = width;
                resource->image.height = height;
            }
            break;
        default:
            HtAssertNotReached();
            break;
    }

    *outResource = resource;

    return result;
}
