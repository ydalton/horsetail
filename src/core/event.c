#include "horsetail/defs.h"
#include "horsetail/event.h"
#include <assert.h>

static HtEvent gEvents[HT_MAX_EVENTS] = {0};
static HtInt gEventHead = 0;
static HtInt gEventTail = 0;

void HtPostEvent(HtEvent *event)
{
    assert(event != NULL);
    gEvents[gEventHead] = *event;
    gEventHead = (gEventHead + 1) % HT_MAX_EVENTS;
}

void HtPostQuitEvent(void)
{
    HtEvent event = {0};
    event.type = HT_EVENT_QUIT;
    HtPostEvent(&event);
}

HtEvent *HtPopEvent(void)
{
    HtEvent *result = NULL;
    
    if (gEventHead != gEventTail)
    {
        result = &gEvents[gEventTail];
        gEventTail = (gEventTail + 1) % HT_MAX_EVENTS;
    }

    return result;
}
