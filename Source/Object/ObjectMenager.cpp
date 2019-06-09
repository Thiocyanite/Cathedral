//
// Created by Julia on 2019-06-09.
//

#include "ObjectMenager.h"

void ObjectMenager::addObject(std::shared_ptr<Model> _model, glm::vec3 pos, glm::vec3 rot, glm::vec3 sc){
    model.push_back(_model);
    position.push_back(pos);
    rotation.push_back(rot);
    scale.push_back(sc);
}
std::shared_ptr<Model> ObjectMenager::getModel(int id){
    return model.at(id);
}
glm::vec3 ObjectMenager::getPosition(int id){
    return position.at(id);
}
glm::vec3 ObjectMenager::getRotation(int id){
    return rotation.at(id);
}
glm::vec3 ObjectMenager::getScale(int id){
    return scale.at(id);
}