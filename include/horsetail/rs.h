#ifndef _HORSETAIL_RS_H_
#define _HORSETAIL_RS_H_

#define RS_IDENTIFIER_MAX_LENGTH        12

#include "horsetail/horsetail.h"
#include "horsetail/fs.h"

typedef enum
{
    HT_RESOURCE_TYPE_NONE = 0,
    HT_RESOURCE_TYPE_FILE,
    HT_RESOURCE_TYPE_IMAGE,
} HtResourceType;

typedef struct
{
    u32 id;
    char identifier[RS_IDENTIFIER_MAX_LENGTH];
    HtFile file;

    union
    {
        struct
        {
            i32 width;
            i32 height;
        } image;
    };
} HtResource;

void RsInit(void);

#endif
