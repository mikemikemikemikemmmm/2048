#pragma once
#include "position.h"
#include "../const.h"
struct MatrixIndex
{
    MatrixIndex(const int& x, const int& y) :x(x), y(y) {};
    int x;
    int y;
    void plus(const MatrixIndex& other) {
        this->x += other.x;
        this->y += other.y;
    }
    void minus(const MatrixIndex& other) {
        this->x -= other.x;
        this->y -= other.y;
    }
    bool equal(const MatrixIndex& other) const { 
        return (this->x == other.x && this->y == other.y);
    }
    Position toPosition() const{
        return Position{
            this->x * (TILE_INTERVAL_WIDTH + TILE_WIDTH)+ TILE_INTERVAL_WIDTH +MATRIX_START_X ,
            this->y * (TILE_INTERVAL_WIDTH + TILE_HEIGHT)+ TILE_INTERVAL_WIDTH + MATRIX_START_Y
        };
    }
};