#include <stdio.h>

#include "horsetail/core.h"
#include "horsetail/impl.h"
#include "horsetail/event.h"
#include "horsetail/vg.h"
#include "horsetail/util.h"

#include <stdio.h>
#include <stdarg.h>

HtBool gRunning = HT_TRUE;

static void HtpInit();
static void HtpProcessEvents(void);
static void HtpShutdown(int code);

void HtMain(void)
{
    HtpInit();

    while (gRunning)
    {
        ImplBeginLoop();
        HtpProcessEvents();
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
        assert (event->type != HT_EVENT_NONE);
        switch (event->type)
        {
        case HT_EVENT_KEY_DOWN:
            if (event->keyPress.key == HT_KEY_ESC)
            {
                gRunning = HT_FALSE;
            }
            break;
        case HT_EVENT_QUIT:
            gRunning = HT_FALSE;
            break;
        default:
            break;
        }
    }
}

void HtError(const char *fmt, ...)
{
    va_list args;
    va_start (args, fmt);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);

    HtpShutdown(-1);
}

static void HtpShutdown(int code)
{
    ImplShutdown(code);
}
