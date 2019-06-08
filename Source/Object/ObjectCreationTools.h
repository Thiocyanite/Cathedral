//
// Created by dominik on 01.06.19.
//

#ifndef OPENGLSETUP_OBJECTCREATIONTOOLS_H
#define OPENGLSETUP_OBJECTCREATIONTOOLS_H


#include "Model.h"

class ObjectCreationTools {

protected:
    std::vector<std::shared_ptr<Mesh>> meshes;
    bool isMesh = false;

    template<class Type>
    std::shared_ptr<Type> innerMake(){
        std::shared_ptr<Type> returnObject= std::make_shared<Type>();
        if (!isMesh) //Model has to have at least one mesh
        {
            std::cerr << "There is no mesh to create a model 😤\n ";
            throw false;
        }
        returnObject->meshes=meshes;
        meshes.clear();
        isMesh=false;
        return returnObject;
    }

public:
    inline void AddMesh(const std::shared_ptr<Mesh>& mesh){ //because Model can have few meshes
        meshes.push_back(mesh);
        isMesh = true;
    }
};


#endif //OPENGLSETUP_OBJECTCREATIONTOOLS_H
