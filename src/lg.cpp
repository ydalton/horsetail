#include "horsetail/horsetail.h"
#include "horsetail/rs.h"
#include "horsetail/in.h"
#include "horsetail/vg.h"
#include "horsetail/clk.h"

#include "horsetail_private.h"
#include "horsetail/array.hpp"

HtBool LgHandleEvent(HtEvent *event)
{
    HT_UNUSED(event);
    return HT_FALSE;
}

/* possible usage code: */
 
#if 0
HtSprite *sprite = NULL;

void LgInit(void)
{
    VgTexture *texture = VgLoadTexture("data/baadu.png", "baadu");

    sprite = SprCreateSpriteEx("baadu", texture, VEC3(0.0, 0.0, 0.0));
    sprite->texture = texture;
}

void LgUpdate(void)
{
    vec3 movement = {0};

    if (InKeyIsDown(HT_KEY_W))
    {
        movement.y = -0.5;
    }
    if (InKeyIsDown(HT_KEY_S))
    {
        movement.y = 0.5;
    }
    if (InKeyIsDown(HT_KEY_A))
    {
        movement.x = -0.5;
    }
    if (InKeyIsDown(HT_KEY_D))
    {
        movement.x = 0.5;
    }

    sprite->Move(movement);
}


#else
void LgInit(void)
{
}

void _ResizeCamera(void)
{
    VgDisplaySize displaySize = {};
    VgCamera *camera = VgGetCamera();
    float ratio = 0;

    VgGetDisplaySize(&displaySize);
    ratio = (float) displaySize.width / displaySize.height;

    Mat4Ortho(-10 * ratio, 10 * ratio, -10, 10, 100, 0.1, &camera->projection);
}

void LgUpdate(void)
{
    VgCamera *camera = VgGetCamera();

    _ResizeCamera();

    if (InKeyIsDown(HT_KEY_ESC))
    {
        HtPostQuitEvent();
    }

    camera->Move(VEC3(0.0, 0.01, 0.0));
}

#endif
