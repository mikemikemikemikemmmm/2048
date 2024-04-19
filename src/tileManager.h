#pragma once
#include <array>
#include <forward_list>
#include <utility>
#include <memory>
#include <tuple>
#include <cstdlib> 
#include <vector> 
#include <ctime> 
#include <unordered_set>
#include "const.h"
#include "struct/matrixIndex.h"
#include "gameObj/tile.h"
#include "gameObj/matrix.h"
class TileManager {
private:
	using TilePtrMatrix = std::array<std::array<TileObj*, MATRIX_COL_NUM>, MATRIX_ROW_NUM>;
	using IndexSet = std::unordered_set<std::pair<int, int>>;
	const int rowLen = MATRIX_ROW_NUM;
	const int colLen = MATRIX_COL_NUM;
	TilePtrMatrix tileObjPtrMatrix;
public:
	std::forward_list<TileObj> tileObjContainer;
	void generateNewTile();
	void drawAllTiles();;
	void handleBeMergedTile(
		const int& currentX,
		const int& currentY,
		const int& targetX,
		const int& targetY 
	);;
	void handleDeleteTileObj();
	void setTileNewTargetPositionByPtr(TileObj* tilePtr, const MatrixIndex& newIndex);
	void setNewTileMatrixByPressUp();
	void setNewTileMatrixByPressRight();
	void setNewTileMatrixByPressDown();
	void setNewTileMatrixByPressLeft();
	void swapTilePtrByIndex(const MatrixIndex& i1, const MatrixIndex& i2);
	const bool testIsSingleTileGameOverByBPS(const int& x, const int& y) const;
};