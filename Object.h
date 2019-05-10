//
// Created by Julia on 2019-05-07.
//

#ifndef OPENGLSETUP_OBJECT_H
#define OPENGLSETUP_OBJECT_H
#include "Mesh.h"
#include <iostream>

class Object{
public:
    Object();
    std::vector<std::shared_ptr<Mesh>> meshes;
};


class ObjectCreator{
private:
    std::vector<std::shared_ptr<Mesh>> meshes;
    bool isMesh = false;
public:
    ObjectCreator& AddMesh(const std::shared_ptr<Mesh>& mesh){
        meshes.push_back(mesh);
        isMesh = true;
        return *this;
    }

    std::shared_ptr<Object> make(){
        std::shared_ptr<Object> returnObject=std::make_shared<Object>();
        if (!isMesh)
        {std::cerr<<"There is no mesh to create a model 😤\n "; } //later there will be something thrown
        returnObject->meshes=meshes;
        isMesh=false;
        return returnObject;
    }

};

#endif //OPENGLSETUP_OBJECT_H
