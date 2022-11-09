#pragma once

#include <math.h>
#include <iostream>
#include <vector>

struct Vector2D
{
    float x;
    float y;

    Vector2D(float inputX, float inputY);
    Vector2D();
    ~Vector2D();

    Vector2D& operator+=(const Vector2D& v);
    Vector2D& operator-=(const Vector2D& v);
    Vector2D& operator *=(const float& f);

    friend Vector2D operator-(const Vector2D &v);
    friend Vector2D operator-(const Vector2D &v1, const Vector2D &v2);
    friend Vector2D operator+(const Vector2D &v1, const Vector2D &v2);
    friend Vector2D operator*(const Vector2D &v, float f);
    friend Vector2D operator*(float f, const Vector2D &v);
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v);
    friend std::ostream& operator<<(std::ostream& os, const std::vector<Vector2D> &v);
    friend bool operator==(const Vector2D& v1, const Vector2D& v2);
};

class Math
{
public:
    static Vector2D normalize_vector(const Vector2D &vector);
    static float dot(const Vector2D &vect1, const Vector2D &vect2);
    static Vector2D triple_cross_product(const Vector2D &vect1, const Vector2D &vect2, const Vector2D &vect3);
    static Vector2D normal_clockwise(const Vector2D &vect);
    static Vector2D normal_counter_clockwise(const Vector2D &vect);
    static float lenght(const Vector2D &vect);
};