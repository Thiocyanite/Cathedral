//
// Created by Julia on 2019-05-07.
//

#ifndef OPENGLSETUP_AUDIO_H
#define OPENGLSETUP_AUDIO_H

#include <SDL2_Mixer/SDL_mixer.h>


class Audio{
private:
    Mix_Music *audio[2];


public:
    Audio();
    ~Audio();
    void playEpica();
    void playAfter();
    void playall();
    void stopaudio();
};
#endif //OPENGLSETUP_AUDIO_H
