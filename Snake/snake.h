#pragma once

#include <utility>
#include <vector>
#include <unordered_map>
#include <string>
#include <utility>
#include <SFML/System/Time.hpp>


//A piece is a node representing a part of the snake
//Each piece consists of a pair of coordinates representing it's position on the grid
//Each piece also contains direction, represented by a 2d unit vector
struct piece
{
	std::pair<int, int> location;
	std::pair<int, int> direction; //(x,y)

	piece(int x, int y, int x_dir, int y_dir)
		:location{ x,y }, direction{ x_dir, y_dir } {}

};


//A snake is a vector of pieces
class Snake
{
public:

	Snake(int x, int y) //Constructor
		:body{ piece{x,y,0,0} } {}


	void add_piece(); //Adds a piece to the tail of the snake, increasing the length of the snake by 1 node
	void update_direction(); //Updates directions of each piece in the snake
	void update_position(); //Updates positions of each piece in the snake
	bool contains(int x, int y) const; //Function that returns true if the node at coordinates (x,y) is a snake piece
	bool intersect() const; //Checks whether the snake has a self-collision
	void reset();

	piece& front() { return body[0]; } 
	const piece& front() const { return body[0]; }
	int size() const { return body.size(); }

private:
	std::vector<piece> body; //The snake is  a vector of coordinate pairs. body[0] is the first element
};