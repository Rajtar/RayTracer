#ifndef RENDERER_VECTOR_H
#define RENDERER_VECTOR_H


class Vector {

public:

    float x = 0,
          y = 0,
          z = 0;

    Vector(float x, float y, float z);
    Vector(float xyz);
    ~Vector();

    float getMagnitude();
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


#endif //RENDERER_VECTOR_H
