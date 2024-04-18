#include <iostream>
#include <SFML/Graphics.hpp>


#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H


struct Board {
    // default constructor
    Board();

    int row_count;
    int column_count;
    int mine_count;
    int tiles;

    // functions
    void clear();
    void draw(sf::RenderWindow& window);
};


#endif //MINESWEEPER_BOARD_H
