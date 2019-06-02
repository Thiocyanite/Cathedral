//
// Created by Julia on 2019-05-07.
//

#ifndef OPENGLSETUP_MESH_H
#define OPENGLSETUP_MESH_H

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

class Mesh {
public:
    std::vector<glm::vec3> pos;
    std::vector<glm::vec3> col;
    std::vector<glm::vec2> texCords;
    std::vector<glm::vec3> normals;

    std::vector<unsigned int> indicies;

    GLuint vertexArrayObject, bufferObjects[5];

    template<class Vec>
    auto getVecSizeInBytes(Vec vec){
        return sizeof(vec[0]) * vec.size();
    }

    void initVAO(){
        glGenVertexArrays(1, &vertexArrayObject);
        glGenBuffers(5, bufferObjects);

        glBindVertexArray(vertexArrayObject);

        /* Load positions into gpu ram, and enable it in vao.*/
        glBindBuffer(GL_ARRAY_BUFFER, bufferObjects[0]);
        glBufferData(GL_ARRAY_BUFFER, getVecSizeInBytes(pos), pos.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(pos[0]), nullptr);
        glEnableVertexAttribArray(0);

        /* Load colors into gpu ram, and enable it in vao.*/
        glBindBuffer(GL_ARRAY_BUFFER, bufferObjects[1]);
        glBufferData(GL_ARRAY_BUFFER, getVecSizeInBytes(col), col.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(col[0]), nullptr);
        glEnableVertexAttribArray(1);

        /* Load texture coordinates into gpu ram, and enable it in vao.*/
        glBindBuffer(GL_ARRAY_BUFFER, bufferObjects[2]);
        glBufferData(GL_ARRAY_BUFFER, getVecSizeInBytes(texCords), texCords.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(texCords[0]), nullptr);
        glEnableVertexAttribArray(2);

        /* Load normals into gpu ram, and enable it in vao.*/
        glBindBuffer(GL_ARRAY_BUFFER, bufferObjects[3]);
        glBufferData(GL_ARRAY_BUFFER, getVecSizeInBytes(normals), normals.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(normals[0]), nullptr);
        glEnableVertexAttribArray(3);

        /* Load indicies into gpu ram.*/
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObjects[4]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, getVecSizeInBytes(indicies), indicies.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    inline void bindVAO(){
        glBindVertexArray(vertexArrayObject);
    }

    inline void unbindVAO(){
        glBindVertexArray(0);
    }

    Mesh(){};
    ~Mesh(){};
};
#endif //OPENGLSETUP_MESH_H
