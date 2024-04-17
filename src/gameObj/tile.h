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
		Normal,Enlarging, Minifing
	};
	void minifySelf() {
		if (scale <= TILE_SCALE_VAR) {
			scale = 0;
			return;
		}
		scale -= TILE_SCALE_VAR;
	};
	void setTargetPosition(const Position& targetPos) {
		this->targetPosition = targetPos;
	}
	void enlargeSelf() {
		if ((scale + TILE_SCALE_VAR)>=1) {
			scale = 1;
			setState(State::Normal);
			return;
		}
		scale += TILE_SCALE_VAR;
	};
	bool isNeedToBeDeleted() const {
		return state == State::Minifing && scale <= TILE_SCALE_DELETED_THRESHOLD;
	};
	bool isMinifing() const {
		return state == State::Minifing;
	};
	bool isShowOnMatrix() const {
		return state != State::Minifing;
	};
	void setState(const State& state) {
		this->state = state;
	};
	void moveTile() {
		if (targetPosition == pos|| isMinifing()) {
			return;
		}
		setPosition(targetPosition);
		//const int distance = pos.getDistance(targetPosition);
		//if (distance<= speed) {
		//	setPosition(targetPosition);
		//	return;
		//}
		//int quotient = distance / (speed*2); TODO
		//speed *= quotient;//TODO

	};
	void increaseLevel() {
		if (level >=TILE_MAX_LEVEL) {
			return;
		}
		else {
			++level ;
		}
	};
	Position getDrawStartPoint()const {
		if (scale ==1) {
			return pos;
		}
		return {
			pos.x + static_cast<int>(((1-scale)* TILE_WIDTH) / 2),
			pos.y + static_cast<int>(((1-scale) * TILE_HEIGHT) / 2),
		};
	}
	int getLevel() const {
		return level;
	};
	void handleScale() {
		if (state == State::Enlarging) {
			enlargeSelf();
		}
		else if (state == State::Minifing) {
			minifySelf();
		}
	}
	void drawBackgound() {
		const Position& drawStartPoint = getDrawStartPoint();
		DrawRectangle(
			drawStartPoint.x,
			drawStartPoint.y,
			static_cast<int>(scale * TILE_WIDTH),
			static_cast<int>(scale * TILE_HEIGHT),
			TILE_COLOR_LIST[level]
		);
	}
	void drawText() {
		DrawText(
			TILE_TEXT_LIST[level],
			pos.x, 
			pos.y, 
			TILE_FONT_SIZE, 
			TILE_FONT_COLOR);
	}
	void drawSelf() override {
			moveTile();
			handleScale();
			drawBackgound();
			if (state==State::Normal) {
				drawText();
			}
	};
	TileObj(const MatrixIndex& startIndex) :
		targetPosition(startIndex.toPosition()),
		BaseObj(startIndex.toPosition()) {};
private:
	Position targetPosition;
	int level = 0;
	float scale = TILE_SCALE_START; // start by 20% TILE_WIDTH 20% TILE_HEIGHT
	int speed = TILE_BASE_SPEED;
	State state = State::Enlarging;
};