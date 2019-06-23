//
// Created by Julia on 2019-06-10.
//

#include "Material.h"

void Material::loadTexture(GLuint Tex, Material::MaterialType Mat) {
    assert(glIsTexture(Tex));
    Textures[(int)Mat] = Tex;
}

void Material::bind() {
    assert(glIsTexture(Textures[(int)MaterialType::COLOR]));


    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, Textures[(int)MaterialType::COLOR]);


}
