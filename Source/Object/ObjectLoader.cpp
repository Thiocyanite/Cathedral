//
// Created by dominik on 11.05.19.
//
#include <fstream>
#include "ObjectLoader.h"

#include "Mesh.h"
#include "Object.h"
#include "AnimatedObject.h"

std::shared_ptr<Object> ObjectLoader::loadObject( const std::string &path ) {
    ObjectCreator objectCreator;

    directory = getFileDir(path);

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
        std::cerr<<"No scene 😤\n"<<importer.GetErrorString()<<"\n";
    }

    loadMeshes(objectCreator);

    return objectCreator.make();

}
void ObjectLoader::loadMeshes(ObjectCreator &objectCreator) {
    for(int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh *assimpMesh = scene->mMeshes[i];
        auto myMesh = meshLoader.loadSingleMesh(assimpMesh);
        objectCreator.AddMesh(myMesh);
    }
}

std::shared_ptr<AnimatedObject> ObjectLoader::loadAnimation(const std::string &path) {
    std::fstream HowToLoad;
    HowToLoad.open(path);
    std::string reads[4];
    int i = 0;
    while (!HowToLoad.eof()){
        if(HowToLoad.peek() == '#')
            HowToLoad.ignore(1,'\n');
        HowToLoad >> reads[i++];
    }
    std::string filename = reads[0];
    int indexWidth       = static_cast<int>(std::strtol(reads[1].c_str(), nullptr, 10));
    int numKeyframes     = static_cast<int>(std::strtol(reads[2].c_str(), nullptr, 10));
    std::string format   = reads[3];


}
