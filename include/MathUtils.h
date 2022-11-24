//
//  MathUtils.h
//  myGame
//
//  Created by Deng Tengyu on 2022/11/24.
//  Copyright © 2022 Deng Tengyu. All rights reserved.
//

#ifndef MathUtils_h
#define MathUtils_h
#include <cmath>

class Vector2D{
public:
    float x, y;
    Vector2D(float x, float y): x(x), y(y) {}
    Vector2D(): x(0), y(0) {}
    Vector2D operator+(const Vector2D& v) const{
        return Vector2D(x + v.x, y + v.y);
    }
    Vector2D operator-(const Vector2D& v) const{
        return Vector2D(x - v.x, y - v.y);
    }
    Vector2D operator+(float scalar) const{
        return Vector2D(x + scalar, y + scalar);
    }
    Vector2D operator-(float scalar) const{
        return Vector2D(x - scalar, y - scalar);
    }
    Vector2D operator*(float scalar) const{
        return Vector2D(x * scalar, y * scalar);
    }
    Vector2D operator/(float scalar) const{
        return Vector2D(x / scalar, y / scalar);
    }
    Vector2D& operator+=(const Vector2D& v){
        x += v.x;
        y += v.y;
        return *this;
    }
    Vector2D& operator-=(const Vector2D& v){
        x -= v.x;
        y -= v.y;
        return *this;
    }
    Vector2D& operator+=(float scalar){
        x += scalar;
        y += scalar;
        return *this;
    }
    Vector2D& operator-=(float scalar){
        x -= scalar;
        y -= scalar;
        return *this;
    }
    Vector2D& operator*=(float scalar){
        x *= scalar;
        y *= scalar;
        return *this;
    }
    Vector2D& operator/=(float scalar){
        x /= scalar;
        y /= scalar;
        return *this;
    }
    float Length() const{
        return sqrt(x * x + y * y);
    }
    float LengthSquared() const{
        return x * x + y * y;
    }
    float Dot(const Vector2D& v) const{
        return x * v.x + y * v.y;
    }
    Vector2D Normalize() const{
        float length = Length();
        return Vector2D(x / length, y / length);
    }

};

#endif /* MathUtils_h */
