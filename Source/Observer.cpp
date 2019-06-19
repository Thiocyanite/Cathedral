//
// Created by Julia on 2019-05-28.
//

#include "Observer.h"
Observer::Observer()
{
    this->position = glm::vec3(0.0f, 0.0f, 3.0f);
    this->cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
    this->direction = glm::normalize(position - cameraFront);
    this->noseVector = glm::vec3(0.0f, 1.0f, 0.0f);
    this->rightVector = glm::normalize(glm::cross(noseVector, cameraFront));
    this->upVector = glm::cross(direction, rightVector);

}

Observer::~Observer()
{
    //dtor
}

glm::mat4 Observer::calculateLookAtMatrix()
{
    glm::mat4 V = glm::lookAt(
            position,
            position + cameraFront,
            noseVector);
    return V;
}

void Observer::moveForward(float speed)
{
    this->position += this->cameraFront * speed;

}

void Observer::moveAside(float speed)
{
    this->position + glm::normalize(glm::cross(cameraFront, upVector)) * speed;
}

void Observer::lookAround(float xRotate, float yRotate)
{
    pitch += xRotate;
    yaw += yRotate;
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    updateFront();
}

void Observer::updateFront()
{
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y = sin(glm::radians(pitch));
    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    cameraFront = glm::normalize(front);
}