#include <SFML/Graphics.hpp>
#include "game.h"
#include "start_menu.h"

#include <iostream>

Game::Game()
	: context{std::make_shared<Context>()}
{
	
	context->window->create(sf::VideoMode(500, 500), "Snake");
	context->window->setFramerateLimit(10); //hack to fix timesteps
	context->state = std::make_unique<StartMenu>(context); //Game always starts in the StartMenu state


}


//The run() function handles updating the state of the game
//TODO Implement timing correctly
void Game::run() 
{
	while (context->window->isOpen())
	{

		context->state->HandleEvents();

		context->state->Update(); 
		
		context->window->clear();
		context->state->Draw();
		context->window->display();
	}

}
