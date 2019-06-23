//
// Created by Julia on 2019-05-28.
//

#include "Observer.h"
void Observer::load_char(std::shared_ptr<Object> obj) {
    character = obj;
}

Observer::Observer() {
    position = glm::vec3(0.0f, 0.0f, 3.0f);
    thirdPersonOffset = glm::vec3(0.0f, -2.0f, -1.0f);
    direction = glm::vec3(0.0f, 0.0f, 1.0f);
    upVector = glm::vec3(0.0f, 1.0f, 0.0f);
    rightVector = glm::normalize(glm::cross(direction, upVector));
}

Observer::~Observer() {
    //dtor
}

glm::mat4 Observer::calculateLookAtMatrix() {
    glm::mat4 V = glm::lookAt(
            position + glm::vec3(0.0f, 2.5f, 0.0f) - direction,
            position + direction,
            upVector);
    return V;
}

void Observer::moveForward(float speed) {
    position += direction * speed;
}

void Observer::moveAside(float speed) {
    position += glm::normalize(glm::cross(direction, upVector)) * speed;
}

void Observer::lookAround(float xRotate, float yRotate) {
    pitch += xRotate;
    yaw += yRotate;
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    updateFront();
}

void Observer::updateFront() {
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y = sin(glm::radians(pitch));
    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    direction = glm::normalize(front);
}