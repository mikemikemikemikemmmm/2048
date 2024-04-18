#pragma once
#include <cmath>
#include "../../lib/raylib/include/raylib.h"

struct Position
{
    int x;
    int y;
    Position(const int& x, const int& y) :x(x), y(y) {};
    Position operator-(const Position& other) const {
        return { this->x - other.x,this->y - other.y };
    }
    Position operator+(const Position& other) const {
        return { this->x+ other.x,this->y +other.y };
    }
    Position operator*(const int& speed) const {
        return { this->x* speed,this->y * speed };
    }
    Position divide(const int& val) const{
        return {
            this->x / val,
            this->y / val
        };
    }
    bool operator==(const Position& other) const {
        return  this->x == other.x&&this->y == other.y ;
    }
    bool operator!=(const Position& other) const {
        return  this->x != other.x || this->y != other.y;
    }
    Position getDifferenceVector(const Position& other) const {
        return {  other.x - this->x   , other.y- this->y };
    }
    Vector2 toVec2() const {
        return Vector2{
            static_cast<float>(this->x),
            static_cast<float>(this->y) 
        };
    }
};