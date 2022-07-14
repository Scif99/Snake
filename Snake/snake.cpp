#include "snake.h"

void Snake::update_position()
{
	for (auto& piece : body)
	{
		piece.location.first += piece.direction.first;
		piece.location.second += piece.direction.second;
	}
}


void Snake::update_direction()
{
	
	for(int i =1;i<body.size();++i)
	{
		
		body[i].direction.first = body[i - 1].location.first - body[i].location.first;
		body[i].direction.second = body[i - 1].location.second - body[i].location.second;
	}
}


void Snake::add_piece()
{
	piece last_piece = body.back(); 
	std::pair<int, int> new_coords{ last_piece.location.first - last_piece.direction.first, //coords of piece to be added
									last_piece.location.second - last_piece.direction.second }; 
	std::pair<int, int> new_dir{ last_piece.location.first - new_coords.first, last_piece.location.second - new_coords.second };

	body.emplace_back(new_coords.first,new_coords.second,new_dir.first,new_dir.second);
}

bool Snake::contains(int x, int y)
{
	for (const auto& piece : body)
	{
		if (piece.location.first == x && piece.location.second == y) return true;
	}
	return false;
}

//Reset snake to starting point, with only one piece
void Snake::reset()
{
	piece start{ 10,10,0,0 };
	body = { start };
}