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

#include "Mesh.h"
#include "MeshLoader.h"
#include "Object.h"
#include "ObjectLoader.h"

class ObjectLoader {
public:
    std::shared_ptr<Object> loadObject(const std::string &path);
private:
    inline  static aiScene scene;
    inline static MeshLoader meshload;
    inline static Assimp::Importer import;
    inline static std::string directory;

    static void loadMeshes(const std::shared_ptr<Object> &thisObject);
};

std::shared_ptr<Object> ObjectLoader::loadObject( const std::string &path ) {
    std::shared_ptr<Object> thisObject = std::make_shared<Object>();

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
        std::cerr<<"No object 😤\n";
    }
    loadMeshes(thisObject);
    return thisObject;

}
void ModelLoader::loadMeshes(const std::shared_ptr<Model> &thisModel) {
    for(int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh *assimpMesh = scene->mMeshes[i];
        meshLoader.loadBasicMeshInfo(assimpMesh);
        thisModel->meshes.push_back(meshLoader.make());
    }
}

#endif //OPENGLSETUP_OBJECTLOADER_H
