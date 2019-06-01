//
// Created by dominik on 11.05.19.
//

#ifndef OPENGLSETUP_OBJECTCREATOR_H
#define OPENGLSETUP_OBJECTCREATOR_H

#include "Object.h"
#include "ObjectCreationTools.h"

class ObjectCreator : public  ObjectCreationTools{
public:
    inline ObjectCreator& AddMesh(const std::shared_ptr<Mesh>& mesh){
        ObjectCreationTools::innerAddMesh(mesh);
        return *this;
    }

    inline std::shared_ptr<Object> make() { return ObjectCreationTools::innerMake<Object>(); }
};

#include "Object.h"

#endif //OPENGLSETUP_OBJECTCREATOR_H
