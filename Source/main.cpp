#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <cmath>
#include <memory>
#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

// if you use different OS, add your elif
#ifdef __APPLE__
#include <SDL2_Mixer/SDL_mixer.h>
#elif __linux__
#include <SDL2/SDL_mixer.h>
#endif

#include "Menager.h"




int main(int argc, char *argv[]) {
    Menager menager;
    menager.loadObjects();

menager.mainloop();

}