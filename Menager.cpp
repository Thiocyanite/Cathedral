//
// Created by Julia on 2019-05-07.
//

#include "Menager.h"
#include <fstream>
#include <memory>
#include <stdlib.h>
#include <glm/glm.hpp>


void Menager::loadObjects(std::string &fileWithPaths, std::string &fileWithParameters) {
    std::fstream objects, parameters;
    objects.open(fileWithPaths.c_str(), std::ios::in);
    parameters.open(fileWithParameters.c_str(), std::ios::in);
    if (objects.fail() || parameters.fail() )
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



}


void Menager::mainloop() {



    while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
    {
        auto time = static_cast<float>(glfwGetTime());
        glClearColor(sin(time), cos(time), 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
        glfwSwapBuffers(window);
    }

}



Menager::Menager() {
    if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
        fprintf(stderr, "Nie można zainicjować GLFW.\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(500, 500, "Cathedral", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

    if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
    {
        fprintf(stderr, "Nie można utworzyć okna.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
    glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

    if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
        fprintf(stderr, "Nie można zainicjować GLEW.\n");
        exit(EXIT_FAILURE);
    }
    audi = new Audio();
    audi->playEpica();
}




Menager::~Menager() {
    delete audi;
    glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
    glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
    exit(EXIT_SUCCESS);
}