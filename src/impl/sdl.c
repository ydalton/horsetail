#include <SDL3/SDL.h>
#include <stdlib.h>

#include "horsetail/core.h"
#include "horsetail/event.h"
#include "horsetail/impl.h"

SDL_Window *gWindow = NULL;

static void ImplpGetEvents(void);
static HtKey ImplpGetKeycode(SDL_Keycode keycode);

int main(int argc, char **argv)
{
    /* TODO: to be used later */
    (void) argc;
    (void) argv;

    HtMain();

    return 0;
}

void ImplInit(void)
{
    SDL_Init(SDL_INIT_VIDEO);
    gWindow = SDL_CreateWindow(IMPL_DEFAULT_DISPLAY_NAME,
                               IMPL_DEFAULT_DISPLAY_WIDTH,
                               IMPL_DEFAULT_DISPLAY_HEIGHT,
                               SDL_WINDOW_OPENGL);

    HtAssert(gWindow != NULL);

    /* we want OpenGL ES 2.0 */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetSwapInterval(1);

    SDL_GL_CreateContext(gWindow);
}

void ImplBeginLoop(void)
{
    ImplpGetEvents();
}

/* translate events from implementation to events */
static void ImplpGetEvents(void)
{
    SDL_Event sdlEvent;

    while (SDL_PollEvent(&sdlEvent))
    {
        HtBool postEvent = HT_TRUE;
        HtEvent htEvent = {0};

        switch(sdlEvent.type)
        {
        case SDL_EVENT_KEY_UP:
        case SDL_EVENT_KEY_DOWN:
            {
                HtKey key;

                key = ImplpGetKeycode(sdlEvent.key.key);

                if (key == HT_KEY_NONE)
                {
                    postEvent = HT_FALSE;
                }

                if (sdlEvent.type == SDL_EVENT_KEY_DOWN)
                {
                    htEvent.type = HT_EVENT_KEY_DOWN;
                }
                else
                {
                    htEvent.type = HT_EVENT_KEY_UP;
                }

                htEvent.keyPress.key = key;
            }
            break;
        case SDL_EVENT_QUIT:
            htEvent.type = HT_EVENT_QUIT;
            break;
        default:
            postEvent = HT_FALSE;
            break;
        }

        if (postEvent)
        {
            HtPostEvent(&htEvent);
        }
    }

}

static HtKey ImplpGetKeycode(SDL_Keycode sdlKeyCode)
{
    HtKey htKey = HT_KEY_NONE;

    switch (sdlKeyCode)
    {
        case SDLK_W:
            htKey = HT_KEY_W;
            break;
        case SDLK_A:
            htKey = HT_KEY_A;
            break;
        case SDLK_S:
            htKey = HT_KEY_S;
            break;
        case SDLK_D:
            htKey = HT_KEY_D;
            break;
        case SDLK_UP:
            htKey = HT_KEY_UP;
            break;
        case SDLK_DOWN:
            htKey = HT_KEY_DOWN;
            break;
        case SDLK_LEFT:
            htKey = HT_KEY_LEFT;
            break;
        case SDLK_RIGHT:
            htKey = HT_KEY_RIGHT;
            break;
        case SDLK_ESCAPE:
            htKey = HT_KEY_ESC;
            break;
    }

    return htKey;
}

void ImplFinishUpdate()
{
    SDL_GL_SwapWindow(gWindow);
}

void ImplShutdown(int code)
{
    SDL_DestroyWindow(gWindow);

    exit(code);
}
