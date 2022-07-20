#pragma once
#include <SFML/Graphics.hpp>

class Game {};

//An abstract class
class GameState : sf::Drawable
{
public:
	GameState();
	virtual ~GameState() = default; //Default
	virtual void Init() = 0;
	virtual void HandleInput(sf::Event event) = 0;
	virtual void Update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override; 
	
private:
	Game* pGame;

};






class Paused : public GameState
{

};

class GameOver : public GameState
{};