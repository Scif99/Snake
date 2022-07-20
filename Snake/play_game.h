#pragma once
#include "game_state.h"
#include "snake.h"
#include "game.h"
#include <vector>
#include <cstdlib>

class PlayGame : public GameState
{
public:
	PlayGame(std::unique_ptr<Game> game);
	~PlayGame() {};
	void HandleEvents() override;
	void Update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::unique_ptr<Game> pGame;
	Snake snake;
	std::pair<int, int> apple;
	std::vector<sf::RectangleShape> grid;
	int grid_dim;
	//bool game_over;
};