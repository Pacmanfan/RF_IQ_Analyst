#ifndef AUDIO_H
#define AUDIO_H

#include <alsa/asoundlib.h>

/*
    this is a utility class for configuring the audio system through alsa
    We should also support some basic wav recording or playback thoruigh here.

*/
#define AUDIO_BUFFER_SIZE 4096 // for audio buffer

void SetupAudio();
void CloseAudio();
bool SoundConfigured();//{return soundconfigured;}
bool PlayAudio(float *buffer, int len);


#endif // AUDIO_H
