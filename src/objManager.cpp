#include "objManager.h"

void ObjManager::drawAllObj() {
	matrixObj.drawSelf();
	tileManager.handleDeleteTileObj();
	tileManager.drawAllTiles();
}

void ObjManager::whenKeyPress(const KeyPressDirection& direction) {
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
}

const bool ObjManager::checkIsGameOver() const {
	return tileManager.testIsSingleTileGameOverByBPS(0, 0);
}

const bool ObjManager::checkIsGameWin() const {
	for (const auto& tileObj : tileManager.tileObjContainer) {
		if (tileObj.getLevel() >= TILE_MAX_LEVEL) {
			return true;
		}
	}
	return false;
}
