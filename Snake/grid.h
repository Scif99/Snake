#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Grid
{
public:
	Grid(int dim, float window_size);
	~Grid();

	void draw();

private:
	std::vector<sf::RectangleShape> m_grid;
};