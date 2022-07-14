#pragma once

#include <utility>
#include <vector>
#include <unordered_map>
#include <string>
#include <utility>
#include <SFML/System/Time.hpp>


//A snake is comprised of a number of pieces
//Each piece consists of a pair of coordinates representing it's position on the grid
//Each piece also contains a and a 
struct piece
{
	std::pair<int, int> location;
	std::pair<int, int> direction{ 0,0 };

	piece(int x, int y, int x_dir, int y_dir)
		:location({ x,y }), direction({ x_dir, y_dir }) {}

};

class Snake
{
public:
	Snake(int x, int y)
	{
		body.emplace_back(x, y, 0, 0);
	}
	void add_piece();
	void update_direction();
	void update_position();
	bool contains(int x, int y); //Function that returns true if the node at coordinates (x,y) is a snake piece
	void reset();

	piece& front() { return body[0]; }
	const piece& front() const { return body[0]; }

private:
	std::vector<piece> body; //The snake is  a vector of coordinate pairs. body[0] is the first element
};