#include <cmath>
#include "Vector3.h"

Vector3::Vector3(const Vector3 &p1, const Vector3 &p2) {
    this->x = p2.x - p1.x;
    this->y = p2.y - p1.y;
    this->z = p2.z - p1.z;
}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3::Vector3(float xyz) : x(xyz), y(xyz), z(xyz) {}

void Vector3::normalize() {
    float magnitude = getMagnitude();
    if (magnitude != 0) {
        *this /= magnitude;
    }
}

float Vector3::getMagnitude() {
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

float Vector3::dot(const Vector3 &other) const {
    return this->x * other.x + this->y * other.y + this->z * other.z;
}

Vector3 Vector3::cross(const Vector3 &other) {
    return (this->y * other.z - this->z * other.y, this->z * other.x - this->x * other.z, this->x * other.y -
                                                                                          this->y * other.x);
}

Vector3 Vector3::reflect(const Vector3 &normal) {
    return *this - (2 * this->dot(normal) * normal);
}

//region InstanceOperators

Vector3 Vector3::operator+() {
    return *this;
}

Vector3 Vector3::operator-() {
    return Vector3(-this->x, -this->y, -this->z);
}

void Vector3::operator+=(const Vector3 &other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
}

void Vector3::operator-=(const Vector3 &other) {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
}

void Vector3::operator*=(const Vector3 &other) {
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
}

void Vector3::operator/=(const Vector3 &other) {
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
}

//endregion

//region GeneralOperators

Vector3 operator+(const Vector3 &left, const Vector3 &right) {
    return Vector3(left.x + right.x, left.y + right.y, left.z + right.z);
}

Vector3 operator-(const Vector3 &left, const Vector3 &right) {
    return Vector3(left.x - right.x, left.y - right.y, left.z - right.z);
}

Vector3 operator*(const Vector3 &left, const Vector3 &right) {
    return Vector3(left.x * right.x, left.y * right.y, left.z * right.z);
}

Vector3 operator/(const Vector3 &left, const Vector3 &right) {
    return Vector3(left.x / right.x, left.y / right.y, left.z / right.z);
}

std::ostream &operator<<(std::ostream &os, const Vector3 &vector) {
    return os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
}
//endregion