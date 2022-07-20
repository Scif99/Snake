#pragma once
#include <SFML/Graphics.hpp>

class Game; //Forward declaration

class GameState : sf::Drawable
{
public:
	GameState(std::unique_ptr<Game> game) : pGame{ std::move(game) } {};
	virtual ~GameState() = default; //Default
	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0; 
	//void SetContext(Game game) { pGame = std::make_unique<Game>(); };

protected:
	std::unique_ptr<Game> pGame;

};

