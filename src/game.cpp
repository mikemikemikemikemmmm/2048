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
	if (state == State::Playing) {
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
	else if (state== State::GameWin && IsKeyPressed(KEY_ENTER)) {
		initGame();
	}
	else if (state ==State::GameOver && IsKeyPressed(KEY_ENTER)) {
		initGame();
	}
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
	setState(State::Playing);
	previousTime = std::chrono::steady_clock::now();
	objManagerPtr = std::make_unique<ObjManager>();
	currentAnimationFrame = 0;
	handleGameLoop();
}


void Game::setState(const State& state)
{
	this->state = state;
}

const bool Game::isAnimating() const
{
	return currentAnimationFrame < TILE_ANIMATION_COST_FRAME;
}
void Game::handleGameLoop()
{
	while (!WindowShouldClose()) {
		#ifdef _DEBUG
		const auto currentTime = std::chrono::steady_clock::now();
		const auto delta_time =
			std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previousTime).count();
		lag += delta_time;
		previousTime += std::chrono::milliseconds(delta_time);
		while (lag >= FRAME_COST_MILLSECOND) {
			lag = 0;
		#endif
			handleDraw();
			if (isAnimating()) {
				++currentAnimationFrame;
			}
			else if (objManagerPtr->checkIsGameOver()) {
				setState(State::GameOver);
				listenKeyPress();
			}
			else if (objManagerPtr->checkIsGameWin()) {
				setState(State::GameWin);
				listenKeyPress();
			}
			else if(!isAnimating()){
				listenKeyPress();
			}
		#ifdef _DEBUG
		}
		#endif
	}
	if (WindowShouldClose()) {
		handleCloseWindow();
	}
}

void Game::handleCloseWindow()
{
	CloseWindow();
}

void Game::handleDraw()
{
	BeginDrawing();
	ClearBackground(GAME_BACKGROUND_COLOR);
	objManagerPtr->drawAllObj();
	if (state == State::GameOver) {
		drawGameStateText(GAME_OVER_TEXT);
	}
	else if (state == State::GameWin) {
		drawGameStateText(GAME_WIN_TEXT);
	}
	EndDrawing();
}

void Game::drawGameStateText(
	const std::vector<std::string>& textVector
)
{
	DrawRectangle(
		0,
		0,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		GAME_STATE_BACKGROUND_COLOR
	);
	const int vectorLen = static_cast<int>(textVector.size());
	const int singleYSectionHeight = WINDOW_HEIGHT / ((2 * vectorLen) + 1);
	for (int i = 0; i < vectorLen; ++i) {
		const char* textChar = textVector[i].c_str();
		Vector2 textSize = MeasureTextEx(GetFontDefault(), textChar, FONT_SIZE, 0);
		const int startX = static_cast<int>((WINDOW_WIDTH - textSize.x) / 2);
		const int startY = static_cast<int>(((2 * i) + 1) * singleYSectionHeight);
		DrawText(
			textChar,
			startX,
			startY,
			FONT_SIZE,
			WHITE
		);
	}
};


