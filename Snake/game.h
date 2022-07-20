#pragma once
#include "game_state.h"
#include "snake.h"

class Game
{
public:
	Game();
	~Game() {};

	void run();
	void ChangeState(GameState*); //Change the state of the game
	sf::RenderWindow window;
	
private:
	GameState* state;

	//assets
	Snake snake;
};