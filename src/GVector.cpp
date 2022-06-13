#include "GVector.h"
#include <math.h>

GVector::GVector() : x(0), y(0) {}
GVector::GVector(float _x, float _y) : x(_x), y(_y) {}

GVector::~GVector()
{
}

void GVector::add(const GVector &v)
{
    x += v.x;
    y += v.y;
}
GVector GVector::operator+(const GVector &v)
{
    GVector vec;
    vec.x = this->x + v.x;
    vec.y = this->y + v.y;
    return vec;
}
void GVector::sub(const GVector &v)
{
    x -= v.x;
    y -= v.y;
}
GVector GVector::operator-(const GVector &v)
{
    GVector vec;
    vec.x = this->x - v.x;
    vec.y = this->y - v.y;
    return vec;
}
void GVector::mult(const float &n)
{
    x *= n;
    y *= n;
}
GVector GVector::operator*(const float &n)
{
    GVector vec;
    vec.x = this->x * n;
    vec.y = this->y * n;
    return vec;
}
void GVector::div(const float &n)
{
    x /= n;
    y /= n;
}
GVector GVector::operator/(const float &n)
{
    GVector vec;
    vec.x = this->x / n;
    vec.y = this->y / n;
    return vec;
}
float GVector::mag()
{
    return std::sqrt(x * x + y * y);
}
void GVector::normalize()
{
    float m = mag();
    if (m == 0)
        return;
    div(m);
}