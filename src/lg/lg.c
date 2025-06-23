#include "horsetail/horsetail.h"

HtBool LgHandleEvent(HtEvent *event)
{
    if (event->type == HT_EVENT_KEY_DOWN
        && event->keyPress.key == HT_KEY_ESC)
    {
        HtPostQuitEvent();
        return HT_TRUE;
    }

    return HT_FALSE;
}

void LgInit(void)
{
}

void LgUpdate(void)
{
}
