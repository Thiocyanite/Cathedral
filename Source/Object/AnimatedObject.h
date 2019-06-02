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

    AnimatedObject() = default;

    void initAnimationVAO();

    void sendDataToBufer(const std::shared_ptr<Mesh>& mesh1, const std::shared_ptr<Mesh>& mesh2);

    virtual ~AnimatedObject();

    float getInterpolationFactor(float timePassed);

    void bindCurrentPose(float timePassed, int meshNum);

    void unbind();

    struct Keyframe{
        float timeStamp;
        std::vector<std::shared_ptr<Mesh>> pose;

        Keyframe(float timeStamp, std::vector<std::shared_ptr<Mesh>> pose) : timeStamp(timeStamp), pose(std::move(pose)) {
        }
        virtual ~Keyframe() = default;
    };

    GLuint vao{0}, vbo[7]{0};

    std::vector<Keyframe> keyframes;
private:
    float animationTime{0};
    float keyframeDuration{0};
};


#endif //OPENGLSETUP_ANIMATEDOBJECT_H
