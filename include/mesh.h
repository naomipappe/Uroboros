//
// Created by Ihor Zvieriev on 16.01.2022.
//

#ifndef ENTRYPOINT_MESH_H
#define ENTRYPOINT_MESH_H

#include <glm/glm.hpp>

namespace Ouroboros {
    struct Vertex {
        glm::vec3 mPosition;
        glm::vec3 mNormal;
        glm::vec2 mTextureCoordinates;
    };

    struct Mesh {
    };

}// namespace Ouroboros

#endif//ENTRYPOINT_MESH_H
