//
// Created by Julia on 2019-05-07.
//

#ifndef OPENGLSETUP_MESHLOADER_H
#define OPENGLSETUP_MESHLOADER_H


#include <iostream>
#include <stdio.h>
#include <memory>
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "Converter.h"
#include "Mesh.h"
class MeshLoader{
public:
    std::shared_ptr<Mesh> loadSingleMesh(aiMesh* assimpMesh){
        if(assimpMesh == nullptr){
            std::cerr << "Tried to load not existing Mesh\n";
            exit(1);
        }

        std::shared_ptr<Mesh> loadedMesh = std::make_shared<Mesh>();
        unsigned int numVertices = assimpMesh->mNumVertices;
        unsigned int numFaces = assimpMesh->mNumFaces;

        bool hasColors = assimpMesh->HasVertexColors(0);
        bool hasTexCords = assimpMesh->HasTextureCoords(0);
        bool hasNormals = assimpMesh->HasNormals();
        bool hasTex= assimpMesh->HasTextureCoords(0);
        aiColor4D defaultColor(1.f, 0.5f, 1.f, 1.0f); //default purple
        aiVector3D defaultTexCoord = aiVector3D(0.0f, 0.0f, 0.0f);
        aiVector3D defaultNormal(0.0f, 0.0f, 1.0f);

        for(unsigned int i = 0; i < numVertices; i++){
            aiVector3D* positions = &assimpMesh->mVertices[i];
            bool tex=hasTexCords;
            aiColor4D* colors    = hasColors   ? assimpMesh->mColors[i]         : & defaultColor;
            //aiVector3D* texCords = hasTexCords ? assimpMesh->mTextureCoords[i] : & defaultTexCoord;
            aiVector3D* normals  = hasNormals  ? & assimpMesh->mNormals[i]     : & defaultNormal;
            loadedMesh->texCords.push_back(glmCast(defaultTexCoord));
            loadedMesh->pos.push_back( glmCast(*positions) ); //setting  parameters
            loadedMesh->col.push_back( glmCast(*colors) );
            loadedMesh->normals.push_back( glmCast(*normals) );
        }

        for(unsigned int i = 0; i < numFaces; i++){
            aiFace& face = assimpMesh->mFaces[i];

            if(face.mNumIndices != 3){
                std::cerr << "Mesh faces not triangulated\n";
                exit(1);
            }

            loadedMesh->indicies.push_back( face.mIndices[0] );
            loadedMesh->indicies.push_back( face.mIndices[1] );
            loadedMesh->indicies.push_back( face.mIndices[2] );
        }

        loadedMesh->initVAO();

        return loadedMesh;
    }
private:

};


#endif //OPENGLSETUP_MESHLOADER_H
