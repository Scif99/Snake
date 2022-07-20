#include <SFML/Graphics.hpp>


#include "game.h"
#include "start_menu.h"



/// <summary>
/// Game starts in the StartMenu state
/// </summary>
Game::Game()
	: window{ sf::VideoMode(500, 500), "Snake" }
{
	state = new StartMenu(this);
}


//The run() function handles updating the state of the game
void Game::run() 
{
	while (window.isOpen())
	{
		//Handle events/input
		sf::Event event;
		state->HandleEvents(event);

		//state->Update(); //for changing state?
		 
		//Draw onto windo
		window.clear();
		state->draw(window, sf::RenderStates::Default);
		window.display();
	}

}

void Game::ChangeState(GameState* next_state)
{
	state = next_state;
}