#ifndef RENDERER_SCENE_H
#define RENDERER_SCENE_H


#include <list>
#include "geometry/Primitive.h"

class Scene {
public:
    std::list<Primitive> primitives;

    Scene(const std::list<Primitive> &primitives);
    Scene() = default;

    void AddPrimitive(const Primitive &primitive);
};


#endif //RENDERER_SCENE_H
