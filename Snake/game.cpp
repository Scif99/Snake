#include <SFML/Graphics.hpp>
#include "game.h"
#include "start_menu.h"

#include <iostream>


void Context::ChangeState(std::unique_ptr<GameState> next_state)
{
	if (!state_stack.empty()) { state_stack.pop(); }
	state_stack.emplace(std::move(next_state));
}

Game::Game()
	: context{std::make_shared<Context>()}
{
	context->window->create(sf::VideoMode(500, 500), "Snake");
	context->window->setFramerateLimit(10); //hack to fix timesteps
	context->state_stack.push(std::make_unique<StartMenu>(context)); //Game always starts in the Start Menu
}


//Game loop
//TODO Implement timing correctly
void Game::run() 
{
	sf::Clock clock;
	while (context->window->isOpen())
	{
		sf::Time elapsed = clock.restart();

		context->state_stack.top()->HandleEvents();
		context->state_stack.top()->Update(elapsed);
		context->state_stack.top()->Draw();
	}
}
