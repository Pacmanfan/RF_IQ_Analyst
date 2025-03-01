#include "audio_util.h"

snd_pcm_t *playback_handle = 0;
bool soundconfigured = false;


void SetupAudio()
{
    int err = 0;

    if ((err = snd_pcm_open(&playback_handle, "default", SND_PCM_STREAM_PLAYBACK, 0)) < 0)
    {
                    printf("Playback open error: %s\n", snd_strerror(err));
                    return;
    }
    if ((err = snd_pcm_set_params(playback_handle,
                                  SND_PCM_FORMAT_S16_LE ,
                                  SND_PCM_ACCESS_RW_INTERLEAVED,
                                  1,
                                  48000,
                                  0,
                                  500000)) < 0)
    {   /* 0.5sec */
            return;
    }
    soundconfigured = true;
}

/*
    play back sound, must be less than AUDIO_BUFFER_SIZE in length
*/

bool PlayAudio(float *buffer, int len)
{
    static short sbuf[AUDIO_BUFFER_SIZE];
    if(!soundconfigured)
        return false;

    //scale it from -1 -> 1 to -32768 -> 32768
    for(int c = 0;  c < len; c++)
    {
        sbuf[c] = (short)(buffer[c] * 50.0);
    }
    //write it to the audio device
    int frames = snd_pcm_writei (playback_handle, sbuf, AUDIO_BUFFER_SIZE);
    if(frames < 0) // try to recover
         frames = snd_pcm_recover(playback_handle, frames, 0);

    return true;
}

bool SoundConfigured()
{
    if (playback_handle == 0)
        return false;
    return soundconfigured;
}

void CloseAudio()
{
    if (playback_handle == 0)
        return;
    if(soundconfigured)
    {
        //close the audio device
        snd_pcm_close(playback_handle);
        playback_handle = 0;
        soundconfigured = false;
    }
}
