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
	std::shared_ptr<Font> fontPtr = std::make_shared<Font>(GetFontDefault());
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
		const int randomIndex = std::rand() % listSize;
		const auto& randomMatrixIndex = emptyIndexList[randomIndex];
		const int& x = randomMatrixIndex.x;
		const int& y = randomMatrixIndex.y;
		tileObjContainer.emplace_front(MatrixIndex{ x, y }, fontPtr);
		TileObj* const newTilePtr = &tileObjContainer.front();
		tileObjPtrMatrix[y][x] = newTilePtr;
		int c = 0;
		for (auto&t: tileObjContainer) {
			++c;
		}
		if (c>16) {
		LOG("container");
		LOG(c);
		}
	};
	void drawAllTiles() {
		for (auto& tileObj : tileObjContainer) {
			tileObj.drawSelf();
		}
	};
	void handleBeMergedTile(
		const int& currentX,
		const int& currentY,
		const int& targetX,
		const int& targetY 
	) {
		auto& targetTilePtr = tileObjPtrMatrix[currentY][currentX];
		(*targetTilePtr).setState(TileObj::State::BeMerged);
		(*targetTilePtr).setTargetPosition(MatrixIndex{ targetX,targetY }.toPosition());
		tileObjPtrMatrix[currentY][currentX] = nullptr;
	};
	void handleDeleteTileObj() {
		std::forward_list< TileObj*> waitToBeDeletedList;
		for (auto& tileObj : tileObjContainer) {
			if (tileObj.isReadyToBeDeleted()) {
				waitToBeDeletedList.emplace_front(&tileObj);
			}
		}
		//delete tile obj
		for (auto& tileObjPtr : waitToBeDeletedList) {
			tileObjContainer.remove_if(
				[tileObjPtr](auto& tileObj) {
					if (&tileObj == tileObjPtr) {
						LOG("remove")
					}
					return &tileObj == tileObjPtr; 
				}
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
					handleBeMergedTile(x, y,x,mergeOtherY);//matrix[y][x]is merged by matrix[mergeOtherY][x]
					mergeOtherY = -1;//reset				
				}
				else { //not same level, can't merge.
					mergeOtherY = y; 
				}
			}
			//sort zero
			int notNullY = 0;
			for (int currentY = 0; currentY < rowLen ;++currentY) {
				TileObj* currentTilePtr = tileObjPtrMatrix[currentY][x];
				if (currentTilePtr != nullptr) {
					swapTilePtrByIndex({ x,currentY }, { x,notNullY });
					++notNullY;
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
					handleBeMergedTile(x, y, mergeOtherX, y);
					mergeOtherX = -1;//reset
				}
				else { //not same level, can't merge.
					mergeOtherX = x;
				}
			}
			//sort zero
			int notNullX = colLen-1;
			for (int currentX = notNullX; currentX >=0; --currentX) {
				auto& currentTilePtr = tileObjPtrMatrix[y][currentX];
				if (currentTilePtr != nullptr) {
					swapTilePtrByIndex({ currentX,y }, { notNullX,y });
					--notNullX;
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
					handleBeMergedTile(x, y, x, mergeOtherY);
					mergeOtherY = -1;//reset
				}
				else { //not same level, can't merge.
					mergeOtherY = y; //current y try to merge other
				}
			}
			//sort zero
			int notNullY = rowLen-1;
			for (int currentY = notNullY; currentY >=0; --currentY) {
				auto& currentTilePtr = tileObjPtrMatrix[currentY][x];
				if (currentTilePtr != nullptr) {
					swapTilePtrByIndex({ x,currentY }, { x,notNullY });
					--notNullY;
				}
			}
		}
	};
	void setNewTileMatrixByPressLeft() {
		for (int y = 0; y < rowLen; ++y) {
			int mergeOtherX = -1;
			//merge
			for (int x = 0; x < colLen; ++x) {
				 auto&  currentTilePtr = tileObjPtrMatrix[y][x];
				if (currentTilePtr == nullptr) {
					continue;
				}
				if (mergeOtherX < 0) {
					mergeOtherX = x;//current x try to merge other
					continue;
				}
				const bool isSameLevel =
					currentTilePtr->getLevel() ==
					tileObjPtrMatrix[y][mergeOtherX]->getLevel();
				if (isSameLevel) { //merge
					tileObjPtrMatrix[y][mergeOtherX]->increaseLevel();
					handleBeMergedTile(x, y, mergeOtherX, y);
					mergeOtherX = -1;//reset
				}
				else { //not same level, can't merge.
					mergeOtherX = x;
				}
			}
			//sort zero
			int notNullX = 0;
			for (int currentX = notNullX; currentX < colLen; ++currentX) {
				auto& currentTilePtr = tileObjPtrMatrix[y][currentX];
				if (currentTilePtr != nullptr) {
					swapTilePtrByIndex({ currentX,y }, { notNullX,y });
					++notNullX;
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
	bool testIsSingleTileGameOverByBPS(const int& x, const int& y) const {
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