#pragma once
#include "../../lib/raylib/include/raylib.h"

#include "base.h"
#include "../struct/position.h"
#include "../struct/matrixIndex.h"
#include "../const.h"
class MatrixObj :public BaseObj {
public:
	MatrixObj():BaseObj(Position{ MATRIX_START_X ,MATRIX_START_Y}) {};
	void  drawSelf() override;
};