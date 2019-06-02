//
// Created by Julia on 2019-05-07.
//

#include "Menager.h"
#include <fstream>
#include <memory>
#include <stdlib.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Audio/Audio.h"
#include "Observer.h"
#include "Shader.h"

#include "Object/AnimatedObject.h"

void Menager::DrawScene() {
    auto time = static_cast<float>(glfwGetTime());
    glClearColor(sin(time), cos(time), 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int width, height;
    glfwGetWindowSize(window, &width, &height);
    float aspectRatio = (float)width/(float)height;

    glm::mat4 M = glm::mat4(1);
              M = glm::translate(M, glm::vec3(-2.f,-4.0f,-10.f) );
              //M = glm::rotate(M, time, glm::vec3(0,1,0));
              M = glm::scale(M, glm::vec3(0.5f));
    glm::mat4 V = glm::lookAt(glm::vec3( 0, 0, 0), // position
                              glm::vec3( 0, 0,-1),
                              glm::vec3( 0, 1, 0));
    /* Draw from 0.1 to 10.f away from camera plane*/
    glm::mat4 P = glm::perspective(glm::radians(45.f), aspectRatio, 0.1f, 100.f);
    glm::mat4 MVP = P * V * M;

    shader->use();
    glUniformMatrix4fv(shader->getU("M"), 1, GL_FALSE, glm::value_ptr(M) );
    glUniformMatrix4fv(shader->getU("MVP"), 1, GL_FALSE, glm::value_ptr(MVP) );
    for(int i = 0; i < cowboy->getMeshes().size(); i ++){
        glUniform1f(shader->getU("interpolationFactor"), cowboy->getInterpolationFactor(time));
//        cowboy->keyframes[200].pose[i]->initVAO();
//        cowboy->keyframes[200].pose[i]->reloadVAO();
//        cowboy->keyframes[200].pose[i]->bindVAO();

        cowboy->bindCurrentPose(time, i);

    glDrawElements(GL_TRIANGLES, cowboy->keyframes[0].pose[i]->indicies.size(), GL_UNSIGNED_INT, nullptr);
    }


    cowboy->unbind();
    shader->unuse();

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


#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
void Menager::loadObjects() {

    /*TEST ANIMATED OBJECT LOADING*/
    cowboy = objLoad.loadAnimation("Models/Cowboy/HowToLoad.txt");

    /*TEST ANIMATED OBJECT LOADING*/
    std::fstream objects, parameters;
#ifdef _WIN32
    objects.open("Paths_for_retarded_OS.txt", std::ios::in); //Cause Windows have insane paths
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
        //An empty file will load an empty string once
        if(!pathToObject.empty()){
            try{
                loadingOne=objLoad.loadObject(pathToObject); //if the object is loaded, it's ok
                stableObjects.addObject(loadingOne);

                for (auto &i : par)
                     parameters >> i;

                positions.emplace_back(atof(par[0].c_str()), atof(par[1].c_str()), atof(par[3].c_str()) );

                for (auto &i : par)
                    parameters >> i;

                rotations.emplace_back(atof(par[0].c_str()), atof(par[1].c_str()), atof(par[3].c_str()) );

                for (auto &i : par)
                    parameters >> i;

                scales.emplace_back(atof(par[0].c_str()), atof(par[1].c_str()), atof(par[3].c_str()) );
            }
            catch (...){
                for (int i=0;i<9;i++){
                    parameters>>par[0];} //we have to leave the paramethers if we don't have object
            }
        }
    }
    objects.close();
    parameters.close();
}
#pragma clang diagnostic pop /* Drop clang waring about atof not checking formatting. */


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
    shader->loadProgram("vertexshader.glsl", "","fragmentshader.glsl");
    audi = new Audio();
    audi->playEpica();

}


Menager::~Menager() {
    delete audi;
    shader->freeProgram();
    delete shader;


    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void Menager::stopMusic(){audi->stopaudio();};
void Menager::playEpica(){audi->playEpica();};
void Menager::playAfter(){audi->playAfter();};