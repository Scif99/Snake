#include "play_game.h"
#include <thread>
#include <chrono>
#include <memory>
#include "pause_menu.h"

#define GRID_DIM 20

PlayGame::PlayGame(std::shared_ptr<Context>& context)
    : pContext{ context }, snake{ 10, 10 }, apple{ rand() % GRID_DIM, rand() % GRID_DIM}, tick_rate{10}
{
    //Constants
    int node_size = pContext->window->getSize().x / GRID_DIM; //size of the node in pixels 
    pContext->window->setFramerateLimit(10 + snake.size()); //hack to increase speed

    //Fill the grid
    for (int y = 0;y < GRID_DIM;++y)
    {
        for (int x = 0;x < GRID_DIM;++x)
        {
            sf::RectangleShape node(sf::Vector2f(node_size, node_size));
            node.setPosition(sf::Vector2f(x * node_size, y * node_size));
            grid.push_back(node);
        }

    }

}

void PlayGame::HandleEvents()
{
    sf::Event event;
    while (pContext->window->pollEvent(event))
    {

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
               pContext->state_man->AddState(std::make_unique<PauseMenu>(pContext), false);
                return;
            }

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

void PlayGame::Update(sf::Time elapsed)
{

    snake.update_direction();
    snake.update_position();

    //Reset if snake moves out of bounds or collides with itself
    auto front_coords = snake.front().location;
    if (snake.intersect() || std::clamp(front_coords.first, 0, GRID_DIM - 1) != front_coords.first
        || std::clamp(front_coords.second, 0, GRID_DIM - 1) != front_coords.second)
    {
        pContext->state_man->AddState(std::make_unique<GameOver>(pContext), true);
        return;

    }

    //If the snake eats the apple, spawn apple at a new random point
    if (snake.front().location.first == apple.first && snake.front().location.second == apple.second)
    {
        //++tick_rate;
        snake.add_piece(); //Add a piece to the tail of the snake
        pContext->window->setFramerateLimit(10 + snake.size()); //hack to increase speed
        apple.first = rand() % GRID_DIM;
        apple.second = rand() % GRID_DIM; //x,y
        grid[apple.second * GRID_DIM + apple.first].setFillColor(sf::Color::Red);
    }



}

//Basically only draw the nodes occupied by snake or appl
//NOT FINISHED
void PlayGame::Draw()
{
    pContext->window->clear();
    for (int y = 0;y < GRID_DIM;++y)
    {
        for (int x = 0;x < GRID_DIM;++x)
        {
            int index = y * GRID_DIM + x;

            sf::RectangleShape curr = grid[index];

            //Need to check if this point is occupied by any of the snake pieces
            if (snake.contains(x, y))
            {
                grid[y * GRID_DIM + x].setFillColor(sf::Color::Green);
                pContext->window->draw(grid[y * GRID_DIM + x]);
            }

            if (x == apple.first && y == apple.second) //Apple is on this node
            {
                grid[y * GRID_DIM + x].setFillColor(sf::Color::Red);
                pContext->window->draw(grid[y * GRID_DIM + x]);
            }
            //window.draw(grid[y * grid_dim + x]);
        }
    }

    pContext->window->display();

}