//
// Created by Julia on 2019-05-12.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include "Shader.h"


void Shader::loadProgram(std::string vertex, std::string geometry, std::string fragment) {
    loadShader(vertex, GL_VERTEX_SHADER);
    if (geometry!="\0")
        loadShader(geometry, GL_GEOMETRY_SHADER);
    loadShader(fragment, GL_FRAGMENT_SHADER);

    freeProgram();
}

void Shader::loadShader(std::string path, GLuint ShaderType) {
    std::string shaderSourceCode = readFile(path);
    GLuint shaderName = glCreateShader(ShaderType);

    const char *const_source_code_ptr = shaderSourceCode.c_str();
    glShaderSource(shaderName, 1, &const_source_code_ptr, NULL);
}

std::string Shader::readFile(std::string path) {
    std::ifstream file(path.c_str());
    if (file.is_open()) {
        std::stringstream fileBuffer;
        fileBuffer << file.rdbuf();
        return fileBuffer.str();
    }
    else std::cerr<<"Zla sciezka 🤯\n";

}

void Shader::freeShaders() {
    while (numShaders>=1){
        glDeleteShader(shaderNames[--numShaders]);
    }
}
void Shader::freeProgram() {
    glDeleteProgram(programName);
}

GLint Shader::getU(const std::string uniformName) {
    GLint uniformLocation = 0;
    auto locationContainer = uniformLocationsMap.find(uniformName);
    if(locationContainer == uniformLocationsMap.end()){
        uniformLocation = glGetUniformLocation(programName, uniformName.c_str());
        uniformLocationsMap.emplace(uniformName, uniformLocation);
    }
    else {
        uniformLocation = locationContainer->second;
    }
    return uniformLocation;
}