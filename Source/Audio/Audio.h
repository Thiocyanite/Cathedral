//
// Created by Julia on 2019-05-07.
//

#ifndef OPENGLSETUP_AUDIO_H
#define OPENGLSETUP_AUDIO_H

#ifdef __APPLE__
#include <SDL2_Mixer/SDL_mixer.h>
#elif __linux__
#include <SDL2/SDL_mixer.h>
#endif

class Audio{
private:
    Mix_Music *audio[2];


public:
    Audio();
    ~Audio();
    void playEpica();
    void playAfter();
    void stopaudio();
};
#endif //OPENGLSETUP_AUDIO_H
