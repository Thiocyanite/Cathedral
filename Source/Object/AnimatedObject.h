#include <utility>

//
// Created by dominik on 31.05.19.
//

#ifndef OPENGLSETUP_ANIMATEDOBJECT_H
#define OPENGLSETUP_ANIMATEDOBJECT_H

#include <memory>
#include <vector>

#include "Object.h"
class Mesh;

class AnimatedObject : public Object {
    friend class ObjectCreator;
    friend class AnimatedObjectCreator;
public:
    struct Keyframe{
        float timeStamp;
        std::vector<std::shared_ptr<Mesh>> pose;

        Keyframe(float timeStamp, std::vector<std::shared_ptr<Mesh>> pose) : timeStamp(timeStamp), pose(std::move(pose)) {}
    };

    void findCurrentPose(float* timePassed){
        /*Trim the time to fit animation time*/
        while(*timePassed > animationTime){
            *timePassed = *timePassed - animationTime;
        }

        int lowerPoseId = static_cast<int>(*timePassed / keyframeDuration);
        int upperPoseId = lowerPoseId + 1;
        if (upperPoseId > keyframes.size()) upperPoseId = 0;

        /*TODO: Bind both poses for drawing*/
    }

private:
    std::vector<Keyframe> keyframes;
    float animationTime;
    float keyframeDuration;
};


#endif //OPENGLSETUP_ANIMATEDOBJECT_H
