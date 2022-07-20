#pragma once
#include <SFML/Graphics.hpp>
#include "game_state.h"


class StartMenu : public GameState
{
public:
	StartMenu(std::unique_ptr<Game> game);
	~StartMenu() {};
	void HandleEvents() override;
	void Update() {};
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::unique_ptr<Game> pGame;
	int curr_index; //index of the highlighted item
	unsigned int width;
	unsigned int height;
	sf::Font font;
	sf::Text items[3];
};