//
// Created by Julia on 2019-06-09.
//

#ifndef OPENGLSETUP_OBJECTMENAGER_H
#define OPENGLSETUP_OBJECTMENAGER_H

#include <vector>
#include <memory>
#include <glm/glm.hpp>

class Model;
class Menager;


class ObjectMenager {
private:
    std::vector<std::shared_ptr<Model>> model;
    std::vector<glm::vec3> position;
    std::vector<glm::vec3> rotation;
    std::vector<glm::vec3> scale;
public:
    friend class Menager;
    void addObject(std::shared_ptr<Model> _model, glm::vec3 pos, glm::vec3 rot, glm::vec3 sc );
    std::shared_ptr<Model> getModel(int id);
    glm::vec3 getPosition(int id);
    glm::vec3 getRotation(int id);
    glm::vec3 getScale(int id);
    int size(){ return model.size();};
};


#endif //OPENGLSETUP_OBJECTMENAGER_H
