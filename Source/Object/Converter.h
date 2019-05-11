//
// Created by Julia on 2019-05-07.
//

#ifndef OPENGLSETUP_CONVERTER_H
#define OPENGLSETUP_CONVERTER_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/scene.h>

std::string asstoapp(const aiString &name);

glm::vec4 glmCast(const aiColor4D &v);
glm::vec4 glmCast(const aiVector3D &v, float fourthValue);
glm::vec3 glmCast(const aiVector3D &v);
glm::vec2 glmVec2Cast(const aiVector3D &v);
glm::quat glmCast(const aiQuaternion &q);
glm::mat4 glmCast(const aiMatrix4x4 &m);



#endif //OPENGLSETUP_CONVERTER_H
