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
    Orientation='F';
}

Observer::~Observer()
{
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
    if ((speed>0 && maxZ<=position.z)|| speed<0 && minZ>=position.z) //now we are inside a rectangle (later this will be use for collision with walls
        std::cout<<"I can't go farther\n";
    else
        position += direction * speed;
    if (speed>0)
        Orientation='F';
    else
        Orientation='B';

}

void Observer::moveAside(float speed)
{
    if ((speed<0 && maxX<=position.x) || (speed>0 && minX>=position.x)) //same as in moveForard
        std::cout<<"I can't go farther\n";
    else
    position += rightVector * speed;
    if (speed>0)
        Orientation='R';
    else
        Orientation='L';

}