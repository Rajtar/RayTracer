#ifndef RENDERER_VECTOR_H
#define RENDERER_VECTOR_H


#include <ostream>

class Vector3 {
public:
    float x = 0,
          y = 0,
          z = 0;

    /// Creates vector between two points
    Vector3(const Vector3& p1, const Vector3& p2);
    Vector3(float x, float y, float z);
    Vector3(float xyz);
    Vector3() = default;

    Vector3 normalize() const;
    float getMagnitude() const;
    float dot(const Vector3 &other) const;
    Vector3 cross(const Vector3 &other) const;
    Vector3 reflect(const Vector3& normal) const;

    Vector3 operator+() const;
    Vector3 operator-() const;
    void operator+=(const Vector3 &other);
    void operator-=(const Vector3 &other);
    void operator*=(const Vector3 &other);
    void operator/=(const Vector3 &other);
};

Vector3 operator+(const Vector3 &left, const Vector3 &right);
Vector3 operator-(const Vector3 &left, const Vector3 &right);
Vector3 operator*(const Vector3 &left, const Vector3 &right);
Vector3 operator/(const Vector3 &left, const Vector3 &right);
std::ostream& operator<<(std::ostream &os, const Vector3& vector);

#endif //RENDERER_VECTOR_H
