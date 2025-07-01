#include "horsetail/in.h"

HtBool gKeysDown[HT_KEY_LAST] = {0};

void InpSetKey(HtKey key, HtBool isDown);


HtBool InHandleEvent(HtEvent *event)
{
    /* ignore all other kinds of events */
    if (!(event->type == HT_EVENT_KEY_DOWN
        || event->type == HT_EVENT_KEY_UP))
    {
        return HT_FALSE;
    }

    HtAssert(event->keyPress.key != HT_KEY_NONE);
    HtAssert(event->keyPress.key != HT_KEY_LAST);

    if (event->type == HT_EVENT_KEY_DOWN)
    {
        InpSetKey(event->keyPress.key, HT_TRUE);
    }
    else if (event->type == HT_EVENT_KEY_UP)
    {
        InpSetKey(event->keyPress.key, HT_FALSE);
    }

    /* we merely want to snoop on the key, for now */
    return HT_FALSE;
}

void InpSetKey(HtKey key, HtBool isDown)
{
    gKeysDown[key] = isDown;
}

HtBool InKeyIsDown(HtKey key)
{
    HtAssert(key != HT_KEY_NONE);
    HtAssert(key != HT_KEY_LAST);
    return gKeysDown[key];
}
