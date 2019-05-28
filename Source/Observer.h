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

class Observer {
    glm::vec3 position;
    glm::vec3 center;
    glm::vec3 noseVector;
    glm::vec3 direction;
    glm::vec3 rightVector;
    glm::vec3 upVector;
    glm::mat4 lookAt;

public:
    Observer();
    virtual ~Observer();
    glm::mat4 calculateLookAtMatrix();
    void moveForward(float speed);
    void moveAside(float speed);
};


#endif //OPENGLSETUP_OBSERVER_H
