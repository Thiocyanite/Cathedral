//
// Created by dominik on 11.05.19.
//

#ifndef OPENGLSETUP_OBJECTCREATOR_H
#define OPENGLSETUP_OBJECTCREATOR_H

#include "Model.h"
#include "ObjectCreationTools.h"

class ObjectCreator : public  ObjectCreationTools{
public:

    inline std::shared_ptr<Model> make() { return ObjectCreationTools::innerMake<Model>(); }
};

#include "Model.h"

#endif //OPENGLSETUP_OBJECTCREATOR_H
