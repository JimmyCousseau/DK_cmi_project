#include "Math.hpp"

Vector2D::Vector2D(float inputX, float inputY) : x(inputX), y(inputY)
{

}

Vector2D::Vector2D() : x(0), y(0)
{

}

Vector2D::~Vector2D()
{
    
}

Vector2D& Vector2D::operator+=(const Vector2D& v)
{
    this->x += v.x;
    this->y += v.y;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& v)
{
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}

Vector2D& Vector2D::operator*=(const float& f)
{
    this->x *= f;
    this->y *= f;
    return *this;
}

Vector2D operator-(const Vector2D &v)
{
    Vector2D result = {-v.x, -v.y};

    // avoid -0 shenanigans 
    if (result.x == -0.0) { result.x = 0.0; }
    if (result.y == -0.0) { result.y = 0.0; }

    return result;
}

Vector2D operator-(const Vector2D &v1, const Vector2D &v2)
{
    Vector2D result = v1;
    return result -= v2;
}

Vector2D operator+(const Vector2D &v1, const Vector2D &v2)
{
    Vector2D result = v1;
    return result += v2;
}

Vector2D operator*(const Vector2D &v, float f)
{
    Vector2D result = v;
    return result *= f;
}

Vector2D operator*(float f, const Vector2D &v)
{
    Vector2D result = v;
    return result *= f;
}

std::ostream& operator<<(std::ostream& os, const Vector2D& v)
{
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<Vector2D> &vector)
{
    os << "[";

    size_t vectorSize = vector.size();
    for (size_t i = 0; i < vectorSize; ++i)
    {
        os << vector[i];
        if (i != vectorSize -1)
        {
            os << ", ";
        }
    }
    os << "]";

    return os;
}


bool operator==(const Vector2D& v1, const Vector2D& v2)
{
    return (v1.x == v2.x && v1.y == v2.y);
}

Vector2D Math::normalize_vector(const Vector2D &vector)
{
    const float vectorLength = std::sqrt(vector.x*vector.x + vector.y*vector.y);
    Vector2D normalizedVector = { vector.x/vectorLength, vector.y/vectorLength };

    return normalizedVector;
}

float Math::dot(const Vector2D &vect1, const Vector2D &vect2)
{
    const float result = vect1.x*vect2.x + vect1.y*vect2.y;
    return result;
}

Vector2D Math::triple_cross_product(const Vector2D &vect1, const Vector2D &vect2, const Vector2D &vect3)
{
    const Vector2D result = Math::dot(vect1, vect3)*vect2 - Math::dot(vect2, vect3)*vect1;
    return result;
}

Vector2D Math::normal_clockwise(const Vector2D &vect)
{
    return Vector2D(vect.y, -vect.x);
}

Vector2D Math::normal_counter_clockwise(const Vector2D &vect)
{
    return Vector2D(-vect.y, vect.x);
}

float Math::lenght(const Vector2D &vect)
{
    return sqrt(vect.x*vect.x + vect.y*vect.y);
}