#include <SFML/Graphics.hpp>


#include "game.h"
#include "game_state.h"

#include <vector>
#include <iostream>
#include <utility>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <algorithm>

/// <summary>
/// Game starts in the StartMenu state
/// </summary>
Game::Game()
	: window{ sf::VideoMode(500, 500), "Snake" }, snake{10,10} , state{new StartMenu()}
{
	state->Init();



}


//The run() function handles updating the state of the game
void Game::run() 
{
	while (window.isOpen())
	{
		//Handle events/input
		//sf::Event event;
		//state->HandleInput(event);

		state->Update(); //for changing state?
		//window.clear();
		state->draw(window, sf::RenderStates::Default);
		//window.display();
	}

}