//
// Created by Julia on 2019-05-28.
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