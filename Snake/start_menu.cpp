#include "start_menu.h"
#include "play_game.h"

#include <memory>
#include <SFML/Graphics.hpp>
#include <iostream>

#define ITEM_SIZE 3

StartMenu::StartMenu(std::shared_ptr<Context>& context)
	: pContext{ context }, curr_index{ 0 }
{
	if (!font.loadFromFile("arial.ttf"))
	{
		//handle error
	}

	items[0].setFont(font);
	items[0].setFillColor(sf::Color::White);
	items[0].setString("Play");
	items[0].setPosition(sf::Vector2f(context->window->getSize().x / 2, context->window->getSize().y / (ITEM_SIZE + 1) * 1)); //3 items...

	items[1].setFont(font);
	items[1].setFillColor(sf::Color::White);
	items[1].setString("Options");
	items[1].setPosition(sf::Vector2f(context->window->getSize().x / 2, context->window->getSize().y / (ITEM_SIZE + 1) * 2));

	items[2].setFont(font);
	items[2].setFillColor(sf::Color::White);
	items[2].setString("Exit");
	items[2].setPosition(sf::Vector2f(context->window->getSize().x / 2, context->window->getSize().y / (ITEM_SIZE + 1) * 3));

	items[curr_index].setFillColor(sf::Color::Red); //Highlight 
}



void StartMenu::HandleEvents()
{
	sf::Event event;
	while (pContext->window->pollEvent(event))
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
				break;
			case sf::Keyboard::Down:
				if (curr_index < ITEM_SIZE-1)
				{
					items[curr_index].setFillColor(sf::Color::White);
					++curr_index;
					items[curr_index].setFillColor(sf::Color::Red);
				}
				break;
			case sf::Keyboard::Return:
				if(curr_index== 2) {
					pContext->window->close();
				}
				else if(curr_index==0)
				{
					pContext->state_man->AddState(std::make_unique<PlayGame>(pContext), true);
					return; //After switching context, exit loop.
				}
				break;

			case sf::Keyboard::Escape:
				pContext->window->close();
			}
		}
	}
	

}

void StartMenu::Draw()
{
	pContext->window->clear();
	for (const auto& item : items)
	{
		pContext->window->draw(item);
	}
	pContext->window->display();
}