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
    GVector operator+(const GVector &v) const;
    void sub(const GVector &v);
    GVector operator-(const GVector &v) const;
    void mult(const float &n);
    GVector operator*(const float &n) const;
    void div(const float &n);
    GVector operator/(const float &n) const;
    float mag();
    void normalize();
    void limit(const float &l);

    static GVector random2D();
};