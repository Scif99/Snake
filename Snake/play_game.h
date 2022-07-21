#pragma once
#include "game_state.h"
#include "snake.h"
#include "game.h"
#include <vector>
#include <cstdlib>

class PlayGame : public GameState
{
public:
	PlayGame(std::shared_ptr<Context> context);
	~PlayGame() {};
	void HandleEvents() override;
	void Update() override;
	virtual void Draw() override;

private:
	std::shared_ptr<Context> pContext;
	Snake snake;
	std::pair<int, int> apple;
	std::vector<sf::RectangleShape> grid;
	int grid_dim{20};
	//bool game_over;
};