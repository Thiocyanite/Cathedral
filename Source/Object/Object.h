//
// Created by Julia on 2019-05-07.
//

#ifndef OPENGLSETUP_OBJECT_H
#define OPENGLSETUP_OBJECT_H
#include "Mesh.h"
#include <iostream>
#include <memory>

class Object{
    friend class ObjectCreationTools;
    friend class AnimatedObjectCreator;
private:
    std::vector<std::shared_ptr<Mesh>> meshes; //Object is a group of meshes
public:
    Object() = default;

    const std::vector<std::shared_ptr<Mesh>> &getMeshes() const {
        return meshes;
    }

    void rotate(float angle) {
        for (auto mesh : meshes) {
            mesh->rotate(angle);
        }
    }

    void scale(float scale) {
        for (auto mesh : meshes) {
            mesh->scale(scale);
        }
    }

};


#endif //OPENGLSETUP_OBJECT_H
