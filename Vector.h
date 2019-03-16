#ifndef RENDERER_VECTOR_H
#define RENDERER_VECTOR_H


#include <ostream>

class Vector {

public:

    float x = 0,
          y = 0,
          z = 0;

    Vector(float x, float y, float z);

    Vector(float xyz);

    /// Creates vector between two points
    Vector(const Vector& p1, const Vector& p2);

    ~Vector();

    float getMagnitude();
    void normalize();
    Vector cross(Vector other);
    float dot(Vector other);

    Vector operator+();
    Vector operator-();
    Vector operator+(Vector other);
    Vector operator-(Vector other);
    Vector operator*(float num);
    Vector operator/(float num);
    Vector operator*(Vector other);
    Vector operator/(Vector other);
    void operator+=(Vector other);
    void operator-=(Vector other);
    void operator*=(Vector other);
    void operator/=(Vector other);
};

std::ostream& operator<<(std::ostream &os, const Vector& vector);

#endif //RENDERER_VECTOR_H
