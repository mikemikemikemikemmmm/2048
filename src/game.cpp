#include "game.h"

Game::Game()
{
	this->initWindow();
	this->initGame();
}

void Game::listenKeyPress()
{
	if (IsKeyPressed(KEY_RIGHT)) {
		objManagerPtr->whenKeyPress(KeyPressDirection::RIGHT);
	}
	else if (IsKeyPressed(KEY_LEFT)) {
		objManagerPtr->whenKeyPress(KeyPressDirection::LEFT);
	}
	else if (IsKeyPressed(KEY_UP)) {
		objManagerPtr->whenKeyPress(KeyPressDirection::UP);
	}
	else if (IsKeyPressed(KEY_DOWN)) {
		objManagerPtr->whenKeyPress(KeyPressDirection::DOWN);
	}
}

void Game::initWindow()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "2048");
	SetTargetFPS(TARGET_FPS);
	std::srand(static_cast<unsigned int>(time(NULL)));
}

void Game::initGame()
{
	previousTime = std::chrono::steady_clock::now();
	objManagerPtr = std::make_unique<ObjManager>();
	handleGameLoop();
}


void Game::handleGameLoop()
{
	while (!WindowShouldClose()) {
		const auto currentTime = std::chrono::steady_clock::now();
		const auto delta_time =
			std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previousTime).count();
		lag += delta_time;
		previousTime += std::chrono::milliseconds(delta_time);
		while (lag >= FRAME_COST_MILLSECOND) {
			lag = 0;
			BeginDrawing();
			objManagerPtr->drawAllObj();
			if (objManagerPtr->checkIsGameOver()) {
				LOG("game over");
			}
			else if (objManagerPtr->checkIsGameWin()) {
				LOG("game win");
			}
			else {
				listenKeyPress();

			}
			EndDrawing();
		}
	}
	if (WindowShouldClose()) {
		handleCloseWindow();
	}
}

void Game::handleCloseWindow()
{
	CloseWindow();
}
