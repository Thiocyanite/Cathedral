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
#include "Menager.h"

int main(int argc, char *argv[]) {
Menager menager;
menager.mainloop();

}