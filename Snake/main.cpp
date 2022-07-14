#include <SFML/Graphics.hpp>

#include "snake.h"


#include <vector>
#include <iostream>
#include <utility>
#include <cstdlib>
#include <chrono>
#include <thread>

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Snake");


    //Create a grid that contains the nodes
    constexpr int grid_dim = 20;
    std::vector<sf::RectangleShape> grid;

    //Constants
    int node_size= 25; 

    //Fill the grid
    for (int y = 0;y < grid_dim;++y)
    {
        for (int x = 0;x < grid_dim;++x)
        {
            sf::RectangleShape node(sf::Vector2f(node_size, node_size));
            //node.setFillColor(sf::Color::Black);
            //node.setOutlineColor(sf::Color::White);
            node.setOutlineThickness(-0.5f);
            node.setPosition(sf::Vector2f(x * node_size, y*node_size));
            grid.push_back(node);
        }

    }

    bool show_outline = false; //Toggle grid lines

    //Initialise snake
    std::pair<int, int> start_pos{ 10,10 };
    Snake snake(10, 10);
 
    //Set coordinates for apple
    std::pair<int, int> apple(rand()%grid_dim, rand()%grid_dim); //x,y

    //**SHOULD DECREASE AS SNAKE INCREASES
    sf::Time interval = sf::milliseconds(100);
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {

                //Toggle to show outline of grid
                if (event.key.code == sf::Keyboard::Tab)
                {
                    show_outline = !show_outline;
                }

                //Movement
                //Note that the snake is not allowed to turn 180 degrees (i.e turn in on itself)
                if (event.key.code == sf::Keyboard::Up && snake.front().direction != std::make_pair(0,1))
                {
                    snake.front().direction = {0,-1};
                }

                if (event.key.code == sf::Keyboard::Down && snake.front().direction != std::make_pair(0, -1))
                {
                    snake.front().direction = { 0,1 };
                }

                if (event.key.code == sf::Keyboard::Left && snake.front().direction != std::make_pair(1, 0))
                {
                    snake.front().direction = { -1,0 };
                }

                if (event.key.code == sf::Keyboard::Right && snake.front().direction != std::make_pair(-1,0))
                {
                    snake.front().direction = {1,0 };
                }
                //std::cout << "x: " << snake.front().location.first << "\ty: " << snake.front().location.second << '\n'; //Log

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
        if (snake.intersect() || snake.front().location.first < 0 || snake.front().location.first >= grid_dim || snake.front().location.second < 0 || snake.front().location.second >= grid_dim)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); //Pause for a while when you lose
            snake.reset();

            //Reset apple too
            apple.first = rand() % grid_dim;
            apple.second = rand() % grid_dim; //x,y
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
                curr.setOutlineThickness(-float(show_outline) / 2.f);
                curr.setFillColor(sf::Color::Black);
                //Need to check if this point is occupied by any of the snake pieces
                if(snake.contains(x,y))
                {
                    curr.setFillColor(sf::Color::Green);
                }

                if (x == apple.first && y == apple.second) //Apple is on this node
                {
                    curr.setFillColor(sf::Color::Red);
                }
                window.draw(grid[y * grid_dim + x]);
            }
        }
        window.display();
    }

    return 0;
}
