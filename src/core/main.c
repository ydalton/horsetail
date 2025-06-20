#define _ISOC99_SOURCE
#include <stdio.h>

#include "horsetail/horsetail.h"
#include "horsetail/impl.h"
#include "horsetail/vg.h"

#include <stdio.h>
#include <stdarg.h>

static void HtpInit();
static void HtpProcessEvents(void);
static HtBool HtpMainEventHandler(HtEvent *event);
static void HtpShutdown(int code);

static HtBool gRunning = HT_TRUE;
static HtEventHandlerProc gEventHandlers[] = {
    HtpMainEventHandler,
    LgHandleEvent,
};

void HtMain(void)
{
    HtpInit();

    while (gRunning)
    {
        ImplBeginLoop();
        HtpProcessEvents();
        LgUpdate();
        VgUpdate();
        ImplFinishUpdate();
    }

    HtpShutdown(0);
}

static void HtpInit(void)
{
    ImplInit();
    VgInit();
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

static HtBool HtpMainEventHandler(HtEvent *event)
{
    if (event->type == HT_EVENT_QUIT)
    {
        gRunning = HT_FALSE;
        return HT_TRUE;
    }

    return HT_FALSE;
}

void HtError(const char *fmt, ...)
{
    char buf[512] = {0};
    usize size = HT_ARRAY_SIZE(buf);

    va_list args;
    va_start (args, fmt);
    vsnprintf(buf, size, fmt, args);
    va_end(args);

    ImplShowError(buf);

    HtpShutdown(-1);
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
