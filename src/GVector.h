#pragma once

class GVector
{
private:
public:
    float x;
    float y;
    GVector();
    GVector(float _x, float _y);
    ~GVector();

    void add(const GVector &v);
    GVector operator+(const GVector &v);
    void sub(const GVector &v);
    GVector operator-(const GVector &v);
    void mult(const float &n);
    GVector operator*(const float &n);
    void div(const float &n);
    GVector operator/(const float &n);
    float mag();
    void normalize();
};