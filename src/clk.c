#include "horsetail/clk.h"
#include "horsetail/impl.h"

struct {
    HtBool initialized;
    i32 ticks;
    f32 deltaTime;
    f32 lastTime;
} clk = {0};

void ClkInit(void)
{
    HtAssert(clk.initialized == HT_FALSE);

    /* set the initial clock */
    clk.lastTime = ImplGetClockTime();

    clk.initialized = HT_TRUE;
}

void ClkUpdate(void)
{
    f32 lastTime = ImplGetClockTime();
    f32 deltaTime = (lastTime - clk.lastTime);

    clk.lastTime = lastTime;
    clk.deltaTime = deltaTime;
    clk.ticks++;
}

f32 ClkGetDeltaTime(void)
{
    return clk.deltaTime;
}

i32 ClkGetTicks(void)
{
    return clk.ticks;
}

f32 ClkGetFPS(void)
{
    return 1.0 / clk.deltaTime;
}
