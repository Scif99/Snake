
#include "grid.h"

Grid::Grid(int dim, float window_size)
{
    //Constants
    int node_size = window_size / dim; //size of the node in pixels 

    //Fill the grid
    for (int y = 0;y < dim;++y)
    {
        for (int x = 0;x < dim;++x)
        {
            sf::RectangleShape node(sf::Vector2f(node_size, node_size));
            node.setPosition(sf::Vector2f(x * node_size, y * node_size));
            m_grid.push_back(node);
        }

    }

}