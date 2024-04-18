#pragma once
#include <ctime> 
#include <chrono> 
#include <memory> 
#include <iostream> 
#include "objManager.h"
class Game {
private:
	std::unique_ptr<ObjManager> objManagerPtr;
	std::chrono::time_point<std::chrono::steady_clock> previousTime;
	long long lag = 0;
	int currentAnimationFrame = TILE_ANIMATION_COST_FRAME;
	bool isAnimating();
	void startAnimation();
	void listenKeyPress();
	void initWindow();
	void initGame();
	void handleGameLoop();
	void handleCloseWindow();
public:
	Game();
};