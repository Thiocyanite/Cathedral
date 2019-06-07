//
// Created by Julia on 2019-05-07.
//

#ifndef OPENGLSETUP_MESH_H
#define OPENGLSETUP_MESH_H

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

#include "../Utility.h"

class Mesh {
public:
    std::vector<glm::vec3> pos;
    std::vector<glm::vec3> col;
    std::vector<glm::vec2> texCords;
    std::vector<glm::vec3> normals;

    std::vector<unsigned int> indicies;

    GLuint vertexArrayObject, bufferObjects[5];

    void initVAO();

    void reloadVAO();

    void bindVAO();

    inline void unbindVAO();

    Mesh(){};
    ~Mesh(){};
};



#endif //OPENGLSETUP_MESH_H
