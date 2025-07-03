#include "horsetail/au.h"
#include "horsetail/impl.h"
#include "horsetail/math.h"

#include "horsetail_private.h"

#define AUDIO_BUFFER_SIZE       (4096 / 2)

i16 gAudioBuffer[AUDIO_BUFFER_SIZE] = {0};

void AuInit(void)
{
}

void AuUpdate(void)
{
    HtBool succeeded = HT_FALSE;
    f32 freq = 500.0;
    f32 sampleRate = 48000.0;

    for(usize i = 0; i < AUDIO_BUFFER_SIZE; i += 2)
    {
        f32 currentPos = 2.0 * HT_PI * (((f32) i) / (sampleRate/freq));
        i16 byte;
        byte = (i16) (HtSin(currentPos) * 16000.0);

        /* left speaker */
        gAudioBuffer[i] = byte;
        /* right speaker */
        gAudioBuffer[i + 1] = byte;
    }

    succeeded = ImplUploadAudio((u8 *) gAudioBuffer, sizeof(gAudioBuffer));
    HtAssert(succeeded);
}

