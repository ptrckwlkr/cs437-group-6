#ifndef CSCI437_VECTOR2D_H
#define CSCI437_VECTOR2D_H

#include <iostream>
#include <cmath>

/**
 * Normalized vector
 */
class Vector2D
{
public:
    Vector2D(float x, float y) : x(x), y(y), length(sqrtf(x * x + y * y)) {}

    friend std::ostream& operator<< (std::ostream &out, const Vector2D &v) {out << "(" << v.x << ", " << v.y << ")";}
    friend Vector2D operator* (float scalar, const Vector2D &v) {return {v.x * scalar, v.y * scalar};}
    friend Vector2D operator* (const Vector2D &v, float scalar) {return {v.x * scalar, v.y * scalar};}
    friend Vector2D operator+ (const Vector2D &v1, const Vector2D &v2) {return {v1.x + v2.x, v1.y + v2.y};}
    friend Vector2D operator- (const Vector2D &v1, const Vector2D &v2) {return {v1.x - v2.x, v1.y - v2.y};}
    friend Vector2D operator- (const Vector2D &v) {return {-v.x, -v.y};}
    Vector2D normal()
    {
      Vector2D v = length > 0 ? Vector2D(x / length, y / length) : Vector2D(0, 0);
      return v;
    }

    float x;
    float y;
    float length;
};

#endif //CSCI437_VECTOR2D_H
