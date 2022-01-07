//
// Created by Ihor Zvieriev on 13.03.2021.
//

#include <Scene.h>

Scene::Scene() {
}

void Scene::addBox(std::unique_ptr<Box> object) {
    m_boxes.insert(std::move(object));
}

void Scene::setPlane(std::unique_ptr<Plane> plane) {
    m_plane = std::move(plane);
}

void Scene::render() {
    for (const auto &object : m_boxes) {
        object->update();
    }
    m_plane->update();
}