#pragma once

#include <array>
#include <vector>
#include <string>
#include <iostream>

#include "../lib/raylib/include/raylib.h"

#include "struct/position.h"

#ifdef _DEBUG
#define LOG(a) std::cout <<a <<std::endl
#endif

//tile
constexpr int TILE_ANIMATION_COST_FRAME = 4;
constexpr int TILE_INTERVAL_WIDTH = TILE_ANIMATION_COST_FRAME*3;//should be divisible by ANIMATION_COST_FRAME.
constexpr int TILE_WIDTH = TILE_ANIMATION_COST_FRAME *30;//should be divisible by ANIMATION_COST_FRAME.
constexpr int TILE_HEIGHT = TILE_ANIMATION_COST_FRAME * 30;//should be divisible by ANIMATION_COST_FRAME.
constexpr float TILE_SCALE_START = static_cast<float>(0.1);  //10%
constexpr float TILE_SCALE_VAR = static_cast<float>((1- TILE_SCALE_START)/ TILE_ANIMATION_COST_FRAME);

//font
constexpr int FONT_SIZE = static_cast<int>(TILE_WIDTH / 3.5);

//tile level
constexpr int TILE_MAX_LEVEL = 10;
constexpr int TILE_START_LEVEL = 0;
constexpr std::array< Color, TILE_MAX_LEVEL+1> TILE_INNER_COLOR_LIST{
	Color{238,228,218,255},
	Color{238,225,201,255},
	Color{243,178,122,255},
	Color{246,150,100,255},
	Color{247,124,95,255},
	Color{247,95,59,255},
	Color{237,208,115,255},
	Color{237,204,98,255},
	Color{237,201,80,255},
	Color{237,197,63,255},
	Color{237,194,46,255}
};
constexpr std::array< Color, TILE_MAX_LEVEL + 1> TILE_FONT_COLOR_LIST{
	Color{119,110,101,255},
	Color{119,110,101,255},
	Color{ 249,246,242,255 },
	Color{ 249,246,242,255 },
	Color{ 249,246,242,255 },
	Color{ 249,246,242,255 },
	Color{ 249,246,242,255 },
	Color{ 249,246,242,255 },
	Color{ 249,246,242,255 },
	Color{ 249,246,242,255 },
	Color{ 249,246,242,255 }
	};
constexpr std::array<const char*, TILE_MAX_LEVEL+1> TILE_TEXT_LIST{
	"2","4","8","16","32","64","128","256","512","1024","2048"
};


//matrix
constexpr int MATRIX_START_X = 40;
constexpr int MATRIX_START_Y = 40;
constexpr int MATRIX_ROW_NUM = 4;
constexpr int MATRIX_COL_NUM = 4;
constexpr int MATRIX_WIDTH = MATRIX_COL_NUM * (TILE_INTERVAL_WIDTH + TILE_WIDTH) + TILE_INTERVAL_WIDTH;
constexpr int MATRIX_HEIGHT = MATRIX_ROW_NUM * (TILE_INTERVAL_WIDTH + TILE_HEIGHT) + TILE_INTERVAL_WIDTH;
constexpr Color MATRIX_BACKGROUND_COLOR{ 205,193,180,255 };
constexpr Color MATRIX_INTERVAL_COLOR{ 187,173,160,255 };


//system
constexpr int WINDOW_WIDTH = MATRIX_START_X *2+ MATRIX_WIDTH;
constexpr int WINDOW_HEIGHT = MATRIX_START_Y*2 + MATRIX_HEIGHT;
constexpr int TARGET_FPS = 60;
enum class KeyPressDirection {
	UP, RIGHT, DOWN, LEFT
};
constexpr Color GAME_BACKGROUND_COLOR  { 250,248,239,255 };
constexpr int FRAME_COST_MILLSECOND = 0;//for debug to control frame speed


//game state
const std::vector< std::string> GAME_OVER_TEXT{ 
	"Game Over!!",
	"Press Enter to",
	"start new game." 
};
const std::vector< std::string>GAME_WIN_TEXT{
	"You Win!!",
	"Press Enter to", 
	"start new game."
};
constexpr Color GAME_STATE_BACKGROUND_COLOR{ 0,0,0,200};