//
// Created by Julia on 2019-05-28.
//

#include "Observer.h"
#include "Object/Model.h"

void Observer::load_char(std::shared_ptr<Model> obj) {
    character = obj;
}

Observer::Observer()
{
    position = glm::vec3(0.0f, 0.0f, 3.0f);
    thirdPersonOffset = glm::vec3(0.0f, -2.0f, -1.0f);
    direction = glm::vec3(0.0f,0.0f, 3.0f);
    upVector = glm::vec3(0.0f, 1.0f, 0.0f);
    rightVector = glm::normalize(glm::cross(direction, upVector));
}

Observer::~Observer()
{
    //dtor
}

glm::mat4 Observer::calculateLookAtMatrix()
{
    glm::mat4 V = glm::lookAt(
            position + glm::vec3(0,2.5, 0) - direction,
            position + direction,
            upVector);
    return V;
}

void Observer::moveForward(float speed)
{
    position += direction * speed;

}

void Observer::moveAside(float speed)
{
    position += rightVector * speed;
}