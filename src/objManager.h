#pragma once
#include <array>
#include <forward_list>
#include <utility>
#include <tuple>
#include <cstdlib> 
#include <ctime> 
#include <unordered_set>
#include "const.h"
#include "tileManager.h"
#include "struct/matrixIndex.h"
#include "gameObj/tile.h"
#include "gameObj/matrix.h"
class ObjManager
{
public:
	MatrixObj matrixObj;
	TileManager tileManager;
	void drawAllObj();
	void whenKeyPress(const KeyPressDirection& direction);
	const bool checkIsGameOver() const;
	const bool checkIsGameWin() const;
};