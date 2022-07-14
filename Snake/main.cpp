#include <SFML/Graphics.hpp>

#include "grid.cpp"

#include <vector>
#include <iostream>
#include <utility>
#include <cstdlib>
#include <unordered_map>

struct Snake
{
    std::pair<int, int> location;
    std::pair<int, int> direction{0,0};

    Snake(int x, int y)
        :location({ x,y }) {}
};
int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Snake");


    //Create a grid that contains the nodes
    constexpr int grid_dim = 20;
    std::vector<sf::RectangleShape> grid;

    //Constants
    sf::Vector2f node_size(25.f, 25.f); 

    //Fill the grid
    for (int y = 0;y < grid_dim;++y)
    {
        for (int x = 0;x < grid_dim;++x)
        {
            sf::RectangleShape node(node_size);
            node.setFillColor(sf::Color::Black);
            node.setOutlineColor(sf::Color::White);
            node.setOutlineThickness(-0.5f);
            node.setPosition(sf::Vector2f(x * 25.f, y*25.f));
            grid.push_back(node);
        }

    }

    bool show_outline = true;

    //Set initial point for snake
    std::pair<int, int> start_pos{ 10,10 };
    Snake snake(10, 10);
 
    
    std::pair<int, int> apple(rand()%grid_dim, rand()%grid_dim); //x,y



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
                if (event.key.code == sf::Keyboard::Up && snake.direction != std::make_pair(0,1))
                {
                    //--snake.location.second;
                    snake.direction = { 0,-1 };
                }

                if (event.key.code == sf::Keyboard::Down && snake.direction != std::make_pair(0, -1))
                {
                    //++snake.location.second;
                    snake.direction = { 0,1 };
                }

                if (event.key.code == sf::Keyboard::Left && snake.direction != std::make_pair(1, 0))
                {
                    //--snake.location.first;
                    snake.direction = { -1,0 };
                }

                if (event.key.code == sf::Keyboard::Right && snake.direction != std::make_pair(-1,0))
                {
                    //++snake.location.first;
                    snake.direction = {1,0 };
                }

                std::cout << "x: " << snake.location.first << "\ty: " << snake.location.second << '\n';

            }
        }

        //Update position
        snake.location.first += snake.direction.first;
        snake.location.second+= snake.direction.second;


        if (snake.location.first < 0 || snake.location.first >= grid_dim || snake.location.second < 0 || snake.location.second >= grid_dim)
        {
            snake.location = start_pos;
        }







        //If the snake eats the apple, spawn apple at a new random point
        if (snake.location.first == apple.first && snake.location.second == apple.second)
        {
            apple.first = rand() % grid_dim;
            apple.second = rand() % grid_dim; //x,y
        }



        window.clear();
        for (int y = 0;y < grid_dim;++y)
        {
            for (int x = 0;x < grid_dim;++x)
            {
                int index = y * grid_dim + x;
                sf::RectangleShape& curr = grid[index];
                curr.setFillColor(sf::Color::Black);

                curr.setOutlineThickness(-float(show_outline) / 2.f);

                if (x == snake.location.first && y == snake.location.second) //Snake is on this node
                {
                    curr.setFillColor(sf::Color::Green);
                }

                if (x == apple.first && y == apple.second) //Snake is on this node
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
