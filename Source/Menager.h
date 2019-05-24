//
// Created by Julia on 2019-05-07.
//

#ifndef OPENGLSETUP_MENAGER_H
#define OPENGLSETUP_MENAGER_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <cmath>

#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>


//if somebody is using different OS - add your elif
#ifdef __APPLE__
#include <SDL2_Mixer/SDL_mixer.h>
#elif __linux__
#include <SDL2/SDL_mixer.h>
#endif

#include "Audio/Audio.h"
#include "Object/ObjectMenager.h"
#include "Object/ObjectLoader.h"
#include "Observer.h"


class Menager {
private:
Audio *audi; //Audio system
    GLFWwindow* window; //Main window
    ObjectLoader objLoad;
    ObjectMenager stableObjects;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> rotations;
    std::vector<glm::vec3> scales;
    static Observer *observer;

public:
    Menager();
    ~Menager();
    void mainloop();
    void stopMusic(){audi->stopaudio();};
    void playEpica(){audi->playEpica();};
    void playAfter(){audi->playAfter();};
    void loadObjects();
    static void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods); //keyboard
};


#endif //OPENGLSETUP_MENAGER_H
