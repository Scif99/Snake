#include "game_over.h"

#define ITEM_SIZE 2

GameOver::GameOver(std::shared_ptr<Context> context)
	: pContext{ context }, curr_index{ 0 }
{
	if (!font.loadFromFile("arial.ttf"))
	{
		//handle error
	}

	items[0].setFont(font);
	items[0].setFillColor(sf::Color::White);
	items[0].setString("Retry");
	items[0].setPosition(sf::Vector2f(context->window->getSize().x / 2, context->window->getSize().y / (ITEM_SIZE + 1) * 1)); //3 items...

	items[1].setFont(font);
	items[1].setFillColor(sf::Color::White);
	items[1].setString("Exit");
	items[1].setPosition(sf::Vector2f(context->window->getSize().x / 2, context->window->getSize().y / (ITEM_SIZE + 1) * 2));

	items[curr_index].setFillColor(sf::Color::Red); //Highlight 
}

void GameOver::HandleEvents()
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
				if (curr_index == 1) {
					pContext->window->close();
				}
				else if (curr_index == 0)
				{
					pContext->ChangeState(std::make_unique<PlayGame>(pContext));
					return; //After switching context, exit loop.
				}
				break;

			case sf::Keyboard::Escape:
				pContext->window->close();
			}
		}

	}


}

void GameOver::Draw()
{
	for (const auto& item : items)
	{
		pContext->window->draw(item);
	}

}