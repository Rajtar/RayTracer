#include <algorithm>
#include "Scene.h"

void Scene::addPrimitive(std::shared_ptr<Primitive> primitive) {
        primitives.push_back(primitive);
}
