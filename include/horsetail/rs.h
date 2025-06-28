#ifndef _HORSETAIL_RS_H_
#define _HORSETAIL_RS_H_

#define RS_IDENTIFIER_MAX_LENGTH        12

#include "horsetail/horsetail.h"
#include "horsetail/fs.h"

HT_BEGIN_DECLS

typedef enum
{
    HT_RESOURCE_TYPE_NONE = 0,
    HT_RESOURCE_TYPE_FILE,
    HT_RESOURCE_TYPE_TEXTURE,
} HtResourceType;

typedef struct
{
    u32 id;
    char identifier[RS_IDENTIFIER_MAX_LENGTH];
    HtFile file;
    HtResourceType type;
    union
    {
        struct
        {
            i32 width;
            i32 height;
            u8 *bytes;
        } image;
    };
} HtResource;

void RsInit(void);
HtResult RsLoadResource(const char *path, HtResourceType resourceType, const char *identifier, HtResource **outResource);
HtResult RsGetResource(const char *identifier, HtResource **outResource);
void RsUnloadResource(HtResource *resource);

#define RsLoadTexture(path, identifier, outResource)        RsLoadResource(path, HT_RESOURCE_TYPE_TEXTURE, identifier, outResource)

HT_END_DECLS

#endif
