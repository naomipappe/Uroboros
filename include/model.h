#ifndef OUROBOROS_MODEL_H
#define OUROBOROS_MODEL_H

#include <string>
#include <iterator>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <mesh.h>
// Texture is loaded for each mesh, which can be a lot
// Consider a globally stored textures with meshes holding only a reference / pointer to the said texture
// This should be implemented as a Resource Manager or Resource Storage of some kind
namespace Ouroboros {
    class Model {
    public:
        Model(const std::string &aPath);
        void draw(ShaderProgram &aProgram);

    private:
        std::vector<Mesh> mMeshes;
        static std::vector<std::shared_ptr<Texture>> storage;

        std::string directory;
        void load(const std::string &aPath);
        void process(aiNode *aNode, const aiScene *aScene);
        Mesh process(aiMesh *aMesh, const aiScene *aScene);
        void loadMaterialTextures(aiMaterial *aMaterial, aiTextureType aType, std::vector<std::shared_ptr<Texture>> &textures);
    };
}// namespace Ouroboros
#endif// !MODEL_H
