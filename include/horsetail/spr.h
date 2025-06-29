#ifndef _HORSETAIL_SPR_H_
#define _HORSETAIL_SPR_H_

#include "horsetail/vg.h"

struct _HtSprite;
typedef struct _HtSprite HtSprite;

void HtSprite_Move(HtSprite *sprite, vec3 movement);

#define HT_SPRITE_IDENTIFIER_MAX_LENGTH     12

struct _HtSprite
{
    VgObject *object;
    char identifier[HT_SPRITE_IDENTIFIER_MAX_LENGTH];
#ifdef __cplusplus
    inline void Move(vec3 movement)
    {
        HtSprite_Move(this, movement);
    }
#endif
};

HtSprite *SprCreateSpriteEx(const char *spriteId, const char *textureId, const char *meshId, vec3 initialPosition);
void SprDestroySprite(HtSprite *sprite);

#endif
