#include "start_menu.h"
#include "game.h"
#include "play_game.h"

#include <memory>
#include <SFML/Graphics.hpp>

StartMenu::StartMenu(std::unique_ptr<Game> game)
	: GameState(std::move(game)), curr_index{ 0 },width{pGame->window.getSize().x}, height{pGame->window.getSize().y}
{
	if (!font.loadFromFile("arial.ttf"))
	{
		//handle error
	}

	items[0].setFont(font);
	items[0].setFillColor(sf::Color::White);
	items[0].setString("Play");
	items[0].setPosition(sf::Vector2f(width / 2, height / (3 + 1) * 1)); //3 items...

	items[1].setFont(font);
	items[1].setFillColor(sf::Color::White);
	items[1].setString("Options");
	items[1].setPosition(sf::Vector2f(width / 2, height / (3 + 1) * 2));

	items[2].setFont(font);
	items[2].setFillColor(sf::Color::White);
	items[2].setString("Exit");
	items[2].setPosition(sf::Vector2f(width / 2, height / (3 + 1) * 3));

	items[curr_index].setFillColor(sf::Color::Red); //Highlight 
}



void StartMenu::HandleEvents()
{
	sf::Event event;
	while (pGame->window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			
			case sf::Keyboard::Up:
				if (curr_index > 0)
				{
					items[curr_index].setFillColor(sf::Color::White);
					--curr_index;
					items[curr_index].setFillColor(sf::Color::Red);
				}
			case sf::Keyboard::Down:
				if (curr_index < 2)
				{
					items[curr_index].setFillColor(sf::Color::White);
					++curr_index;
					items[curr_index].setFillColor(sf::Color::Red);
				}
			case sf::Keyboard::Return:
				//pGame->ChangeState(std::make_unique<PlayGame>());
				break;
			}
		}

	}
	

}

void StartMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& item : items)
	{
		target.draw(item, states);
	}

}