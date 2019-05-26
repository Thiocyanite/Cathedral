//
// Created by Julia on 2019-05-07.
//

#include "Menager.h"
#include <fstream>
#include <memory>
#include <stdlib.h>
#include <glm/glm.hpp>


void Menager::DrawScene() {
    auto time = static_cast<float>(glfwGetTime());
    glClearColor(sin(time), cos(time), 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
}

void Menager::keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
auto  *menager= reinterpret_cast<Menager*>(glfwGetWindowUserPointer(window));
if (action==GLFW_PRESS){
    if (key==GLFW_KEY_A) //example action
        menager->playAfter();

}
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
            std::cout<<"In the loop\n";
            loadingOne=objLoad.loadObject(pathToObject.c_str()); //if the object is loaded, it's ok
            std::cout<<"loaded\n";
            stableObjects.addObject(loadingOne);
            std::cout<<"Object added\n";
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
    }
}



Menager::Menager() {
    if (!glfwInit()) {
        fprintf(stderr, "No GLFW 😢\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(1920, 1080, "Cathedral", NULL, NULL);  //Creating a window in FullHD
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, keyboard);
    if (!window)
    {
        fprintf(stderr, "Even there's no Window[s], there's a problem 🤪 \n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    audi = new Audio();
    audi->playEpica();

}


Menager::~Menager() {
    delete audi;
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

