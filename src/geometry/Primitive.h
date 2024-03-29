#ifndef RENDERER_PRIMITIVE_H
#define RENDERER_PRIMITIVE_H

#include <vector>
#include "Vector3.h"
#include "Ray.h"
#include "../light/Material.h"
#include "Intersection.h"

class Primitive {
public:
    Material material;

    Primitive();

    explicit Primitive(Material material);

    virtual std::vector<Intersection> intersect(const Ray &ray) const = 0;

    virtual void getTexelCoordinates(const Vector3 &intersection, const int textureWidth, const int textureHeight,
                                     int &row, int &column) const = 0;

    const std::string &getUUID() const;

    LightIntensity getDiffuse() const;
    LightIntensity getAmbient() const;
    LightIntensity getSpecular() const;
    double getSmoothness() const;
    bool compareUUID(const Primitive &other) const;

private:
    std::string UUID;
};

#endif //RENDERER_PRIMITIVE_H
