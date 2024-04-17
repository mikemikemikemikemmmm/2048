#pragma once
#include <array>
#include <forward_list>
#include <utility>
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
public:
	using TilePtrMatrix = std::array<std::array<TileObj*, MATRIX_COL_NUM>, MATRIX_ROW_NUM>;
	using IndexSet = std::unordered_set<std::pair<int, int>>;
	const int rowLen = MATRIX_ROW_NUM;
	const int colLen = MATRIX_COL_NUM;
	TilePtrMatrix tileObjPtrMatrix;
	std::forward_list<TileObj> tileObjContainer;
	void generateNewTile() {
		std::vector<MatrixIndex> emptyIndexList;
		for (int y = 0; y < rowLen; ++y) {
			for (int x = 0; x < colLen; ++x) {
				if (tileObjPtrMatrix[y][x] == nullptr) {
					emptyIndexList.emplace_back(x, y);
				}
			}
		}
		const auto& listSize = emptyIndexList.size();
		if (listSize == 0) {
			return;
		}
		int randomIndex = std::rand() % listSize;
		auto randomMatrixIndex = emptyIndexList[randomIndex];
		const int& x = randomMatrixIndex.x;
		const int& y = randomMatrixIndex.y;
		tileObjContainer.emplace_front(MatrixIndex{ x, y });
		TileObj* const newTilePtr = &tileObjContainer.front();
		tileObjPtrMatrix[y][x] = newTilePtr;
	};
	void drawAllTiles() {
		for (auto& tileObj : tileObjContainer) {
			tileObj.drawSelf();
		}
	};
	void deleteTilePtrFromMatrix(const int x, const int y) {
		auto targetTilePtr = tileObjPtrMatrix[y][x];
		(*targetTilePtr).setState(TileObj::State::Minifing);
		tileObjPtrMatrix[y][x] = nullptr;
	};
	void handleDeleteTileObj() {
		std::forward_list<TileObj*> waitToBeDeletedList;
		for (auto& tileObj : tileObjContainer) {
			if (tileObj.isNeedToBeDeleted()) {
				waitToBeDeletedList.emplace_front(&tileObj);
			}
		}
		//delete tile obj
		for (auto& tileObjPtr : waitToBeDeletedList) {
			tileObjContainer.remove_if(
				[tileObjPtr](auto& tileObj) { return &tileObj == tileObjPtr; }
			);
		}
	};
	void setTileNewTargetPositionByPtr(TileObj* tilePtr, const MatrixIndex& newIndex) {
		(*tilePtr).setPosition(newIndex.toPosition());
	}
	void setNewTileMatrixByPressUp() {
		for (int x = 0; x < colLen; ++x) {
			int mergeOtherY = -1;
			//merge
			for (int y = 0; y < rowLen; ++y) {
				auto& currentTilePtr = tileObjPtrMatrix[y][x];
				if (currentTilePtr == nullptr) {
					continue;
				}
				if (mergeOtherY < 0) {
					mergeOtherY = y;//try to merge other, not be merged
					continue;
				}
				const bool isSameLevel =
					currentTilePtr->getLevel() ==
					tileObjPtrMatrix[mergeOtherY][x]->getLevel();
				if (isSameLevel) { //can merge
					tileObjPtrMatrix[mergeOtherY][x]->increaseLevel();
					mergeOtherY = -1;//reset
					deleteTilePtrFromMatrix(x, y);//matrix[y][x]is merged by matrix[mergeOtherY][x]
				}
				else { //not same level, can't merge.
					mergeOtherY = y; 
				}
			}
			//sort zero
			int y = 0;
			for (int currentY = y; currentY < rowLen;++currentY) {
				auto& currentTilePtr = tileObjPtrMatrix[currentY][x];
				if (currentTilePtr != nullptr) {
					swapTilePtrByIndex({ x,currentY }, { x,y});
					++y;
				}
			}
		}
	};
	void setNewTileMatrixByPressRight() {
		for (int y = 0; y < rowLen; ++y) {
			int mergeOtherX = -1;
			//merge
			for (int x = colLen - 1; x >= 0; --x) {
				auto& currentTilePtr = tileObjPtrMatrix[y][x];
				if (currentTilePtr == nullptr) {
					continue;
				}
				if (mergeOtherX < 0) {
					mergeOtherX = x;
					continue;
				}
				const bool isSameLevel =
					currentTilePtr->getLevel() ==
					tileObjPtrMatrix[y][mergeOtherX]->getLevel();
				if (isSameLevel) { //merge
					tileObjPtrMatrix[y][mergeOtherX]->increaseLevel();
					mergeOtherX = -1;//reset
					deleteTilePtrFromMatrix(x, y);
				}
				else { //not same level, can't merge.
					mergeOtherX = x;
				}
			}
			//sort zero
			int x = colLen-1;
			for (int currentX = x; currentX >=0; --currentX) {
				auto& currentTilePtr = tileObjPtrMatrix[y][currentX];
				if (currentTilePtr != nullptr) {
					swapTilePtrByIndex({ currentX,y }, { x,y });
					--x;
				}
			}
		}
	};
	void setNewTileMatrixByPressDown() {
		for (int x = 0; x < colLen; ++x) {
			int mergeOtherY = -1;
			//merge
			for (int y = rowLen - 1; y >= 0; --y) {
				auto& currentTilePtr = tileObjPtrMatrix[y][x];
				if (currentTilePtr == nullptr) {
					continue;
				}
				if (mergeOtherY < 0) {
					mergeOtherY = y;//current y try to merge other
					continue;
				}
				const bool isSameLevel =
					currentTilePtr->getLevel() ==
					tileObjPtrMatrix[mergeOtherY][x]->getLevel();
				if (isSameLevel) { //merge
					tileObjPtrMatrix[mergeOtherY][x]->increaseLevel();
					mergeOtherY = -1;//reset
					deleteTilePtrFromMatrix(x, y);
				}
				else { //not same level, can't merge.
					mergeOtherY = y; //current y try to merge other
				}
			}
			//sort zero
			int y = rowLen-1;
			for (int currentY = y; currentY >=0; --currentY) {
				auto& currentTilePtr = tileObjPtrMatrix[currentY][x];
				if (currentTilePtr != nullptr) {
					swapTilePtrByIndex({ x,currentY }, { x,y });
					--y;
				}
			}
		}
	};
	void setNewTileMatrixByPressLeft() {
		for (int y = 0; y < rowLen; ++y) {
			int notEmptyTileX = -1;
			//merge
			for (int x = 0; x < colLen; ++x) {
				 auto&  currentTilePtr = tileObjPtrMatrix[y][x];
				if (currentTilePtr == nullptr) {
					continue;
				}
				if (notEmptyTileX < 0) {
					notEmptyTileX = x;//current x try to merge other
					continue;
				}
				const bool isSameLevel =
					currentTilePtr->getLevel() ==
					tileObjPtrMatrix[y][notEmptyTileX]->getLevel();
				if (isSameLevel) { //merge
					tileObjPtrMatrix[y][notEmptyTileX]->increaseLevel();
					notEmptyTileX = -1;//reset
					deleteTilePtrFromMatrix(x, y);
				}
				else { //not same level, can't merge.
					notEmptyTileX = x;
				}
			}
			//sort zero
			int x = 0;
			for (int currentX = x; currentX < colLen; ++currentX) {
				auto& currentTilePtr = tileObjPtrMatrix[y][currentX];
				if (currentTilePtr != nullptr) {
					swapTilePtrByIndex({ currentX,y }, { x,y });
					++x;
				}
			}
		}
	};
	void swapTilePtrByIndex(const MatrixIndex& i1, const MatrixIndex& i2) {
		TileObj* const tempPtr = tileObjPtrMatrix[i1.y][i1.x];
		tileObjPtrMatrix[i1.y][i1.x] = tileObjPtrMatrix[i2.y][i2.x];
		tileObjPtrMatrix[i2.y][i2.x] = tempPtr;
		if (tileObjPtrMatrix[i2.y][i2.x] !=nullptr) {
			tileObjPtrMatrix[i2.y][i2.x]->setTargetPosition(i2.toPosition());
		}
		if (tileObjPtrMatrix[i1.y][i1.x] != nullptr) {
			tileObjPtrMatrix[i1.y][i1.x]->setTargetPosition(i1.toPosition());
		}
	};
	bool testIsSingleTileGameOverByBPS(const int& x, const int& y) {
		if (x >= colLen || y >= rowLen) {
			return true;
		}
		auto&  currentPtr = tileObjPtrMatrix[y][x];
		if ( currentPtr == nullptr) {
			return false;
		};
		//test right 
		if (x + 1 < colLen) {
			 auto&  rightPtr = tileObjPtrMatrix[y][x + 1];
			if (rightPtr == nullptr) {
				return false;
			};
			if (rightPtr->getLevel() == currentPtr->getLevel()) {
				return false;
			};
		};
		//test down
		if (y + 1 < rowLen) {
			 auto&  downPtr = tileObjPtrMatrix[y + 1][x];
			if (downPtr == nullptr) {
				return false;
			};
			if (downPtr->getLevel() == currentPtr->getLevel()) {
				return false;
			};
		};
		return testIsSingleTileGameOverByBPS(x + 1, y) &&
			testIsSingleTileGameOverByBPS(x, y + 1);
	};
};