#ifndef _HORSETAIL_EVENT_H_
#define _HORSETAIL_EVENT_H_

#ifndef _HORSETAIL_H_
#error "Do not include this file seperately. Include horsetail.h"
#endif

#define HT_MAX_EVENTS           64

typedef enum
{
    HT_EVENT_NONE = 0,
    HT_EVENT_KEY_UP,
    HT_EVENT_KEY_DOWN,

    /* system events */
    HT_EVENT_SYSTEM = 0x1000,
    HT_EVENT_QUIT,
    HT_EVENT_RESIZE,
} HtEventType;

typedef enum
{
    HT_KEY_NONE = 0,
    HT_KEY_W = 1,
    HT_KEY_A,
    HT_KEY_S,
    HT_KEY_D,
    HT_KEY_UP,
    HT_KEY_DOWN,
    HT_KEY_LEFT,
    HT_KEY_RIGHT,
    HT_KEY_ESC,
} HtKey;

typedef struct {
    HtEventType type;

    union
    {
        struct
        {
            HtKey key;
        } keyPress;
        struct
        {
            i32 newWidth;
            i32 newHeight;
        } resize;
    };
} HtEvent;

void HtPostEvent(HtEvent *event);
HtEvent *HtPopEvent(void);

#define HtPostQuitEvent()           \
    {                               \
        HtEvent event = {0};        \
        event.type = HT_EVENT_QUIT; \
        HtPostEvent(&event);        \
    }

typedef HtBool (*HtEventHandlerProc)(HtEvent *);

#endif
