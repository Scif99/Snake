#include "play_game.h"
#include <thread>
#include <chrono>

PlayGame::PlayGame(std::unique_ptr<Game> game)
    : GameState(std::move(game)), snake( 10,10 ), apple(rand() % grid_dim, rand() % grid_dim), grid_dim(20) //, game_over(false) //Apple should be rando
{
    //Constants
    int node_size = pGame->window.getSize().x / grid_dim; //size of the node in pixels 

    //Fill the grid
    for (int y = 0;y < grid_dim;++y)
    {
        for (int x = 0;x < grid_dim;++x)
        {
            sf::RectangleShape node(sf::Vector2f(node_size, node_size));
            node.setPosition(sf::Vector2f(x * node_size, y * node_size));
            node.setFillColor(sf::Color::Green);
            grid.push_back(node);
        }

    }

}

void PlayGame::HandleEvents()
{
    sf::Event event;
    while (pGame->window.pollEvent(event))
    {

        if (event.type == sf::Event::KeyPressed)
        {

            //Movement
            //Note that the snake is not allowed to turn 180 degrees (i.e turn in on itself)
            if (event.key.code == sf::Keyboard::Up && snake.front().direction != std::make_pair(0, 1))
            {
                snake.front().direction = { 0,-1 };
                break;
            }

            if (event.key.code == sf::Keyboard::Down && snake.front().direction != std::make_pair(0, -1))
            {
                snake.front().direction = { 0,1 };
                break;
            }

            if (event.key.code == sf::Keyboard::Left && snake.front().direction != std::make_pair(1, 0))
            {
                snake.front().direction = { -1,0 };
                break;
            }

            if (event.key.code == sf::Keyboard::Right && snake.front().direction != std::make_pair(-1, 0))
            {
                snake.front().direction = { 1,0 };
                break;
            }
        }
    }

}

void PlayGame::Update()
{
    snake.update_direction();
    snake.update_position();

    //Reset if snake moves out of bounds or collides with itself
    auto front_coords = snake.front().location;
    if (snake.intersect() || std::clamp(front_coords.first, 0, grid_dim - 1) != front_coords.first
        || std::clamp(front_coords.second, 0, grid_dim - 1) != front_coords.second)
    {
        //game_over = true;
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); //Pause for a while when you lose
        snake.reset();

        //Reset apple too
        //But make sure it doesnt spawn inside the snake
        do {
            apple.first = rand() % grid_dim;
            apple.second = rand() % grid_dim; //x,y
        } while (snake.contains(apple.first, apple.second));
    }

    //If the snake eats the apple, spawn apple at a new random point
    if (snake.front().location.first == apple.first && snake.front().location.second == apple.second)
    {
        snake.add_piece(); //Add a piece to the tail of the snake
        apple.first = rand() % grid_dim;
        apple.second = rand() % grid_dim; //x,y
        grid[apple.second * grid_dim + apple.first].setFillColor(sf::Color::Red);
    }


}

//Basically only draw the nodes occupied by snake or appl
//NOT FINISHED
void PlayGame::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (int y = 0;y < grid_dim;++y) 
    {
        for (int x = 0;x < grid_dim;++x)
        {
            int index = y * grid_dim + x;

            sf::RectangleShape curr = grid[index];

            //Need to check if this point is occupied by any of the snake pieces
            if (snake.contains(x, y))
            {
                pGame->window.draw(grid[y * grid_dim + x]);
            }

            if (x == apple.first && y == apple.second) //Apple is on this node
            {
                pGame->window.draw(grid[y * grid_dim + x]);
            }
            //window.draw(grid[y * grid_dim + x]);
        }
    }

}