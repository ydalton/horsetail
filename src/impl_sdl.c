#include <SDL3/SDL.h>
#include <stdlib.h>

#include "horsetail/horsetail.h"
#include "horsetail_private.h"
#include "horsetail/impl.h"
#include "horsetail/vg.h"

SDL_Window *gWindow = NULL;
SDL_GLContext gContext = NULL;
SDL_AudioStream *gAudioStream = NULL;

static HtKey ImplpGetKeycode(SDL_Keycode keycode);
static void ImplpInitWindow(void);
static void ImplpInitOpenGL(void);
static void ImplpInitAudio(void);

/* todo: change asserts to  */
void ImplInit(void)
{

    SDL_Init(SDL_INIT_AUDIO);

    ImplpInitWindow();
    HtLog("Impl (SDL): successfully created window\n");

    ImplpInitOpenGL();
    HtLog("Impl (SDL): successfully created OpenGL ES context\n");

    ImplpInitAudio();
    HtLog("Impl (SDL): successfully opened audio device\n");

    HtLog("Impl (SDL): initialized\n");
}

static void ImplpInitWindow(void)
{
    gWindow = SDL_CreateWindow(VG_DISPLAY_DEFAULT_NAME,
                               VG_DISPLAY_DEFAULT_WIDTH,
                               VG_DISPLAY_DEFAULT_HEIGHT,
                               SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    HtAssert(gWindow != NULL);
}

static void ImplpInitOpenGL(void)
{
    /* we want OpenGL ES 2.0 */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetSwapInterval(1);

    gContext = SDL_GL_CreateContext(gWindow);
    HtAssert(gContext != NULL);
}

static void ImplpInitAudio(void)
{
    SDL_AudioSpec spec = {0};
    spec.format = SDL_AUDIO_S16;
    spec.channels = 2;
    spec.freq = 48000;

    gAudioStream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,
                                             &spec,
                                             NULL,
                                             NULL);

    if (gAudioStream == NULL)
    {
        HtError("SDL: Failed to open audio device stream: %s\n", SDL_GetError());
    }
}

void ImplBeginLoop(void)
{
}

/* translate events from implementation to events */
void ImplGetEvents(void)
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
        case SDL_EVENT_WINDOW_RESIZED:
            htEvent.type = HT_EVENT_RESIZE;
            htEvent.resize.newWidth = sdlEvent.window.data1;
            htEvent.resize.newHeight = sdlEvent.window.data2;
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

HtBool ImplUploadAudio(u8 *data, usize size)
{
    HtBool succeeded = HT_FALSE;

    succeeded = SDL_PutAudioStreamData(gAudioStream, data, size);

    return succeeded;
}

void ImplShutdown(int code)
{
    SDL_DestroyAudioStream(gAudioStream);
    SDL_GL_DestroyContext(gContext);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();

    exit(code);
}
