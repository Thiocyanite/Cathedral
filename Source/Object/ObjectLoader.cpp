//
// Created by dominik on 11.05.19.
//
#include <fstream>
#include <vector>

#include "ObjectLoader.h"

#include "Mesh.h"
#include "Object.h"
#include "AnimatedObject.h"

#include "AnimatedObjectCreator.h"
#include "ObjectCreator.h"

#include "../Utility.h"

std::shared_ptr<Object> ObjectLoader::loadObject( const std::string &path ) {
    ObjectCreator objectCreator;

    directory = getFileDir(path);

    loadScene(path);

    loadMeshes(&objectCreator);

    return objectCreator.make();

}

void ObjectLoader::loadScene(const std::string &path) const {
    scene = importer.ReadFile(path.c_str(),
                              aiProcess_CalcTangentSpace |
                              aiProcess_GenSmoothNormals |
                              aiProcess_JoinIdenticalVertices |
                              aiProcess_ImproveCacheLocality |
                              aiProcess_LimitBoneWeights |
                              aiProcess_RemoveRedundantMaterials |
                              aiProcess_SplitLargeMeshes |
                              aiProcess_Triangulate |
                              aiProcess_GenUVCoords |
                              aiProcess_SortByPType |
                              aiProcess_FindDegenerates |
                              aiProcess_FindInvalidData |
                              aiProcess_FindInstances |
                              aiProcess_ValidateDataStructure |
                              aiProcess_OptimizeMeshes |
                              aiProcess_Debone |
                              0);
    if (!scene) {
        std::cerr << "No scene 😤\n" << importer.GetErrorString() << "\n";
    }
}

void ObjectLoader::loadMeshes(ObjectCreationTools *objectCreator) {
    for(int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh *assimpMesh = scene->mMeshes[i];
        auto myMesh = meshLoader.loadSingleMesh(assimpMesh);
        objectCreator->AddMesh(myMesh);
    }
}

std::shared_ptr<AnimatedObject> ObjectLoader::loadAnimation(const std::string &path) {
    std::fstream HowToLoad;
    HowToLoad.open(path);
    const int numReads = 6;
    std::string reads[numReads];
    int i = 0;
    while (!HowToLoad.eof()){
        /*Ignore comments*/
        if(HowToLoad.peek() == (int)'#')
            HowToLoad.ignore( std::numeric_limits<std::streamsize>::max() ,'\n');
        /*Read one word per read, up to max numReads reads*/
        if(i == numReads) break;
        HowToLoad >> reads[i++];
        /*Drop the next line*/
        HowToLoad.ignore( std::numeric_limits<std::streamsize>::max() ,'\n');
    }

    std::string staticPoseFilename = reads[0];
    std::string filename = reads[1];
    int indexWidth       = static_cast<int>(std::strtol(reads[2].c_str(), nullptr, 10));
    int numKeyframes     = static_cast<int>(std::strtol(reads[3].c_str(), nullptr, 10));
    std::string format   = reads[4];
    float animationTime  = std::strtol(reads[5].c_str(), nullptr, 10);

    AnimatedObjectCreator animatedObjectCreator;

    directory = getFileDir(path);

    std::string delimeter = "/";

#ifdef _WIN32
    delimeter = "\\";
#endif

    /*Load static pose*/

    loadScene(directory + delimeter + staticPoseFilename);

    loadMeshes(&animatedObjectCreator);

    /*Load animation*/
    for(i= 1; i < numKeyframes + 1; i++){
        std::string filePath = directory + delimeter;
                    filePath += filename;
                    filePath += numToStrWithPadding(i, indexWidth);
                    filePath += format;


        loadScene(filePath);
        loadKeyframe(&animatedObjectCreator);
    }

    return animatedObjectCreator.make(animationTime);
}

void ObjectLoader::loadKeyframe(AnimatedObjectCreator *objectCreator) {
    std::vector<std::shared_ptr<Mesh>> meshes;
    for(int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh *assimpMesh = scene->mMeshes[i];
        meshes.push_back( meshLoader.loadSingleMesh(assimpMesh) );
    }
    objectCreator->AddKeyframe(meshes);
}
