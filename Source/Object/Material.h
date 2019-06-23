//
// Created by Julia on 2019-06-10.
//

#ifndef OPENGLSETUP_MATERIAL_H
#define OPENGLSETUP_MATERIAL_H


#include <glm/glm.hpp>
#include <GL/glew.h>


class Material {

public:
enum class MaterialType {COLOR, NUM_MATS};


void loadTexture(GLuint Tex, MaterialType Mat);
void  bind();

private:
    GLuint Textures[(int)MaterialType::NUM_MATS];
};

#endif //OPENGLSETUP_MATERIAL_H
