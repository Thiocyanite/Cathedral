//
// Created by Julia on 2019-05-12.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "Shader.h"

void Shader::loadProgram(std::string vertex, std::string geometry, std::string fragment) {
    loadShader(vertex, GL_VERTEX_SHADER);
    if (!geometry.empty())
        loadShader(geometry, GL_GEOMETRY_SHADER);
    loadShader(fragment, GL_FRAGMENT_SHADER);

    programName = glCreateProgram();
    for(int i = 0; i < numShaders; i ++)
        glAttachShader(programName, shaderNames[i]);

    glBindFragDataLocation(programName, 0, "out_Color");

    glLinkProgram(programName);

    GLint status;
    glGetProgramiv(programName, GL_LINK_STATUS, &status);
    if(status == GL_FALSE){
        GLint consolidationLogSize;
        glGetProgramiv(programName, GL_INFO_LOG_LENGTH, &consolidationLogSize);
        std::vector<GLchar> consolidationLog(consolidationLogSize);
        glGetProgramInfoLog(programName, consolidationLogSize, &consolidationLogSize, &consolidationLog[0]);

        //TODO: add exception
        std::cerr << "=== SHADER PROGRAM CONSOLIDATION ERROR ===\n"
                     + std::string(consolidationLog.begin(), consolidationLog.end()) + "\n";
        exit(1);
    }

    freeShaders();
}

void Shader::loadShader(const std::string& path, GLuint ShaderType) {
    std::string shaderSourceCode = readFile(path.c_str());
    GLuint shaderName = glCreateShader(ShaderType);

    const char *const_source_code_ptr = shaderSourceCode.c_str();
    glShaderSource(shaderName, 1, &const_source_code_ptr, NULL);

    glCompileShader(shaderName);

    /*Check for errors*/
    GLint success = 0;
    glGetShaderiv(shaderName, GL_COMPILE_STATUS, &success);
    if (success != GL_FALSE) {
        shaderNames[numShaders++] = shaderName;
    } else {
        //TODO: add exception
        GLint compilationLogSize = 0;
        glGetShaderiv(shaderName, GL_INFO_LOG_LENGTH, &compilationLogSize);
        std::vector<GLchar> compilationLog(compilationLogSize);
        glGetShaderInfoLog(shaderName, compilationLogSize, &compilationLogSize, &compilationLog[0]);
        std::cerr << "=== SHADER COMPILATION ERROR ===\n"
                     + std::string(compilationLog.begin(), compilationLog.end()); + "\n";
        exit(1);
    }
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

GLint Shader::getU(const std::string &uniformName) {
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