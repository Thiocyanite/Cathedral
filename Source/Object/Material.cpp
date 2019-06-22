//
// Created by Julia on 2019-06-10.
//

#include "Material.h"

void Material::loadTexture(GLuint Tex, Material::MaterialType Mat) {
    Textures[(int)Mat] = Tex;
}

void Material::bind() {
    glBindTextureUnit(0, Textures[(int)MaterialType::COLOR]);
    glBindTextureUnit(1, Textures[(int)MaterialType::NORMAL]);
}
