#include <algorithm>
#include "Scene.h"

Scene::Scene(const std::list<Primitive> &primitives) : primitives(primitives) {}

void Scene::AddPrimitive(const Primitive &primitive) {
    //if(!(std::find(primitives.begin(), primitives.end(), primitive) != primitives.end())){
        primitives.push_back(primitive);
   // }
}
