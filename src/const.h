#pragma once

#include <array>
#include <string>

#include "../lib/raylib/include/raylib.h"

//matrix
constexpr int MATRIX_START_X = 0; 
constexpr int MATRIX_START_Y = 0;
constexpr int MATRIX_ROW_NUM = 4;
constexpr int MATRIX_COL_NUM = 4;
constexpr Color MATRIX_TILE_COLOR = GRAY;
constexpr Color MATRIX_INTERVAL_COLOR = BLUE;

//tile
constexpr int TILE_FONT_SIZE = 70;
constexpr Color TILE_FONT_COLOR = BLACK;
constexpr int TILE_INTERVAL_WIDTH = 10;
constexpr int TILE_WIDTH = 150;
constexpr int TILE_HEIGHT = 150;
constexpr  int TILE_MAX_LEVEL = 10;
constexpr  std::array<const char*, TILE_MAX_LEVEL+1> TILE_TEXT_LIST{
	"2","4","8","16","32","64","128","256","512","1024","2048"
};
constexpr  std::array<Color, TILE_MAX_LEVEL+1> TILE_COLOR_LIST{
	YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW
};//TODO
constexpr int TILE_BASE_SPEED = 5; 
constexpr float TILE_SCALE_VAR = static_cast <float>(0.3);
constexpr float TILE_SCALE_START = static_cast <float>(0.2);
constexpr float TILE_SCALE_DELETED_THRESHOLD = TILE_SCALE_VAR * 2;

//system
constexpr int SCREEN_WIDTH = MATRIX_COL_NUM * (TILE_INTERVAL_WIDTH + TILE_WIDTH) + TILE_INTERVAL_WIDTH;
constexpr int SCREEN_HEIGHT = MATRIX_ROW_NUM * (TILE_INTERVAL_WIDTH + TILE_WIDTH) + TILE_INTERVAL_WIDTH;
constexpr int TARGET_FPS = 60;
constexpr int FRAME_COST_MILLSECOND = 30;
enum class KeyPressDirection {
	UP, RIGHT, DOWN, LEFT
};
