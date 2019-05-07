//
// Created by Julia on 2019-05-07.
//

#include "Audio.h"

#include <iostream>

Audio::Audio(){
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024); //Only with two channels!
    audio[0]=Mix_LoadMUS("mea.mp3");
    audio[1]=Mix_LoadMUS("indygo.mp3");


};

Audio::~Audio(){
    Mix_CloseAudio();
}

void Audio::playEpica(){
    if (audio[1]!=nullptr)
        Mix_PlayMusic(audio[1], -1);
    else {std::cerr<<"😭 No Epica\n";}
}

void Audio::playAfter(){
    if (audio[0]!=nullptr)
        Mix_PlayMusic(audio[0], -1);
    else {std::cerr<<"😢 No After Forever\n";
    }
}


void Audio::stopaudio(){
    Mix_PauseMusic();
}
