#ifndef ENTRYPOINT_SCENE_H
#define ENTRYPOINT_SCENE_H

#include <memory>
#include <set>

#include <Cube.h>

class Scene {
public:
    explicit Scene();

    void addBox(std::unique_ptr<Box> box);
    void setPlane(std::unique_ptr<Plane> plane);

    void render();

private:
    std::set<std::unique_ptr<Box>> m_boxes;
    std::unique_ptr<Plane> m_plane;
    glm::vec3 m_sceneUp = glm::vec3(0, 1, 0);
};

#endif//ENTRYPOINT_SCENE_H
