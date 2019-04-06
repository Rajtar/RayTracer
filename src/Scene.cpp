#include <algorithm>
#include "Scene.h"

void Scene::addPrimitive(std::unique_ptr<Primitive> primitive) {
        primitives.push_back(std::move(primitive));
}
