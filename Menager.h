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
#include "ObjectMenager.h"
#include "ObjectLoader.h"


class Menager {
private:
Audio *audi; //Audio system
    GLFWwindow* window; //Main window
    ObjectLoader objLoad;
    ObjectMenager stableObjects;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> rotations;
    std::vector<glm::vec3> scales;
public:
    Menager();
    ~Menager();
    void mainloop();
    void stopMusic(){audi->stopaudio();};
    void playEpica(){audi->playEpica();};
    void playAfter(){audi->playAfter();};
    void loadObjects(std::string &fileWithPaths, std::string &fileWithParameters);
};


#endif //OPENGLSETUP_MENAGER_H
