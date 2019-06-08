//
// Created by Julia on 2019-05-07.
//

#ifndef OPENGLSETUP_OBJECT_H
#define OPENGLSETUP_OBJECT_H
#include "Mesh.h"
#include <iostream>
#include <memory>

class Model{
    friend class ObjectCreationTools;
    friend class AnimatedObjectCreator;
private:
    std::vector<std::shared_ptr<Mesh>> meshes; //Model is a group of meshes
public:
    Model() = default;

    const std::vector<std::shared_ptr<Mesh>> &getMeshes() const {
        return meshes;
    }

};


#endif //OPENGLSETUP_OBJECT_H
