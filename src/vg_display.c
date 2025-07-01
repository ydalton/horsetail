#include "horsetail/vg.h"
#include "vgp.h"

struct
{
    i32 width;
    i32 height;
} vgDisplay = {
    .width = VG_DISPLAY_DEFAULT_WIDTH,
    .height = VG_DISPLAY_DEFAULT_HEIGHT,
};

HtBool VgGetDisplaySize(VgDisplaySize *outDisplaySize)
{
    HtAssert(outDisplaySize != NULL);
    HtAssert(vgDisplay.width != 0);
    HtAssert(vgDisplay.height != 0);

    outDisplaySize->width = vgDisplay.width;
    outDisplaySize->height = vgDisplay.height;

    return HT_TRUE;
}

HtBool VgSetDisplaySize(const VgDisplaySize *displaySize)
{
    HtAssert(displaySize != NULL);

    vgDisplay.width = displaySize->width;
    vgDisplay.height = displaySize->height;
    
    VgpOnResize(displaySize);

    return HT_TRUE;
}
