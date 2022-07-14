#include <SFML/Graphics.hpp>

#include "grid.cpp"

#include <vector>
#include <iostream>
#include <utility>
#include <cstdlib>
int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Snake");


    //Create a grid that contains the nodes
    constexpr int grid_dim = 20;
    std::vector<sf::RectangleShape> grid;

    //Constants

    sf::Vector2f node_size(25.f, 25.f); 

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

    //Set initial point for snake
    std::pair<int, int> snake(10,10); //x,y
    
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
                //Movement
                if (event.key.code == sf::Keyboard::Up && snake.second>0)
                {
                    --snake.second;
                    std::cout << "x: " << snake.first << "\ty: " << snake.second << '\n';
                }

                if (event.key.code == sf::Keyboard::Down && snake.second < grid_dim-1)
                {
                    ++snake.second;
                    std::cout << "x: " << snake.first << "\ty: " << snake.second << '\n';
                }

                if (event.key.code == sf::Keyboard::Left && snake.first > 0)
                {
                    --snake.first;
                    std::cout << "x: " << snake.first << "\ty: " << snake.second << '\n';
                }

                if (event.key.code == sf::Keyboard::Right && snake.first <grid_dim-1)
                {
                    ++snake.first;
                    std::cout << "x: " << snake.first << "\ty: " << snake.second << '\n';
                }


            }
        }

        if (snake.first == apple.first && snake.second == apple.second)
        {
            apple.first = rand() % grid_dim;
            apple.second = rand() % grid_dim; //x,y

        }



        window.clear();
        for (int y = 0;y < grid_dim;++y)
        {
            for (int x = 0;x < grid_dim;++x)
            {
                grid[y * grid_dim + x].setFillColor(sf::Color::Black);
                if (x == snake.first && y == snake.second) //Snake is on this node
                {
                    grid[y * grid_dim + x].setFillColor(sf::Color::Green);
                }

                if (x == apple.first && y == apple.second) //Snake is on this node
                {
                    grid[y * grid_dim + x].setFillColor(sf::Color::Red);
                }

                window.draw(grid[y * grid_dim + x]);
            }
        }
        window.display();
    }

    return 0;
}
