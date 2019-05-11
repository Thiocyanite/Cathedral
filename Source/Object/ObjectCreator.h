//
// Created by dominik on 11.05.19.
//

#ifndef OPENGLSETUP_OBJECTCREATOR_H
#define OPENGLSETUP_OBJECTCREATOR_H

#include "Object.h"

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
        std::shared_ptr<Object> returnObject= std::make_shared<Object>();
        if (!isMesh)
        {
            std::cerr << "There is no mesh to create a model 😤\n ";
        throw false;}
        returnObject->meshes=meshes;
        isMesh=false;
        return returnObject;
    }
};

#include "Object.h"

#endif //OPENGLSETUP_OBJECTCREATOR_H
