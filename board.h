#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "tile.h"


#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H


struct Board {
    // default constructor
    Board();

    int row_count;
    int column_count;
    int mine_count;
    int tile_count;
    int flag_count;
    vector<vector<Tile*>*> vectorBoardPointers; // vector containing vectors (pointer)

    bool is_paused;
    bool is_debugMode;
    bool is_leaderboard;
    bool loser;
    bool winner;

    // functions
    bool checkWin(); // restarts the board
    void clear(); // clears old memory
    void draw(sf::RenderWindow& window); // draws the whole board
    void boardRestart();
    void clear_flags(); // clears all flags on board
    void reveal_tiles(sf::RenderWindow& window, Tile* tile);
    void placeMines(); // will randomly place mines by adjusting the boolean per Tile object in the 2D vector passed in
    void initializeBoard(); // creates the 2D vector board
    void boardUpdate(sf::RenderWindow& gameWindow); // continuously updates the sprite of each tile after each frame (in main loop)
    void pauseGame(); // sets all the tiles to disabled
    void collectNeighborTiles();
    void reveal_flags();
};


#endif //MINESWEEPER_BOARD_H
