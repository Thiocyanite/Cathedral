//
// Created by Julia on 2019-06-10.
//

#include <fstream>
#include <iostream>
#include "MaterialLoader.h"
#include "../Utility.h"
#include "Material.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::shared_ptr<Material> MaterialLoader::load(const std::string &Path) {
    std::fstream howToLoad;
    howToLoad.open(Path.c_str(), std::ios::in);
    if (howToLoad.fail()) {
        std::cerr << "Could not open howToLoad material file \n";
        exit(EXIT_FAILURE);
    }
    std::string directory=getFileDir(Path);
    std::shared_ptr<Material> mat = std::make_shared<Material>();
    std::string textureName;
    std::string texturePath;

    auto matType=Material::MaterialType::COLOR;
    GLuint tex[(int)Material::MaterialType::NUM_MATS];
    glGenTextures((int)Material::MaterialType::NUM_MATS, tex);

    while (!howToLoad.eof()){
        howToLoad>>textureName;
        texturePath = directory + "/" + textureName;
        if(matType == Material::MaterialType::NUM_MATS) break;
        int width, height, channels;
        unsigned char* image = stbi_load(texturePath.c_str(), &width, &height, &channels, STBI_rgb_alpha );

        glBindTexture(GL_TEXTURE_2D, tex[(int)matType]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

        assert(glIsTexture(tex[(int)matType]));

        mat->loadTexture(tex[(int)matType], matType);

        matType = static_cast<Material::MaterialType>( static_cast<int>(matType) + 1 );

        stbi_image_free(image);
    }
    return mat;
}
