#ifndef RENDERER_LIGHT_H
#define RENDERER_LIGHT_H

#include <memory>
#include <list>
#include "LightIntensity.h"
#include "../geometry/Ray.h"
#include "../geometry/Primitive.h"



class Light {
public:
    LightIntensity diffuseIntensity,
                   ambientIntensity,
                   specularIntensity;

    explicit Light(LightIntensity commonIntensity);

    Light(const LightIntensity &diffuseIntensity, const LightIntensity &ambientIntensity,
          const LightIntensity &specularIntensity);

    Light() = default;

    virtual LightIntensity
    calculateLightIntensity(std::list<std::shared_ptr<Primitive>> scenePrimitives, Vector3 cameraPosition,
                            std::shared_ptr<Primitive> intersectedPrimitive, Intersection intersection) = 0;

    /// Checks if ray can get from surface to light.
    /// \param reflectionPoint point from which the ray is being reflected
    /// \param scenePrimitives list of primitives in scene
    /// \return false if there are other objects in the way of ray.
    /// true if there are none
    virtual bool isAccessible(Vector3 reflectionPoint, std::shared_ptr<Primitive> intersectedPrimitive,
                              std::list<std::shared_ptr<Primitive>> scenePrimitives) = 0;
};




#endif //RENDERER_LIGHT_H
