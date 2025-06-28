#include "horsetail/horsetail.h"
#include "horsetail/rs.h"
#include "horsetail/in.h"
#include "horsetail/vg.h"
#include "horsetail/clk.h"

#include "horsetail_private.h"

HtBool LgHandleEvent(HtEvent *event)
{
    HT_UNUSED(event);
    return HT_FALSE;
}


void LgInit(void)
{
    VgCamera *camera = VgGetCamera();
    Mat4Ortho(-1, 1, 1, 1, 100, 0.1, &camera->projection);
#if 0
    HtSprite *sprite;
    RsLoadResource();

    sprite = HtCreateSprite();
    sprite->SetTexture();
#endif
}

void LgUpdate(void)
{
    VgCamera *camera = VgGetCamera();

    if (InKeyIsDown(HT_KEY_ESC))
    {
        HtPostQuitEvent();
    }

    camera->Move(VEC3(0.0, 0.01, 0.0));
}
