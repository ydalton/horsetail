#define _ISOC99_SOURCE
#include <stdio.h>

#include "horsetail/horsetail.h"
#include "horsetail/impl.h"
#include "horsetail/vg.h"

#include <stdio.h>
#include <stdarg.h>

static void HtpProcessEvents(void);
static HtBool HtpSystemEventHandler(HtEvent *event);
static void HtpShutdown(int code);

static HtBool gRunning = HT_TRUE;
static HtEventHandlerProc gEventHandlers[] = {
    HtpSystemEventHandler,
    LgHandleEvent,
};

void HtMain(void)
{
    ImplInit();
    VgInit();

    while (gRunning)
    {
        ImplBeginLoop();
        ImplGetEvents();
        HtpProcessEvents();
        LgUpdate();
        VgUpdate();
        ImplFinishUpdate();
    }

    HtpShutdown(0);
}

static void HtpProcessEvents(void)
{
    HtEvent *event = NULL;

    while ((event = HtPopEvent()))
    {
        size_t i;

        HtAssert(event->type != HT_EVENT_NONE);

        for(i = 0; i < HT_ARRAY_SIZE(gEventHandlers); i++)
        {
            HtEventHandlerProc eventHandlerProc;

            eventHandlerProc = gEventHandlers[i];

            if (eventHandlerProc(event))
            {
                /* handled */
                break;
            }
        }
    }
}

static HtBool HtpSystemEventHandler(HtEvent *event)
{
    HtBool handled = HT_FALSE;

    /* this event handler only handles system events. */
    if (event->type < HT_EVENT_SYSTEM)
    {
        return HT_FALSE;
    }
    
    switch(event->type)
    {
    case HT_EVENT_QUIT:
        gRunning = HT_FALSE;
        break;
    case HT_EVENT_RESIZE:
        {
            VgDisplaySize displaySize = {0};

            HtAssert(event->resize.newWidth != 0 && event->resize.newHeight != 0);

            displaySize.width = event->resize.newWidth;
            displaySize.height = event->resize.newHeight;

            VgSetDisplaySize(&displaySize);
        }
        break;
    default:
        break;
    }

    return handled;
}

void HtError(const char *fmt, ...)
{
    char buf[512] = {0};
    usize size = HT_ARRAY_SIZE(buf);

    va_list args;
    va_start (args, fmt);
    vsnprintf(buf, size, fmt, args);
    va_end(args);

    HtShowError(buf);

    HtpShutdown(-1);
}

void HtShowError(const char *buf)
{
    ImplShowError(buf);
}

void HtLog(const char *fmt, ...)
{
    char buf[512] = {0};
    usize size = HT_ARRAY_SIZE(buf);

    va_list args;
    va_start (args, fmt);
    vsnprintf(buf, size, fmt, args);
    va_end(args);

    /* TODO: change this */
    puts(buf);
}

static void HtpShutdown(int code)
{
    VgShutdown();
    ImplShutdown(code);
}
