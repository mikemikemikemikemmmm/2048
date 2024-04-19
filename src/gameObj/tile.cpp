#include "tile.h"

void TileObj::setTargetPosition(const Position& targetPos) {
	this->targetPosition = targetPos;
}

void TileObj::setState(const State& state) {
	this->state = state;
}

void TileObj::setFrameSpeed() {
	frameSpeed = pos
		.getDifferenceVector(targetPosition)
		.divide(TILE_ANIMATION_COST_FRAME);
}

void TileObj::increaseLevel() {
	if (level >= TILE_MAX_LEVEL) {
		return;
	}
	else {
		++level;
	}
}

void TileObj::handleMove() {
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
}

void TileObj::handleScale() {
	if (scale + TILE_SCALE_VAR >= 1) {
		scale = 1;
		return;
	}
	if (!isScaleEqualOne()) {
		scale += TILE_SCALE_VAR;
	}
}

const bool TileObj::isScaleEqualOne() const {
	return scale == 1;
}

const bool TileObj::isReadyToBeDeleted() const {
	return state == State::BeMerged &&
		targetPosition == pos;
}

const Position TileObj::getBackgroundStartPoint() const {
	if (isScaleEqualOne()) {
		return pos;
	}
	return {
		pos.x + static_cast<int>(((1 - scale) * TILE_WIDTH) / 2),
		pos.y + static_cast<int>(((1 - scale) * TILE_HEIGHT) / 2),
	};
}

const int TileObj::getLevel() const {
	return level;
}

const bool TileObj::isScaleGrowing() const {
	return scale != 1;
}

void TileObj::drawBackgound() {
	if (isScaleEqualOne()) {
		DrawRectangle(
			pos.x,
			pos.y,
			TILE_WIDTH,
			TILE_HEIGHT,
			TILE_INNER_COLOR_LIST[level]
		);
		return;
	}
	const Position drawBackgroundStartPoint = getBackgroundStartPoint();
	DrawRectangle(
		drawBackgroundStartPoint.x,
		drawBackgroundStartPoint.y,
		static_cast<int>(scale * TILE_WIDTH),
		static_cast<int>(scale * TILE_HEIGHT),
		TILE_INNER_COLOR_LIST[level]
	);
}

const Position TileObj::getTextStartPoint() const {
	Vector2 targetTextSize =
		MeasureTextEx(GetFontDefault(), TILE_TEXT_LIST[level], FONT_SIZE, 0);
	return {
		static_cast<int>(pos.x + ((TILE_WIDTH - targetTextSize.x) / 2)),
		static_cast<int>(pos.y + ((TILE_HEIGHT - targetTextSize.y) / 2))
	};
}

void TileObj::drawText() {
	const Position textStartPoint = getTextStartPoint();
	DrawText(
		TILE_TEXT_LIST[level],
		textStartPoint.x,
		textStartPoint.y,
		FONT_SIZE,
		TILE_FONT_COLOR_LIST[level]);
}

void TileObj::drawSelf() {
	handleMove();
	handleScale();
	drawBackgound();
	if (!isScaleGrowing()) {
		drawText();
	}
}

TileObj::TileObj(const MatrixIndex& startIndex) :
	targetPosition(startIndex.toPosition()),
	BaseObj(startIndex.toPosition()) {
}
