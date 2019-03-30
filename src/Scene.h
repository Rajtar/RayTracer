#ifndef RENDERER_SCENE_H
#define RENDERER_SCENE_H


#include <list>
#include <memory>
#include "geometry/Primitive.h"

class Scene {
public:
    std::list<std::unique_ptr<Primitive>> primitives;

    Scene() = default;

    void AddPrimitive(std::unique_ptr<Primitive> primitive);
};


#endif //RENDERER_SCENE_H
