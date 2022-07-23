#include <SFML/Graphics.hpp>
#include "game.h"
#include "start_menu.h"

#include <iostream>


Game::Game()
	: context{std::make_shared<Context>()}
{
	context->window->create(sf::VideoMode(500, 500), "Snake"); //Create a 500 x 500 window
	context->window->setFramerateLimit(10); //hack to fix timesteps
	context->state_man->AddState(std::make_unique<StartMenu>(context), false); //Game always starts in the Start Menu
}


//Game loop
//TODO Implement timing correctly
void Game::run() 
{
	sf::Clock clock;
	while (context->window->isOpen())
	{
		sf::Time elapsed = clock.restart();

		context->state_man->CurrentState()->HandleEvents();
		context->state_man->CurrentState()->Update(elapsed);
		context->state_man->CurrentState()->Draw();
	}
}
