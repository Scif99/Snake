#pragma once
#include <SFML/Graphics.hpp>


//An abstract class
class Game {};

class GameState : sf::Drawable
{
public:
	GameState(Game* game)
		:pGame{ game } {}
	virtual ~GameState() = default; //Default
	virtual void HandleEvents(sf::Event event) = 0;
	virtual void Update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override; 
private:
	Game* pGame;
};

