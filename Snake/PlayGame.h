#pragma once
#include "game_state.h"

class PlayGame : public GameState
{
public:
	PlayGame(Game* game);
	~PlayGame() {};
	void HandleEvents(sf::Event event) override;
	void Update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};