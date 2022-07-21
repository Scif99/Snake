#pragma once
#include "game_state.h"
#include "play_game.h"
#include "start_menu.h"

#include <memory>
#include "game.h"


class GameOver : public GameState
{
public:

	GameOver(std::shared_ptr<Context> context);
	~GameOver() {}; //Default
	void HandleEvents() override;
	void Update() {};
	void Draw() override;

private:
	std::shared_ptr<Context> pContext;
	int curr_index; //index of the highlighted item
	sf::Font font;
	sf::Text items[2];
};