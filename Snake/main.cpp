#include <SFML/Graphics.hpp>

#include "grid.cpp"

#include <cstdlib>
#include <vector>
int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Snake");


    //Create a grid that contains the nodes
    std::vector<sf::RectangleShape> grid;

    sf::Vector2f node_size(25.f, 25.f); //Fixed size of nodes

    for (int i = 0;i < 20;++i)
    {
        for (int j = 0;j < 20;++j)
        {
            sf::RectangleShape node(node_size);
            node.setFillColor(sf::Color::Black);
            node.setOutlineColor(sf::Color::White);
            node.setOutlineThickness(-0.5f);
            node.setPosition(sf::Vector2f(i * 25.f, j*25.f));
            grid.push_back(node);
        }

    }


    sf::RectangleShape apple(node_size);
    apple.setFillColor(sf::Color::Red);
    apple.setPosition(0.f, 0.f);
    apple.setOutlineColor(sf::Color::White);
    apple.setOutlineThickness(-0.5f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {

                }
            }
        }

        window.clear();
        for (const auto& node : grid) window.draw(node);
        window.draw(apple);
        window.display();
    }

    return 0;
}
