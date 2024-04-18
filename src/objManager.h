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
	void drawAllObj() {
		matrixObj.drawSelf();
		tileManager.handleDeleteTileObj();
		tileManager.drawAllTiles();
	};
	void whenKeyPress(const KeyPressDirection& direction) {
		switch (direction)
		{
			case KeyPressDirection::UP: {
				tileManager.setNewTileMatrixByPressUp();
				break;
			}
			case KeyPressDirection::RIGHT: {
				tileManager.setNewTileMatrixByPressRight();
				break;
			}
			case KeyPressDirection::DOWN: {
				tileManager.setNewTileMatrixByPressDown();
				break;
			}
			case KeyPressDirection::LEFT: {
				tileManager.setNewTileMatrixByPressLeft();
				break;
			}
		};
		tileManager.generateNewTile();
	};
	bool checkIsGameOver() {
		return tileManager.testIsSingleTileGameOverByBPS(0,0);
	};
	bool checkIsGameWin() {
		for (const auto& tileObj : tileManager.tileObjContainer) {
			if (tileObj.getLevel()>=TILE_MAX_LEVEL) { 
				return true;
			}
		}
		return false;
	};
};