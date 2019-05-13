//
// Created by Julia on 2019-05-07.
//

#ifndef OPENGLSETUP_OBJECT_H
#define OPENGLSETUP_OBJECT_H
#include "Mesh.h"
#include <iostream>
#include <memory>

class Object{
    friend class ObjectCreator;
private:
    std::vector<std::shared_ptr<Mesh>> meshes; //Object is a group of meshes
public:
    Object() = default;

    const std::vector<std::shared_ptr<Mesh>> &getMeshes() const {
        return meshes;
    }

};


#endif //OPENGLSETUP_OBJECT_H
