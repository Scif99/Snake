#include "play_game.h"
#include <thread>
#include <chrono>


#define GRID_DIM 20

PlayGame::PlayGame(std::shared_ptr<Context> context)
    : pContext{ context }, snake{ 10, 10 }, apple{ rand() % GRID_DIM, rand() % GRID_DIM}//, game_over(false) //Apple should be rando
{
    //Constants
    int node_size = pContext->window->getSize().x / GRID_DIM; //size of the node in pixels 

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
    if (snake.intersect() || std::clamp(front_coords.first, 0, GRID_DIM - 1) != front_coords.first
        || std::clamp(front_coords.second, 0, GRID_DIM - 1) != front_coords.second)
    {
        pContext->ChangeState(std::make_unique<GameOver>(pContext));
        return;
        //std::this_thread::sleep_for(std::chrono::milliseconds(500)); //Pause for a while when you lose
        //snake.reset();

        ////Reset apple too
        ////But make sure it doesnt spawn inside the snake
        //do {
        //    apple.first = rand() % GRID_DIM;
        //    apple.second = rand() % GRID_DIM; //x,y
        //} while (snake.contains(apple.first, apple.second));
    }

    //If the snake eats the apple, spawn apple at a new random point
    if (snake.front().location.first == apple.first && snake.front().location.second == apple.second)
    {
        snake.add_piece(); //Add a piece to the tail of the snake
        apple.first = rand() % GRID_DIM;
        apple.second = rand() % GRID_DIM; //x,y
        grid[apple.second * GRID_DIM + apple.first].setFillColor(sf::Color::Red);
    }


}

//Basically only draw the nodes occupied by snake or appl
//NOT FINISHED
void PlayGame::Draw()
{
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

}