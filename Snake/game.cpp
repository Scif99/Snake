#include <SFML/Graphics.hpp>


#include "game.h"
#include "start_menu.h"


Game::Game()
	: window{ sf::VideoMode(500, 500), "Snake" }, state{nullptr}
{
	state = std::make_unique<StartMenu>(std::make_unique<Game>(*this)); //Game always starts in the StartMenu state
}


//The run() function handles updating the state of the game
void Game::run() 
{
	while (window.isOpen())
	{
		//Handle events/input
		state->HandleEvents();

		state->Update(); //for changing state?
		 
		//Draw onto windo
		window.clear();
		state->draw(window, sf::RenderStates::Default);
		window.display();
	}

}

void Game::ChangeState(std::unique_ptr<GameState> next_state)
{
	state = std::move(next_state);
}