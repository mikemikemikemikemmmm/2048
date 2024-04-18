#include "game.h"

Game::Game()
{
	this->initWindow();
	this->initGame();
}


void Game::startAnimation()
{
	 currentAnimationFrame= 0;
}

void Game::listenKeyPress()
{
		if (IsKeyPressed(KEY_RIGHT)) {
			objManagerPtr->whenKeyPress(KeyPressDirection::RIGHT);
			startAnimation();
		}
		else if (IsKeyPressed(KEY_LEFT)) {
			objManagerPtr->whenKeyPress(KeyPressDirection::LEFT);			
			startAnimation();
		}
		else if (IsKeyPressed(KEY_UP)) {
			objManagerPtr->whenKeyPress(KeyPressDirection::UP);
			startAnimation();
		}
		else if (IsKeyPressed(KEY_DOWN)) {
			objManagerPtr->whenKeyPress(KeyPressDirection::DOWN);
			startAnimation();
		};
}

void Game::initWindow()
{
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "2048");
	SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	SetTargetFPS(TARGET_FPS);
	std::srand(static_cast<unsigned int>(time(NULL)));
}

void Game::initGame()
{
	previousTime = std::chrono::steady_clock::now();
	objManagerPtr = std::make_unique<ObjManager>();
	currentAnimationFrame = 0;
	handleGameLoop();
}


bool Game::isAnimating()
{
	return currentAnimationFrame < TILE_ANIMATION_COST_FRAME;
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
			ClearBackground(GAME_BACKGROUND_COLOR);
			BeginDrawing();
			objManagerPtr->drawAllObj();
			EndDrawing();
			if (isAnimating()) {
				++currentAnimationFrame;
			}
			else if (objManagerPtr->checkIsGameOver()) {
				LOG("game over");
			}
			else if (objManagerPtr->checkIsGameWin()) {
				LOG("game win");
			}
			else if(!isAnimating()){
				listenKeyPress();
			}
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
