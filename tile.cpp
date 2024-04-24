//
// Created by Costas on 4/17/24.
//

#include "tile.h"

Tile::Tile(float xcoord, float ycoord) {
    // load all the textures
    hiddenTexture.loadFromFile("files/images/tile_hidden.png");
    revealedTexture.loadFromFile("files/images/tile_revealed.png");
    mineTexture.loadFromFile("files/images/mine.png");
    flagTexture.loadFromFile("files/images/flag.png");
    num_one.loadFromFile("files/images/number_1.png");
    num_two.loadFromFile("files/images/number_2.png");
    num_three.loadFromFile("files/images/number_3.png");
    num_four.loadFromFile("files/images/number_4.png");
    num_five.loadFromFile("files/images/number_5.png");
    num_six.loadFromFile("files/images/number_6.png");
    num_seven.loadFromFile("files/images/number_7.png");
    num_eight.loadFromFile("files/images/number_8.png");

    int x_location = xcoord * 32;
    int y_location = ycoord * 32;
    this->sprite.setTexture(hiddenTexture); // auto sets each tile object to hidden
    this->sprite.setPosition(sf::Vector2f(x_location, y_location)); // sets position (but does not draw)
    this->mines_num = 0; // change this later surrounding mines

    //initialize booleans but can change later
    is_flagged = false;
    is_mine = false;
    is_revealed = false;
    is_enabled = true;
    reveal_flags = false;


}


void Tile::update(sf::RenderWindow &window, bool is_paused, bool is_debug, bool is_leaderboard, bool loser, bool winner) {
    // will be implemented in game window loop (main)
    // checks where the mouse is clicked, and obtains a tile within those boundaries
    // tile object sprite is updated based on the conditions

    //*****DEBUG MODE*****//
    if (is_debug && is_mine && is_enabled) {
        this->sprite.setTexture(mineTexture);
        window.draw(this->sprite);
    }
    else{
        // sets mines back to hidden if not in debug mode
        if(is_enabled){
            this->sprite.setTexture(hiddenTexture);
            window.draw(sprite);
        }
    }
    // NOT DEBUG MODE
    if (!is_debug) {
        if(reveal_flags && is_mine){
            sprite.setTexture(flagTexture);
            window.draw(sprite);
        }
        // ONLY IF THE TILE IS NOT REVEALED
        if(!is_revealed && is_enabled){
            if(is_flagged){
                sprite.setTexture(flagTexture);
                window.draw(sprite);
            }
            else{
                sprite.setTexture(hiddenTexture);
                window.draw(sprite);
            }
        }
        // IF THE TILE IS REVEALED IMPLEMENT GAME LOGIC (REVEAL TILES NEAR IT THAT DO NOT HAVE MINES)
        // REVEAL THE NUMBER
        else if(is_revealed && is_enabled){
            if(mines_num == 0 && is_enabled && !is_mine){
                sprite.setTexture(revealedTexture);
                window.draw(sprite);
            }
            else if (mines_num == 1 && is_enabled && !is_mine){
                sprite.setTexture(revealedTexture);
                window.draw(sprite);

                sprite.setTexture(num_one);
                window.draw(sprite);
            }
            else if (mines_num == 2 && is_enabled && !is_mine){
                sprite.setTexture(revealedTexture);
                window.draw(sprite);

                sprite.setTexture(num_two);
                window.draw(sprite);
            }
            else if (mines_num == 3 && is_enabled && !is_mine){
                sprite.setTexture(revealedTexture);
                window.draw(sprite);

                sprite.setTexture(num_three);
                window.draw(sprite);
            }
            else if (mines_num == 4 && is_enabled && !is_mine){
                sprite.setTexture(revealedTexture);
                window.draw(sprite);

                sprite.setTexture(num_four);
                window.draw(sprite);
            }
            else if (mines_num == 5 && is_enabled && !is_mine){
                sprite.setTexture(revealedTexture);
                window.draw(sprite);

                sprite.setTexture(num_five);
                window.draw(sprite);
            }
            else if (mines_num == 6 && is_enabled && !is_mine){
                sprite.setTexture(revealedTexture);
                window.draw(sprite);

                sprite.setTexture(num_six);
                window.draw(sprite);
            }
            else if (mines_num == 7 && is_enabled && !is_mine){
                sprite.setTexture(revealedTexture);
                window.draw(sprite);

                sprite.setTexture(num_seven);
                window.draw(sprite);
            }
            else if (mines_num == 8 && is_enabled && !is_mine){
                sprite.setTexture(revealedTexture);
                window.draw(sprite);

                sprite.setTexture(num_eight);
                window.draw(sprite);
            }
        }
        // CASE WHICH YOU PAUSE THE GAME DISABLES ALL TILES
        else if(!is_enabled){
            sprite.setTexture(hiddenTexture);
            window.draw(sprite);
        }


    }






}

void Tile::toggleFlag() {
    is_flagged = !is_flagged; // switches the boolean
}


