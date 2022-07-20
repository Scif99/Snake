#include <SFML/Graphics.hpp>

#include "snake.h"
#include "start_menu.h"

#include <vector>
#include <iostream>
#include <utility>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <algorithm>

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Snake");
    window.setKeyRepeatEnabled(false);

    //Create a grid that contains the nodes
    constexpr int grid_dim = 20; //number of rows/columns
    std::vector<sf::RectangleShape> grid;

    //Constants
    int node_size= window.getSize().x / grid_dim; //size of the node in pixels 

    //Fill the grid
    for (int y = 0;y < grid_dim;++y)
    {
        for (int x = 0;x < grid_dim;++x)
        {
            sf::RectangleShape node(sf::Vector2f(node_size, node_size));
            node.setPosition(sf::Vector2f(x * node_size, y*node_size));
            grid.push_back(node);
        }

    }

    //Initialise snake
    Snake snake(10, 10);
 
    //Set coordinates for apple
    std::pair<int, int> apple(rand()%grid_dim, rand()%grid_dim); //x,y

    //**SHOULD DECREASE AS SNAKE INCREASES
    sf::Time interval = sf::milliseconds(100);
    sf::Clock clock;

    StartMenu start(window.getSize().x, window.getSize().y); 


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {

                //Movement
                //Note that the snake is not allowed to turn 180 degrees (i.e turn in on itself)
                if (event.key.code == sf::Keyboard::Up && snake.front().direction != std::make_pair(0,1))
                {
                    snake.front().direction = {0,-1};
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

                if (event.key.code == sf::Keyboard::Right && snake.front().direction != std::make_pair(-1,0))
                {
                    snake.front().direction = {1,0 };
                    break;
                }
            }
        }

        //Update position
        sf::Time elapsed1 = clock.getElapsedTime();
        snake.update_direction();
        


        if (elapsed1 > interval)
        {
            
            snake.update_position();
            clock.restart();
        }

        //Reset if snake moves out of bounds or collides with itself
        auto front_coords = snake.front().location;
        if (snake.intersect() || std::clamp(front_coords.first, 0, grid_dim - 1) != front_coords.first 
            || std::clamp(front_coords.second,0,grid_dim-1) !=front_coords.second)
        {
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
        }


        //Draw
        window.clear();
        for (int y = 0;y < grid_dim;++y)
        {
            for (int x = 0;x < grid_dim;++x)
            {
                int index = y * grid_dim + x;

                sf::RectangleShape& curr = grid[index];

                //Need to check if this point is occupied by any of the snake pieces
                if(snake.contains(x,y))
                {
                    curr.setFillColor(sf::Color::Green);
                    window.draw(grid[y * grid_dim + x]);
                }

                if (x == apple.first && y == apple.second) //Apple is on this node
                {
                    curr.setFillColor(sf::Color::Red);
                    window.draw(grid[y * grid_dim + x]);
                }
                //window.draw(grid[y * grid_dim + x]);
            }
        }
        window.display();
    }

    return 0;
}
