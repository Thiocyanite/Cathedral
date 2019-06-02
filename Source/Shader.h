//
// Created by Julia on 2019-05-12.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>

#ifndef OPENGLSETUP_SHADER_H
#define OPENGLSETUP_SHADER_H


class Shader {
public:
    unsigned int vertexShader;
    std::string vertexShaderFileName = "Source/vertexshader.glsl";
    std::string vertexShaderSource;
    Shader();
    void readVertexShaderSource();
    void compileShader();
};


#endif //OPENGLSETUP_SHADER_H
