#include "horsetail/rs.h"
#include "horsetail/mem.h"
#include "horsetail/hashtable.hpp"

#include "vendor/stb_image.h"

HtBool gRsIsInitialized = HT_FALSE;

#define HT_RESOURCE_COUNT           1024

HtResource gResources[HT_RESOURCE_COUNT] = {};

HtHashTable<HtResource> gResourceHashTable;

void RsInit(void)
{

    gResourceHashTable.Init(gResources, HT_RESOURCE_COUNT);
    HtLog("Rs: initialized\n");
    gRsIsInitialized = HT_TRUE;
}

HtResult RsLoadResource(const char *path, HtResourceType resourceType, const char *identifier, HtResource **outResource)
{
    HtResource *resource = NULL;
    HtResult result = HT_ERROR_GENERIC;
    HtFile file = {};
    
    HtAssert(gRsIsInitialized);
    HtAssert(outResource != NULL);
    HT_UNUSED(identifier);

    resource = gResourceHashTable.Get(identifier);
    if (resource == NULL)
    {
        return HT_ERROR_NO_MEMORY;
    }

    /* TODO: hook this up with a proper asset file */
#ifndef RS_RESOURCE_FILE
    result = FsLoadFile(path, &file);
    if (result != HT_SUCCESS)
    {
        goto fail_file_load;
    }
#else
#error TODO
#endif

    HtCopyMemory(&resource->file, &file, sizeof(HtFile));
    resource->type = resourceType;
    
    /* do some resource type specific stuff */
    switch (resourceType)
    {
        case HT_RESOURCE_TYPE_TEXTURE:
            {
                int width;
                int height;
                u8 *bytes;

                bytes = stbi_load_from_memory(resource->file.data,
                                              resource->file.size,
                                              &width,
                                              &height,
                                              NULL,
                                              4);

                if (bytes != NULL)
                {
                    resource->image.width = width;
                    resource->image.height = height;
                    resource->image.bytes = bytes;
                }
                else
                {
                    HtLog("Rs: warning: resource specified to be of type "
                          HT_TO_STRING(HT_RESOURCE_TYPE_TEXTURE)
                          " but image load failed, setting to "
                          HT_TO_STRING(HT_RESOURCE_TYPE_FILE) ".", path);

                    resource->type = HT_RESOURCE_TYPE_FILE;
                }
            }
            break;
        default:
            HtAssertNotReached();
            break;
    }

    /* if the data has been transformed into the proper format, then
     * we don't need to keep the original file data
     */
    if (resource->type != HT_RESOURCE_TYPE_FILE)
    {
        FsUnloadFile(&resource->file);
    }

    if (resource != NULL)
    {
        *outResource = resource;
    }

    return result;
fail_file_load:
    MemFree(resource);
    return result;
}

HtResource *RsGetResource(const char *identifier)
{
    HT_UNUSED(identifier);
    return NULL;
}

HtBool RsResourceIsLoaded(const char *identifier)
{
    HT_UNUSED(identifier);
    return HT_FALSE;
}

void RsUnloadResource(HtResource *resource)
{
    HT_UNUSED(resource);
}
