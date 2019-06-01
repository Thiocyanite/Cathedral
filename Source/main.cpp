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


    if (!glfwInit()) {
        fprintf(stderr, "No GLFW 😢\n");
        exit(EXIT_FAILURE);
    }
    GLFWwindow* window;
    window = glfwCreateWindow(1920, 1080, "Cathedral", NULL, NULL);  //Creating a window in FullHD

    if (!glewInit()){
     std::cerr<<"No glew 🤯\n";
     exit(EXIT_FAILURE);
    }
    if (!window)
    {
        fprintf(stderr, "Even there's no Window[s], there's a problem 🤪 \n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    Menager menager(window);
    menager.loadObjects();

menager.mainloop();

}