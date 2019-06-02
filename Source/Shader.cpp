//
// Created by Julia on 2019-05-12.
//

#include "Shader.h"

Shader::Shader()
{
    std::cout << "Shader class constructor\n";
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
}

void Shader::readVertexShaderSource()
{
    std::fstream file;
    file.open(vertexShaderFileName, std::ios::in | std::ios::out);

    if(!file.is_open())
    {
        std::cout << "ERROR::SHADER::VERTEX::FILE_READ_FAIL\n";
    }

    while(!file.eof())
    {
        std::string tempString;
        getline(file, tempString);
        vertexShaderSource.append(tempString);
    }

    file.close();
}

void Shader::compileShader() {
    const char * vss = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vss, NULL);
    glCompileShader(vertexShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}
