#include "model.h"

namespace Ouroboros {

    std::vector<std::shared_ptr<Texture>> Ouroboros::Model::storage;

    Model::Model(const std::string& aPath) {
        load(aPath);
    }
    void Ouroboros::Model::draw(ShaderProgram& aProgram) {
        for (auto& mesh : mMeshes) {
            mesh.draw(aProgram);
        }
    }

    void Ouroboros::Model::load(const std::string& aPath) {
        Assimp::Importer importer;
        const auto scene = importer.ReadFile(aPath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_OptimizeMeshes);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            printf("ERROR::ASSIMP %s\n", importer.GetErrorString());
            return;
        }
        directory = aPath.substr(0, aPath.find_last_of("\\"));
        process(scene->mRootNode, scene);
    }

    void Ouroboros::Model::process(aiNode* aNode, const aiScene* aScene) {
        for (uint32_t i = 0; i < aNode->mNumMeshes; ++i) {
            aiMesh* mesh = aScene->mMeshes[aNode->mMeshes[i]];
            mMeshes.push_back(process(mesh, aScene));
        }
        for (uint32_t i = 0; i < aNode->mNumChildren; ++i) {
            process(aNode->mChildren[i], aScene);
        }
    }

    Mesh Ouroboros::Model::process(aiMesh* aMesh, const aiScene* aScene) {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        std::vector<std::shared_ptr<Texture>> textures;

        for (uint32_t i = 0; i < aMesh->mNumVertices; ++i) {
            vertices.emplace_back();

            vertices.back().mPosition = glm::vec3(aMesh->mVertices[i].x, aMesh->mVertices[i].y, aMesh->mVertices[i].z);
            if (aMesh->HasNormals()) {
                vertices.back().mNormal = glm::vec3(aMesh->mNormals[i].x, aMesh->mNormals[i].y, aMesh->mNormals[i].z);
            }
            if (aMesh->mTextureCoords[0]) {
                vertices.back().mTextureCoordinates = glm::vec2(aMesh->mTextureCoords[0][i].x, aMesh->mTextureCoords[0][i].y);
            } else {
                vertices.back().mTextureCoordinates = glm::vec2();
            }
        }
        for (uint32_t i = 0; i < aMesh->mNumFaces; ++i) {
            aiFace face = aMesh->mFaces[i];
            for (uint32_t j = 0; j < face.mNumIndices; ++j) {
                indices.push_back(face.mIndices[j]);
            }
        }

        if (aMesh->mMaterialIndex >= 0) {
            aiMaterial* material = aScene->mMaterials[aMesh->mMaterialIndex];
            loadMaterialTextures(material, aiTextureType_DIFFUSE, textures);
            //std::vector<std::shared_ptr<Texture>> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR);
            //textures.insert(textures.end(), std::make_move_iterator(specularMaps.begin()), std::make_move_iterator(specularMaps.end()));
        }
        return Mesh(vertices, indices, textures);
    }

    void Ouroboros::Model::loadMaterialTextures(aiMaterial* aMaterial, aiTextureType aType, std::vector<std::shared_ptr<Texture>>& textures) {
        for (uint32_t i = 0; i < aMaterial->GetTextureCount(aType); ++i) {
            aiString str;
            aMaterial->GetTexture(aType, i, &str);
            auto found = std::find_if(storage.begin(), storage.end(), [&str](const std::shared_ptr<Texture>& t) {
                return t->path() == str.C_Str();
            });
            if (found != storage.end()) {
                textures.push_back(*found);
                return;
            }
            switch (aType) {
                case aiTextureType_DIFFUSE:
                    storage.push_back(std::make_shared<Diffuse>(directory + '\\' + std::string(str.C_Str())));
                    textures.push_back(storage.back());
                    break;
                case aiTextureType_SPECULAR:
                    storage.push_back(std::make_shared<Specular>(directory + '\\' + std::string(str.C_Str())));
                    textures.push_back(storage.back());
                    break;
            }
        }
    }

}// namespace Ouroboros