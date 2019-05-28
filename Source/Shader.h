//
// Created by Julia on 2019-05-12.
//

#ifndef OPENGLSETUP_SHADER_H
#define OPENGLSETUP_SHADER_H

#include <GL/glew.h>
#include <string>

class Shader {
private:
    GLuint MainShader;
    GLuint VertexShader;
    GLuint GeometryShader;
    GLuint FragmentShader;
    const std::string File;
    char* readFile(const std::string File);
    GLuint loadShader(GLenum shaderType, std::string File);

public:
    Shader(const std::string vertexShaderFile,const std::string geometryShaderFile,const std::string fragmentShaderFile);
    ~Shader();
    void use();
    GLuint u(const std::string File);
    GLuint a(const std::string File);
};


#endif //OPENGLSETUP_SHADER_H
