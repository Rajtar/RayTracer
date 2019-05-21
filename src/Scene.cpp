//
// Created by jakub on 21.05.2019.
//

#include "Scene.h"

void Scene::addPrimitive(std::shared_ptr<Primitive> primitive) {
    this->primitives.push_back(primitive);
}

void Scene::addLight(std::shared_ptr<Light> light) {
    this->lights.push_back(light);
}
