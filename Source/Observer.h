//
// Created by matt on 23.05.19.
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


class Observer
{
    glm::vec3 position;
    glm::vec3 center;
    glm::vec3 noseVector;
    glm::vec3 direction;
    glm::vec3 rightVector;
    glm::vec3 upVector;

public:
    glm::mat4 perspectiveMatrix = glm::perspective(glm::radians(130.0f), 1.5f, 0.1f, 100.0f);
    Observer();
    virtual ~Observer();
    glm::mat4 calculateLookAtMatrix();
    void moveForward(float speed);
    void moveAside(float speed);
    void rotate(glm::vec2 rot);
};

#endif //OPENGLSETUP_OBSERVER_H
