#pragma once
#include <cmath>
#include "../../lib/raylib/include/raylib.h"
struct Position
{
    Position(const int& x, const int& y) :x(x), y(y) {};
    int x;
    int y;
    Position operator-(const Position& other) const {
        return { this->x - other.x,this->y - other.y };
    }
    Position operator+(const Position& other) const {
        return { this->x+ other.x,this->y +other.y };
    }
    bool operator==(const Position& other) const {
        return  this->x == other.x&&this->y == other.y ;
    }
    bool operator!=(const Position& other) const {
        return  this->x != other.x || this->y != other.y;
    }
    int getDistance(const Position& other) const { 
        return std::abs(this->x - other.x )+std::abs( this->y - other.y);
    }
    Vector2 toVec2() const {
        return Vector2{
            static_cast<float>(this->x),
            static_cast<float>(this->y) 
        };
    }
};