#pragma once
#include <ctime> 
#include <chrono> 
#include <memory> 
#include <iostream> 
#include "objManager.h"
class Game {
private:
	enum class State {
		Playing,GameOver,GameWin
	};
	std::unique_ptr<ObjManager> objManagerPtr;
	std::chrono::time_point<std::chrono::steady_clock> previousTime;
	long long lag = 0;
	State state = State::Playing;
	int currentAnimationFrame = TILE_ANIMATION_COST_FRAME;
	const bool isAnimating() const;
	void setState(const State& state);
	void startAnimation();
	void listenKeyPress();
	void initWindow();
	void initGame();
	void handleGameLoop();
	void handleCloseWindow();
	void handleDraw();
	void drawGameStateText(const std::vector<std::string>& textVector);
public:
	Game();
};