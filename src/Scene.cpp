#include <algorithm>
#include "Scene.h"

void Scene::AddPrimitive(Primitive* primitive) {
    //if(!(std::find(primitives.begin(), primitives.end(), primitive) != primitives.end())){
        primitives.push_back(primitive);
   // }
}
