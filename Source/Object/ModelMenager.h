//
// Created by Julia on 2019-05-07.
//

#ifndef OPENGLSETUP_OBJECTMENAGER_H
#define OPENGLSETUP_OBJECTMENAGER_H

#include <map>
#include <vector>
#include "Model.h"
#include <glm/glm.hpp>
class ModelMenager {
private:
    std::vector<std::shared_ptr<Model>> allObjects;
public:
    void addObject(std::shared_ptr<Model> object){
        allObjects.push_back(object);
    }

    int size(){return allObjects.size();};
    std::shared_ptr<Model> getObject(int id) const {
        return  allObjects.at(id);
    }

};


#endif //OPENGLSETUP_OBJECTMENAGER_H
