#pragma once
#include <SFML/Graphics.hpp>
#include "game.h"


class PauseMenu : public GameState
{
public:
	PauseMenu(std::shared_ptr<Context>& context);
	~PauseMenu() = default; //Default
	void HandleEvents();
	void Update(sf::Time elapsed) {};
	void Draw() ;

private:
	std::shared_ptr<Context> pContext;
	sf::Font font;
	sf::Text item;


};