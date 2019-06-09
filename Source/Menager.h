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

#include "Object/ObjectMenager.h"
#include "Observer.h"
#include "Object/ModelMenager.h"
#include "Object/ObjectLoader.h"
#include "Audio/Audio.h"



/* Those two */
class Shader;

class Menager {
private:
    Audio *audi; //Audio system
    GLFWwindow* window; //Main window
    //std::shared_ptr<AnimatedObject> cowboy;
    ObjectLoader objLoad;
    std::vector<GLuint> textures;
    ObjectMenager obj;
    Observer *observer = new Observer();
    Shader *shader;

public:
    Menager(GLFWwindow* _window);
    ~Menager();
    void mainloop();
    void stopMusic();
    void playEpica();
    void playAfter();
    void loadObjects();
    void DrawScene();
    void key();
};



#endif //OPENGLSETUP_MENAGER_H
