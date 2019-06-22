//
// Created by dominik on 02.06.19.
//

#include "Mesh.h"

void Mesh::initVAO() {
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

void Mesh::reloadVAO() {
    glBindVertexArray(vertexArrayObject);

    glBindBuffer(GL_ARRAY_BUFFER, bufferObjects[0]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, getVecSizeInBytes(pos), pos.data());

    glBindBuffer(GL_ARRAY_BUFFER, bufferObjects[1]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, getVecSizeInBytes(col), col.data());

    glBindBuffer(GL_ARRAY_BUFFER, bufferObjects[2]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, getVecSizeInBytes(texCords), texCords.data());

    glBindBuffer(GL_ARRAY_BUFFER, bufferObjects[3]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, getVecSizeInBytes(normals), normals.data());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObjects[4]);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, getVecSizeInBytes(indicies), indicies.data());

    glBindVertexArray(0);
}

void Mesh::bindVAO() {
    glBindVertexArray(vertexArrayObject);
}

void Mesh::unbindVAO() {
    glBindVertexArray(0);
}
