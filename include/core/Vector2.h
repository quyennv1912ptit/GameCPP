#pragma once

#include <math.h>

class Vector2
{
public:
    float x, y;
    Vector2();
    Vector2(float x, float y);
    void sub(Vector2 v);
    void sub(float x, float y);
    void add(Vector2 v);
    void add(float x, float y);
    void mul(float f);
    Vector2 mul_N(float f);
    void normalize();
    float length();
    double angle(Vector2 v);
    void set(float x, float y);
    void fromAngle(double angle);
    void rotate(double angle);
};