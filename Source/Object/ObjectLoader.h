//
// Created by Julia on 2019-05-07.
//

#ifndef OPENGLSETUP_OBJECTLOADER_H
#define OPENGLSETUP_OBJECTLOADER_H

#include <memory>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>

#include "MeshLoader.h"
#include "Model.h"
#include "ObjectLoader.h"
#include "../Utility.h"
#include "ObjectCreationTools.h"
#include "AnimatedObjectCreator.h"

class Model;
class AnimatedObject;

class ObjectLoader {
public:
    std::shared_ptr<Model> loadObject(const std::string &path);
    std::shared_ptr<AnimatedObject> loadAnimation(const std::string &path);
private:
    inline static const aiScene* scene;
    inline static MeshLoader meshLoader;
    inline static Assimp::Importer importer;
    inline static std::string directory;
    static void loadMeshes(ObjectCreationTools *objectCreator);
    static void loadKeyframe(AnimatedObjectCreator *objectCreator);

    void loadScene(const std::string &path) const;
};

#endif //OPENGLSETUP_OBJECTLOADER_H
