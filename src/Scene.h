#ifndef RENDERER_SCENE_H
#define RENDERER_SCENE_H


#include <list>
#include <memory>
#include "geometry/Primitive.h"
#include "light/Light.h"

class Scene {
public:
    std::list<std::shared_ptr<Primitive>> primitives;
    std::list<std::shared_ptr<Light>> lights;

    Scene() = default;

    void addPrimitive(std::shared_ptr<Primitive> primitive);
    void addLight(std::shared_ptr<Light> light);
};


#endif //RENDERER_SCENE_H
