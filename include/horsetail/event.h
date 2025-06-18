#ifndef _HORSETAIL_EVENT_H_
#define _HORSETAIL_EVENT_H_

#define HT_MAX_EVENTS           64

typedef enum
{
    HT_EVENT_NONE = 0,
    HT_EVENT_QUIT = 1,
    HT_EVENT_KEY_UP,
    HT_EVENT_KEY_DOWN,
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
    };
} HtEvent;

void HtPostEvent(HtEvent *event);
HtEvent *HtPopEvent(void);

#endif
