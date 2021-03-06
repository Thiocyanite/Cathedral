//
// Created by Julia on 2019-05-07.
//

#include "Menager.h"
#include <fstream>
#include <memory>
#include <stdlib.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "lodepng.h"

#include "Audio/Audio.h"
#include "Observer.h"
#include "Object/AnimatedObject.h"
#include "glCall.h"

void Menager::DrawScene() {
    auto time = static_cast<float>(glfwGetTime());
    glClearColor(0.0f, 0.05f, 0.2f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int width, height;
    glfwGetWindowSize(window, &width, &height);
    float aspectRatio = (float)width/(float)height;

    glm::mat4 M = glm::mat4(1);
              M = glm::translate(M, glm::vec3(-2.f,-4.0f,-10.f) );
    glm::mat4 V = observer->calculateLookAtMatrix();
    glm::mat4 P = glm::perspective(glm::radians(70.f), aspectRatio, 0.1f, 500.f);
    glm::mat4 MVP = P * V * M;

    shaderTextured.use();
    glUniform1i(shaderTextured.getU("colorMap"), 0);
    testMat->bind();
    float angle=10;

    for (int meshID=0; meshID<texObj.size(); meshID++) {
        for (auto &mesh : texObj.getModel(meshID)->getMeshes()) {
            mesh->bindVAO();
            M = glm::mat4(1);


            //M=glm::rotate(M, angle, texObj.getRotation(meshID));
            //M = glm::scale(M, texObj.getScale(meshID)); //now objects can be scaled
            M = glm::translate(M, texObj.getPosition(meshID));
            MVP = P * V * M;
            glUniformMatrix4fv(shaderTextured.getU("M"), 1, GL_FALSE, glm::value_ptr(M)) ;
            glUniformMatrix4fv(shaderTextured.getU("MVP"), 1, GL_FALSE, glm::value_ptr(MVP)) ;

            glCall( glDrawElements(GL_TRIANGLES, mesh->indicies.size(), GL_UNSIGNED_INT, nullptr) );
        }
    }

    shaderTextured.unuse();
    shader.use();
    for (int meshID=0; meshID<obj.size(); meshID++) {
        for (auto &mesh : obj.getModel(meshID)->getMeshes()) {
            mesh->bindVAO();
            M = glm::mat4(1);
            //M=glm::rotate(M, angle, texObj.getRotation(meshID));
            //M = glm::scale(M, texObj.getScale(meshID)); //now objects can be scaled
            M = glm::translate(M, texObj.getPosition(meshID));
            MVP = P * V * M;
            glUniformMatrix4fv(shader.getU("M"), 1, GL_FALSE, glm::value_ptr(M)) ;
             glUniformMatrix4fv(shader.getU("MVP"), 1, GL_FALSE, glm::value_ptr(MVP)) ;

            glCall( glDrawElements(GL_TRIANGLES, mesh->indicies.size(), GL_UNSIGNED_INT, nullptr) );
        }
    }
    for (auto& mesh : observer->character->getMeshes()){
        mesh->bindVAO();
        M = glm::mat4(1);
        M = glm::translate(M, observer->position);
         switch (observer->Orientation) {
             case 'F':
                 break;
             case 'B':
                 M=glm::rotate(M, 60.0f, glm::vec3(0,1,0));
                 break;
             case 'L':
                 M=glm::rotate(M,90.0f, glm::vec3(0,1,0));
                 break;
             case 'R':
                 M=glm::rotate(M,30.0f, glm::vec3(0,1,0));
                 break;

         } //Rotacja postaci zależna od kąta padania



                MVP = P * V * M;
        glUniformMatrix4fv(shader.getU("M"), 1, GL_FALSE, glm::value_ptr(M)) ;
         glUniformMatrix4fv(shader.getU("MVP"), 1, GL_FALSE, glm::value_ptr(MVP)) ;

        glDrawElements(GL_TRIANGLES, mesh->indicies.size(), GL_UNSIGNED_INT, nullptr) ;
    }
    //shaderTextured.unuse();
    shader.unuse();
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
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        playEpica();
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        playAfter();
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        std::cout<<observer->position.x<<" "<<observer->position.y<<" "<<observer->position.z<<"\n";

}


#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
void Menager::loadObjects() {

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
    std::shared_ptr<Model> loadingOne;
    glm::vec3 loadingPos, loadingRot, loadingScale;
    std::string pathToObject, par[3];
    char Mode;
    int numberOfItems;
    while (!objects.eof()){
        objects>>pathToObject;
        objects>>Mode;
        if(!pathToObject.empty()){
            try{

                loadingOne=objLoad.loadObject(pathToObject); //if the object is loaded, it's ok
                parameters>>numberOfItems;
                for (int j=0; j<numberOfItems;j++)
                {
                    for (int i = 0; i < 3; i++)
                        parameters >> par[i];
                    loadingPos = glm::vec3(atof(par[0].c_str())/10, atof(par[1].c_str())/10, atof(par[3].c_str())/10);

                    for (int i = 0; i < 3; i++)
                        parameters >> par[i];
                    loadingRot = glm::vec3(atof(par[0].c_str()), atof(par[1].c_str()), atof(par[3].c_str()));

                    for (int i = 0; i < 3; i++)
                        parameters >> par[i];
                    loadingScale = glm::vec3(atof(par[0].c_str())/10, atof(par[1].c_str())/10, atof(par[3].c_str())/10);
                    if (Mode=='N') //Non-textured
                        obj.addObject(loadingOne, loadingPos, loadingRot, loadingScale);
                    else
                        texObj.addObject(loadingOne,loadingPos,loadingRot,loadingScale);

                }
            }
            catch (...){
                for (int i=0;i<9;i++){
                    parameters>>par[0];} //we have to leave the paramethers if we don't have object
            }
        }
    }
    objects.close();
    parameters.close();
    loadingOne=objLoad.loadObject("Models/woman/woman.obj");
    observer->load_char(loadingOne);

    testMat = materialLoader.load("Textures/Mat1.mat");
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

    shader.loadProgram("Shaders/vertex.glsl", "","Shaders/fragment.glsl");

    shaderTextured.loadProgram("Shaders/vertex.glsl", "","Shaders/fragmentTextured.glsl");

    audi = new Audio();
    audi->playAfter();
    testMat= std::make_shared<Material>();

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