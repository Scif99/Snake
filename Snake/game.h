#pragma once
#include "game_state.h"
#include "snake.h"

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	sf::RenderWindow window;
	GameState* state;
	//assets
	Snake snake;
};