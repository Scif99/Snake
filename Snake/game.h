#pragma once
#include "game_state.h"
#include <memory>


class Game
{
public:
	Game();
	~Game() {};

	void run();
	void ChangeState(std::unique_ptr<GameState> next_state); //Change the state of the game
	sf::RenderWindow window;
	
private:
	std::unique_ptr<GameState> state;
};