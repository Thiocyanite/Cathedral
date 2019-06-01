//
// Created by Julia on 2019-05-07.
//

#include "Menager.h"
#include <fstream>
#include <memory>
#include <stdlib.h>
#include <glm/glm.hpp>

#include "Audio/Audio.h"
#include "Observer.h"
#include "Shader.h"



void Menager::DrawScene() {
    auto time = static_cast<float>(glfwGetTime());
    glClearColor(sin(time), cos(time), 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
}



void Menager::key(){
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        observer->moveForward(0.1);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        observer->moveForward(-0.1);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        observer->moveAside(-0.05);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        observer->moveAside(0.05);
}


void Menager::loadObjects() {
    std::fstream objects, parameters;
#ifdef _WIN32

    objects.open("Paths_for_retardation_OS.txt", std::ios::in); //Couse Windows have insane paths
#else
    objects.open("Paths_for_normal_OS.txt", std::ios::in); //for *nix systems
#endif
    parameters.open("Positions.txt", std::ios::in); //in world
    if (objects.fail() || parameters.fail() ) //checks if both files are open
    {
        std::cerr<<"Couldn't open one of the important files 😫\n";
        exit(0);
    }
    std::shared_ptr<Object> loadingOne;
    glm::vec3 loadingParamether;
    std::string pathToObject, par[3];
    while (!objects.eof()){
        objects>>pathToObject;
        try{
            loadingOne=objLoad.loadObject(pathToObject.c_str()); //if the object is loaded, it's ok
            stableObjects.addObject(loadingOne);
            for (int i=0;i<3;i++){
                 parameters>>par[i];}
            positions.push_back(glm::vec3(atof(par[0].c_str()),atof(par[1].c_str()),atof(par[3].c_str())));
            for (int i=0;i<3;i++){
                parameters>>par[i];}
            rotations.push_back(glm::vec3(atof(par[0].c_str()),atof(par[1].c_str()),atof(par[3].c_str())));
            for (int i=0;i<3;i++){
                parameters>>par[i];}
            scales.push_back(glm::vec3(atof(par[0].c_str()),atof(par[1].c_str()),atof(par[3].c_str())));
        }
        catch (...){
            for (int i=0;i<9;i++){
                parameters>>par[0];} //we have to leave the paramethers if we don't have object
        }
    }
    objects.close();
    parameters.close();
}


void Menager::mainloop() {

    while (!glfwWindowShouldClose(window))
    {
        DrawScene();
        glfwPollEvents();
        key();
    }
}



Menager::Menager(GLFWwindow* _window) {
    window=_window;
    glfwSetWindowUserPointer(window, this);
    shader=new Shader();
    shader->loadProgram("vertexshader.glsl", "\0","fragmentshader.glsl");
    audi = new Audio();
    audi->playEpica();

}


Menager::~Menager() {
    delete audi;
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void Menager::stopMusic(){audi->stopaudio();};
void Menager::playEpica(){audi->playEpica();};
void Menager::playAfter(){audi->playAfter();};