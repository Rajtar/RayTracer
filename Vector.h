#ifndef RENDERER_VECTOR_H
#define RENDERER_VECTOR_H


#include <ostream>

class Vector {

public:

    float x = 0,
          y = 0,
          z = 0;

    /// Creates vector between two points
    Vector(const Vector& p1, const Vector& p2);
    Vector(float x, float y, float z);
    Vector(float xyz);

    ~Vector();

    void normalize();
    float getMagnitude();
    float dot(const Vector &other);
    Vector cross(const Vector &other);
    Vector reflect(const Vector& normal);

    Vector operator+();
    Vector operator-();
    void operator+=(const Vector &other);
    void operator-=(const Vector &other);
    void operator*=(const Vector &other);
    void operator/=(const Vector &other);
};

Vector operator+(const Vector &left, const Vector &right);
Vector operator-(const Vector &left, const Vector &right);
Vector operator*(const Vector &left, const Vector &right);
Vector operator/(const Vector &left, const Vector &right);
std::ostream& operator<<(std::ostream &os, const Vector& vector);

#endif //RENDERER_VECTOR_H
