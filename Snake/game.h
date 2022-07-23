#pragma once
#include "game_state.h"

#include <memory>
#include <stack>
#include <vector>
#include "state_manager.h"



struct Context
{
	std::unique_ptr<StateManager> state_man;
	std::unique_ptr<sf::RenderWindow> window;

	Context()  
		: window{ std::make_unique<sf::RenderWindow>() }, state_man{ std::make_unique<StateManager>() } {}
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