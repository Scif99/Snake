#include "pause_menu.h"
#include "play_game.h"

PauseMenu::PauseMenu(std::shared_ptr<Context>& context)
	: pContext{ context }
{
	if (!font.loadFromFile("arial.ttf"))
	{
		//handle error
	}

	item.setFont(font);
	item.setFillColor(sf::Color::White);
	item.setString("PAUSED");
	item.setPosition(sf::Vector2f(context->window->getSize().x / 2, context->window->getSize().y / 2 ));
}

void PauseMenu::HandleEvents()
{
	sf::Event event;
	while (pContext->window->pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				pContext->state_man->RemoveState(); //TO_DO
			return;
		}

	}
}

void PauseMenu::Draw()
{
	pContext->window->clear();
	pContext->window->draw(item);
	pContext->window->display();
}