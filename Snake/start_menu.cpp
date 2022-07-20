#include "start_menu.h"

StartMenu::StartMenu()
	: curr_index{ 0 }

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

void StartMenu::HandleInput(sf::Event event)
{

}

void StartMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& item : items)
	{
		target.draw(item, states);
	}

}