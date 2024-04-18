#include "matrix.h"

void MatrixObj::drawSelf()
{
	DrawRectangle( //draw background
		this->pos.x,
		this->pos.y,
		MATRIX_WIDTH,
		MATRIX_HEIGHT,
		MATRIX_INTERVAL_COLOR
	);
	for (int r = 0; r < MATRIX_ROW_NUM;++r) {
		for (int c = 0; c < MATRIX_COL_NUM; ++c) {
			const int& x = this->pos.x + (c * (TILE_INTERVAL_WIDTH + TILE_WIDTH)) + TILE_INTERVAL_WIDTH ;
			const int& y = this->pos.y + (r * (TILE_INTERVAL_WIDTH + TILE_HEIGHT))+ TILE_INTERVAL_WIDTH ;
			DrawRectangle( //draw interval tile
				x,
				y,
				TILE_WIDTH,
				TILE_HEIGHT,
				MATRIX_BACKGROUND_COLOR
			);
		}
	}
}
