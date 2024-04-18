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
	void setTargetPosition(const Position& targetPos) {
		this->targetPosition = targetPos;
	}
	void setState(const State& state) {
		this->state = state;
	};
	void setFrameSpeed() {
		frameSpeed = pos
			.getDifferenceVector(targetPosition)
			.divide(TILE_ANIMATION_COST_FRAME);
	}
	void increaseLevel() {
		if (level >=TILE_MAX_LEVEL) {
			return;
		}
		else {
			++level ;
		}
	};
	void handleMove() {
		if (targetPosition == pos) { // arrive target
			isMoving = false;
			return;
		}
		if (isMoving) {// during moving
			setPosition(pos + frameSpeed);
			return;
		}
		//start move
		isMoving = true;
		setFrameSpeed();
		setPosition(pos + frameSpeed);
	};
	void handleScale() {
		if (scale + TILE_SCALE_VAR>=100) {
			scale =100;
			return;
		}
		if (scale !=100) {
			scale += TILE_SCALE_VAR;
		}
	}
	bool isReadyToBeDeleted() const {
		return state == State::BeMerged && 
			targetPosition ==pos;
	};
	Position getDrawStartPoint()const {
		if (scale ==100) {
			return pos;
		}
		return {
			pos.x + static_cast<int>(((100-scale)/100 * TILE_WIDTH) / 2),
			pos.y + static_cast<int>(((100-scale)/100 * TILE_HEIGHT) / 2),
		};
	}
	int getLevel() const {
		return level;
	};
	bool isScaleGrowing() const {
		return scale != 100;
	}
	void drawBackgound() {
		if (scale == 100) {
			DrawRectangle(
				pos.x,
				pos.y,
				TILE_WIDTH ,
				TILE_HEIGHT ,
				TILE_INNER_COLOR_LIST[level]
			);
			return;
		}
		const Position& drawStartPoint = getDrawStartPoint();
		DrawRectangle(
			drawStartPoint.x,
			drawStartPoint.y,
			static_cast<int>(scale * TILE_WIDTH/100),
			static_cast<int>(scale * TILE_HEIGHT/100),
			TILE_INNER_COLOR_LIST[level]
		);
	}
	Position getTextStartPoint(const Vector2& textSize) {
		return {
			static_cast<int>(pos.x+((TILE_WIDTH - textSize.x) / 2)),
			static_cast<int>(pos.y+((TILE_HEIGHT - textSize.y) / 2))
		};
	}
	void drawText() {
		const auto& text = TILE_TEXT_LIST[level];
		const auto& textSize = MeasureTextEx(*fontPtr, text, TILE_FONT_SIZE, 0);
		const Position& textStartPoint = getTextStartPoint(textSize);
		DrawText(
			TILE_TEXT_LIST[level],
			textStartPoint.x,
			textStartPoint.y,
			TILE_FONT_SIZE, 
			TILE_FONT_COLOR_LIST[level]);
	}
	void drawSelf() override {
		handleMove();
		handleScale();
		drawBackgound();
		if (!isScaleGrowing()) {
			drawText();
		}
	};
	TileObj(const MatrixIndex& startIndex,const std::shared_ptr<Font>& fontPtr) :
		targetPosition(startIndex.toPosition()),
		fontPtr(fontPtr),
		BaseObj(startIndex.toPosition()) {};
private:
	const std::shared_ptr<Font>& fontPtr;
	Position targetPosition;
	int level = 0;
	bool isMoving = false;
	int scale = TILE_SCALE_START;
	Position frameSpeed = {0,0};
	State state = State::Normal;
};