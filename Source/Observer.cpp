//
// Created by matt on 23.05.19.
//

#include "Observer.h"
Observer::Observer()
{
    this->position = glm::vec3(0.0f, 0.0f, 3.0f);
    this->center = glm::vec3(0.0f, 0.0f, -1.0f);
    this->direction = glm::normalize(position - center);
    this->noseVector = glm::vec3(0.0f, 1.0f, 0.0f);
    this->rightVector = glm::normalize(glm::cross(noseVector, center));
    this->upVector = glm::cross(direction, rightVector);
}

Observer::~Observer()
{
    //dtor
}

glm::mat4 Observer::calculateLookAtMatrix()
{
    glm::mat4 V = glm::lookAt(
            this->position,
            this->center,
            this->noseVector);
    return V;
}

void Observer::moveForward(float speed)
{
    this->position += this->center * speed;

}

void Observer::moveAside(float speed)
{
    this->position + glm::normalize(glm::cross(center, upVector)) * speed;
}

void Observer::rotate(glm::vec2 rot)
{
    glm::mat4 matrix = glm::mat4(1.0f);
    matrix = glm::rotate(matrix, rot.x, glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, rot.y, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::vec4 direct = matrix * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
    center = position + glm::vec3(direct);
}