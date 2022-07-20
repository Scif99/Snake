#pragma once
#include <SFML/Graphics.hpp>
#include "game_state.h"

class StartMenu : public GameState
{
public:
	StartMenu();
	virtual void Init() override;
	virtual void HandleInput(sf::Event event) override;
	//virtual void Update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	float width;
	float height;
	sf::Font font;
	sf::Text items[3];
	int curr_index; //index of the highlighted item

};