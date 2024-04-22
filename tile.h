#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

#ifndef MINESWEEPER_TILE_H
#define MINESWEEPER_TILE_H


class Tile {
    sf::Texture mineTexture;
    sf::Texture hiddenTexture;
    sf::Texture revealedTexture;
    sf::Texture flagTexture;
    sf::Texture num_one;
    sf::Texture num_two;
    sf::Texture num_three;
    sf::Texture num_four;
    sf::Texture num_five;
    sf::Texture num_six;
    sf::Texture num_seven;
    sf::Texture num_eight;

public:
    sf::Sprite sprite;
    int mines_num;
    int x_location;
    int y_location;
    bool is_mine;
    bool is_flagged;
    bool is_revealed;
    bool is_enabled;
    Tile(float xcoord, float ycoord);
    vector<Tile*> adjacent_tiles; // always going to be 8 tiles

    //functions
    int countMinesAdjacent(Tile& tile); // returns the # of mines near the tile inputted within (should this be in Board?)
    void toggleFlag(); // toggles the flag boolean
    void update(sf::RenderWindow& window, bool is_paused, bool is_debug, bool is_leaderboard, bool loser, bool winner); // will be implemented in gameWindow loop.


};


#endif //MINESWEEPER_TILE_H
