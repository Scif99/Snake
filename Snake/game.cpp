#include <SFML/Graphics.hpp>
#include "game.h"
#include "start_menu.h"

#include <iostream>




Game::Game()
	: context{std::make_shared<Context>()}
{
	
	context->window->create(sf::VideoMode(500, 500), "Snake");
	context->window->setFramerateLimit(10); //hack to fix timesteps
	context->state = std::make_unique<StartMenu>(context); //Game always starts in the Start Menu
}


//Game loop
//TODO Implement timing correctly
void Game::run() 
{
	sf::Clock clock;
	while (context->window->isOpen())
	{
		sf::Time elapsed = clock.restart();
		context->state->HandleEvents();
		context->state->Update(elapsed); 	
		context->state->Draw();
	}
}
