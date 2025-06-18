#include "horsetail/defs.h"
#include "horsetail/event.h"
#include <assert.h>

static HtEvent sEvents[HT_MAX_EVENTS] = {0};
static HtInt sEventHead = 0;
static HtInt sEventTail = 0;

void HtPostEvent(HtEvent *event)
{
    assert(event != NULL);
    sEvents[sEventHead] = *event;
    sEventHead = (sEventHead + 1) % HT_MAX_EVENTS;
}

HtEvent *HtPopEvent(void)
{
    HtEvent *result = NULL;
    
    if (sEventHead != sEventTail)
    {
        result = &sEvents[sEventTail];
        sEventTail = (sEventTail + 1) % HT_MAX_EVENTS;
    }

    return result;
}
