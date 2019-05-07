//
// Created by Julia on 2019-05-07.
//

#ifndef OPENGLSETUP_CONVERTER_H
#define OPENGLSETUP_CONVERTER_H


#include <string>
#include "./glm/glm.hpp"
#include "./glm/gtc/type_ptr.hpp"
#include "./assimp/scene.h"


std::string asstoapp(const aiString &name) {return name.C_Str();}

glm::vec4 glmCast(const aiColor4D &v) { return glm::vec4(v.r, v.g, v.b, v.a); }
glm::vec4 glmCast(const aiVector3D &v, float fourthValue) { return glm::vec4(v.x, v.y, v.z, fourthValue); }
glm::vec3 glmCast(const aiVector3D &v) { return glm::vec3(v.x, v.y, v.z); }
glm::vec2 glmVec2Cast(const aiVector3D &v) { return glm::vec2(v.x, v.y); }
glm::quat glmCast(const aiQuaternion &q) { return glm::quat(q.w, q.x, q.y, q.z); }
glm::mat4 glmCast(const aiMatrix4x4 &m) { return glm::transpose(glm::make_mat4(&m.a1)); }



#endif //OPENGLSETUP_CONVERTER_H
