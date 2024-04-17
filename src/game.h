#pragma once
#include <ctime> 
#include <chrono> 
#include <memory> 
#include <iostream> 
#include "objManager.h"
#define LOG(a) std::cout <<a <<std::endl;
class Game {
public:
	std::unique_ptr<ObjManager> objManagerPtr;
	std::chrono::time_point<std::chrono::steady_clock> previousTime;
	long long lag = 0;
	Game();
	void listenKeyPress();
	void initWindow();
	void initGame();
	void handleGameLoop();
	void handleCloseWindow();
};