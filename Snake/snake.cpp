
#include <utility>
#include <vector>
#include <unordered_map>
#include <string>
#include <utility>

//A snake is comprised of a number of pieces
//Each piece consists of a pair of coordinates representing it's position on the grid
//Each piece also contains a and a 
struct piece {
	std::pair<int, int> location;

};

class Snake
{
public:
	Snake(int x, int y) {}

	void set_position(int x, int y);

private:
	std::vector<std::pair<int, int>> body; //The snake is  a vector of coordinate pairs
	std::unordered_map<std::string, std::pair<int, int>> directions{ {"UP",{-1,0}},
																	 {"Down",{0,1}},
																	 {"LEFT",{-1,0}},
																	 {"RIGHT",{1,0}} };
};