#include "horsetail/spr.h"
#include "horsetail/mem.h"

HtSprite *SprCreateSpriteEx(const char *spriteId, const char *textureId, const char *meshId, vec3 initialPosition)
{
    HtSprite *sprite = NULL;
    VgTexture *texture = NULL;
    VgMesh *mesh = NULL;

    HtZeroMemory(sprite, sizeof(*sprite));

    texture = VgGetTexture(textureId);
    mesh = VgGetMesh(meshId);

    HtAssert(texture != NULL);
    HtAssert(mesh != NULL);

    sprite->object->modelMatrix = Mat4Identity();
    sprite->object->texture = texture;
    sprite->object->mesh = mesh;

    Mat4Translate(initialPosition, &sprite->object->modelMatrix);
    HtCopyString(sprite->identifier, spriteId, HT_ARRAY_SIZE(sprite->identifier));

    return sprite;
}

void SprDestroySprite(HtSprite *sprite)
{
    HtAssert(sprite != NULL);

    MemFree(sprite);
}
