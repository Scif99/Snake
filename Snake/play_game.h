#pragma once
#include "game_state.h"
#include "snake.h"
#include <vector>
#include <cstdlib>

class PlayGame : public GameState
{
public:
	PlayGame(Game* game);
	~PlayGame() {};
	void HandleEvents(sf::Event event) override;
	void Update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	Game* pGame;
	Snake snake;
	std::pair<int, int> apple;
	std::vector<sf::RectangleShape> grid;
	int grid_dim;
	//bool game_over;
};