#ifndef GLCALL
#define GLCALL

#include "GL/glew.h"

#define glCall(x) glClearLog();\
                  x;\
                  glLogCall()

inline void glClearLog(){
    while(glGetError() != GL_NO_ERROR);
}

inline void glLogCall(){
    while(GLenum  error = glGetError()){
        std::cerr << "=====\tOPEN GL ERROR\t====\n" << glGetString(error) << "\n";
    }
}

#endif