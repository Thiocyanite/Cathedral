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

#include <SDL2_mixer/SDL_mixer.h>
#include "Audio.h"

class Menager {
private:
Audio *audi; //Audio system
    GLFWwindow* window; //Main window
public:
    Menager();
    ~Menager();
    void mainloop();
};


#endif //OPENGLSETUP_MENAGER_H
