#pragma once
#include <SFML/Graphics.hpp>
#include "game_state.h"
#include "game.h"

//struct Context; //forward declaration

class StartMenu : public GameState
{
public:
	StartMenu(std::shared_ptr<Context>& context);
	~StartMenu() {};
	void HandleEvents() override;
	void Update(sf::Time elapsed) {};
	void Draw() override;

private:
	std::shared_ptr<Context> pContext;
	int curr_index; //index of the highlighted item
	sf::Font font;
	sf::Text items[3];
};