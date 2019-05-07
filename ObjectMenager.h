//
// Created by Julia on 2019-05-07.
//

#ifndef OPENGLSETUP_OBJECTMENAGER_H
#define OPENGLSETUP_OBJECTMENAGER_H

#include <map>
#include <vector>
#include "Object.h"

class ObjectMenager {
private:
    std::vector<std::shared_ptr<Object>> allObjects;
public:
    void addObject(std::shared_ptr<Object> object){
        allObjects.push_back(object);
    }


    std::shared_ptr<Object> getObject(int id) const {
        return  allObjects.at(id);
    }

};


#endif //OPENGLSETUP_OBJECTMENAGER_H
