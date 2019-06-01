//
// Created by Julia on 2019-05-12.
//

#ifndef OPENGLSETUP_SHADER_H
#define OPENGLSETUP_SHADER_H

#include <GL/glew.h>
#include <string>
#include <map>

class Shader {
private:

    std::string readFile( std::string path);
    void loadShader(std::string path, GLuint ShaderType);
    GLuint programName = 0;
    int numShaders = 0;
    GLuint shaderNames[3] = {0,0,0};
    std::map<std::string, GLint> uniformLocationsMap;
    void freeShaders();
public:
    void loadProgram(std::string vertex, std::string geometry,std::string fragment);
    void use(){ glUseProgram(programName); }
    void freeProgram();
    GLint getU(const std::string uniformName);
    Shader(){};
    ~Shader(){};
};


#endif //OPENGLSETUP_SHADER_H
