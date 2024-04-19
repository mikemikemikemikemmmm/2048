#pragma once
#include <array>

#include "../../lib/raylib/include/raylib.h"

#include "base.h"
#include "../const.h"
#include "../struct/matrixIndex.h"
#include "../struct/position.h"
class TileObj :public BaseObj {
public:
	enum class State {
		Normal,MergeOther,BeMerged
	};
	const bool isScaleEqualOne()  const;
	const bool isReadyToBeDeleted() const;
	const bool isScaleGrowing() const;
	const int getLevel() const;
	const Position getBackgroundStartPoint()const;
	const Position getTextStartPoint() const;
	void setTargetPosition(const Position& targetPos);
	void setState(const State& state);
	void setFrameSpeed();
	void increaseLevel();
	void handleMove();
	void handleScale();
	void drawBackgound();
	void drawText();
	void drawSelf() override;
	TileObj(
		const MatrixIndex& startIndex);
private:
	Position targetPosition;
	int level = TILE_START_LEVEL;
	Vector2 textSize = 
		MeasureTextEx(GetFontDefault(), TILE_TEXT_LIST[TILE_START_LEVEL], FONT_SIZE, 0);
	bool isMoving = false;
	float scale = TILE_SCALE_START;
	Position frameSpeed = {0,0};
	State state = State::Normal;};