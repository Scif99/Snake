#pragma once
#include <SFML/Graphics.hpp>
#include "game_state.h"


class StartMenu : public GameState
{
public:
	StartMenu(Game* game);
	~StartMenu() {};
	void HandleEvents(sf::Event event) override;
	void Update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	Game* pGame;
	int curr_index; //index of the highlighted item
	float width;
	float height;
	sf::Font font;
	sf::Text items[3];
	

};