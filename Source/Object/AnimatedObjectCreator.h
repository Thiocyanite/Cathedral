//
// Created by dominik on 31.05.19.
//

#ifndef OPENGLSETUP_ANIMATEDOBJECTCREATOR_H
#define OPENGLSETUP_ANIMATEDOBJECTCREATOR_H


#include "Object.h"
#include "AnimatedObject.h"
#include "Mesh.h"
#include "ObjectCreationTools.h"

class AnimatedObjectCreator : public ObjectCreationTools{
private:
    std::vector<AnimatedObject::Keyframe> keyframes;

public:
    AnimatedObjectCreator& AddKeyframe(const std::vector<std::shared_ptr<Mesh>>& meshes){
        keyframes.emplace_back(0.0, meshes);
    }

    AnimatedObjectCreator& AddMesh(std::shared_ptr<Mesh>& mesh){
        ObjectCreationTools::innerAddMesh(mesh);
        return *this;
    }

    std::shared_ptr<AnimatedObject> make(float animationTime) {
        std::shared_ptr<AnimatedObject> animatedObject = ObjectCreationTools::innerMake<AnimatedObject>();

        float keyframeInterval = animationTime / (keyframes.size() - 1);
        float timeStamp = 0;
        for(auto& keyframe : keyframes){
            keyframe.timeStamp = timeStamp;
            timeStamp += keyframeInterval;
        }


        return animatedObject;
    }
};

#endif //OPENGLSETUP_ANIMATEDOBJECTCREATOR_H
