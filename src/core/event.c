#include "horsetail/defs.h"
#include "horsetail/event.h"
#include <assert.h>

static HtEvent gEvents[HT_MAX_EVENTS] = {0};
static i32 gEventHead = 0;
static i32 gEventTail = 0;

void HtPostEvent(HtEvent *event)
{
    assert(event != NULL);
    gEvents[gEventHead] = *event;
    gEventHead = (gEventHead + 1) % HT_MAX_EVENTS;
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
