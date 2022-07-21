#pragma once
#include "game_state.h"
#include <memory>

struct Context
{
	std::unique_ptr<GameState> state;
	std::unique_ptr<sf::RenderWindow> window;

	Context()  
		: window{ std::make_unique<sf::RenderWindow>() } {}

	void ChangeState(std::unique_ptr<GameState> next_state) {state = std::move(next_state);}
};

class Game
{
public:
	Game();
	~Game() {};
	void run();
private:
	std::shared_ptr<Context> context;
};