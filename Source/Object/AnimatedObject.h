#include <cmath>

#include <utility>

//
// Created by dominik on 31.05.19.
//

#ifndef OPENGLSETUP_ANIMATEDOBJECT_H
#define OPENGLSETUP_ANIMATEDOBJECT_H

#include <memory>
#include <vector>

#include "Object.h"
#include "../Utility.h"


class Mesh;

class AnimatedObject : public Object {
    friend class ObjectCreator;
    friend class AnimatedObjectCreator;
public:
    GLuint vao{0}, vbo[7]{0};

    AnimatedObject(){
    }

    void initAnimationVAO(){
        glGenVertexArrays(1, &vao);
        glGenBuffers(7, vbo);
        glBindVertexArray(vao);

        float posVecSize   = getVecSizeInBytes(keyframes[0].pose[0]->pos     );
        float colVecSize   = getVecSizeInBytes(keyframes[0].pose[0]->col     );
        float texVecSize   = getVecSizeInBytes(keyframes[0].pose[0]->texCords);
        float normVecSize  = getVecSizeInBytes(keyframes[0].pose[0]->normals );
        float indiciesSize = getVecSizeInBytes(keyframes[0].pose[0]->indicies);

        float posSize  = sizeof(keyframes[0].pose[0]->pos[0]     );
        float colSize  = sizeof(keyframes[0].pose[0]->col[0]     );
        float texSize  = sizeof(keyframes[0].pose[0]->texCords[0]);
        float normSize = sizeof(keyframes[0].pose[0]->normals[0] );

        //pos1
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, posVecSize, nullptr, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, posSize, nullptr);
        glEnableVertexAttribArray(0);

        //color
        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, colVecSize, keyframes[0].pose[0]->col.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, colSize, nullptr);
        glEnableVertexAttribArray(1);

        //texCoord
        glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
        glBufferData(GL_ARRAY_BUFFER, texVecSize, keyframes[0].pose[0]->texCords.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, texSize, nullptr);
        glEnableVertexAttribArray(2);

        //normal1
        glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
        glBufferData(GL_ARRAY_BUFFER, normVecSize, nullptr, GL_STATIC_DRAW);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, normSize, nullptr);
        glEnableVertexAttribArray(3);

        //pos2
        glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
        glBufferData(GL_ARRAY_BUFFER, posVecSize, nullptr, GL_STATIC_DRAW);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, posSize, nullptr);
        glEnableVertexAttribArray(4);

        //normal2
        glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);
        glBufferData(GL_ARRAY_BUFFER, normVecSize, nullptr, GL_STATIC_DRAW);
        glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, normSize, nullptr);
        glEnableVertexAttribArray(5);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[6]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiciesSize, keyframes[0].pose[0]->indicies.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    void sendDataToBufer(const std::shared_ptr<Mesh>& mesh1, const std::shared_ptr<Mesh>& mesh2){
        glBindVertexArray(vao);

        //pos1
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, getVecSizeInBytes(mesh1->pos), mesh1->pos.data());

        //normal1
        glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, getVecSizeInBytes(mesh1->normals), mesh1->normals.data());

        //pos2
        glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, getVecSizeInBytes(mesh2->pos), mesh2->pos.data());

        //normal2
        glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, getVecSizeInBytes(mesh2->normals), mesh2->normals.data());

    }

    virtual ~AnimatedObject() {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(7, vbo);
    }

    struct Keyframe{
        float timeStamp;
        std::vector<std::shared_ptr<Mesh>> pose;


        Keyframe(float timeStamp, std::vector<std::shared_ptr<Mesh>> pose) : timeStamp(timeStamp), pose(std::move(pose)) {
        }

        virtual ~Keyframe() = default;

    };

    float getInterpolationFactor(float timePassed){
        timePassed = std::fmod(timePassed, animationTime);
        return std::fmod(timePassed, keyframeDuration) / keyframeDuration;
    }

    void bindCurrentPose(float timePassed, int meshNum){
        /*Todo: remember animation starting time.
         * Currently all animations behave like they
         * started with the start of application
         * */

        /*Trim the time to fit animation time*/
        timePassed = std::fmod(timePassed, animationTime);


        int lowerPoseId = static_cast<int>(std::floor(timePassed / keyframeDuration));
        int upperPoseId = lowerPoseId + 1;

        sendDataToBufer(keyframes[lowerPoseId].pose[meshNum],
                        keyframes[upperPoseId].pose[meshNum]);
    }

    void unbind(){
        glBindVertexArray(0);
    }

    std::vector<Keyframe> keyframes;
private:
    float animationTime{0};
    float keyframeDuration{0};
};


#endif //OPENGLSETUP_ANIMATEDOBJECT_H
