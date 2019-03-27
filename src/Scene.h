#ifndef RENDERER_SCENE_H
#define RENDERER_SCENE_H


#include <list>
#include <memory>
#include "geometry/Primitive.h"

class Scene {
public:
    std::list<Primitive*> primitives;   // TODO: remove raw pointer

    Scene() = default;

    void AddPrimitive(Primitive* primitive);
};


#endif //RENDERER_SCENE_H
