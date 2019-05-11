//
// Created by Julia on 2019-05-07.
//

#ifndef OPENGLSETUP_MESH_H
#define OPENGLSETUP_MESH_H

#include <memory>
#include <vector>
#include <glm/glm.hpp>

class Mesh {
public:
    std::vector<glm::vec3> pos;
    std::vector<glm::vec3> col;
    std::vector<glm::vec2> texCords;
    std::vector<glm::vec3> normals;

    std::vector<unsigned int> indicies;
    Mesh(){};
    ~Mesh(){};
};
#endif //OPENGLSETUP_MESH_H
