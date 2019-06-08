//
// Created by Julia on 2019-05-28.
//

#ifndef OPENGLSETUP_OBSERVER_H
#define OPENGLSETUP_OBSERVER_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <memory>

class Model;
class Menager;

class Observer {
private:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 rightVector;
    glm::vec3 upVector;
    glm::vec3 thirdPersonOffset;
    std::shared_ptr<Model> character;

public:
    friend  class Menager;
    Observer();
    virtual ~Observer();
    glm::mat4 calculateLookAtMatrix();
    void moveForward(float speed);
    void moveAside(float speed);
    void load_char(std::shared_ptr<Model> obj);
};


#endif //OPENGLSETUP_OBSERVER_H
