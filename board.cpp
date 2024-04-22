//
// Created by Costas on 4/17/24.
//
#include <iostream>
#include "board.h"
#include <fstream>
#include <string>
#include <random>
using namespace std;

Board::Board() {

    // CHANGE THIS BOARD CONFIG LATER
    ifstream boardConfig("files/board_config.txt");
    if (boardConfig.is_open()) {
        // read columns
        string col;
        getline(boardConfig, col);
        this->column_count = stoi(col);
        cout << this->column_count << endl;

        //read rows
        string rows;
        getline(boardConfig, rows);
        this->row_count = stoi(rows);
        cout << this->row_count << endl;


        //read minecount
        string minecount;
        getline(boardConfig, minecount);
        this->mine_count = stoi(minecount);
        cout << this->mine_count << endl;

        //store tile count
        this->tile_count = this->row_count * this->column_count;
        cout << tile_count << endl;
    }
    else cout << "Cannot open file" << endl;

    //initialize booleans
    this->flag_count = mine_count;
    this->is_debugMode = false;
    this->is_leaderboard = false;
    this->is_paused = false;
    this->loser = false;
    this->winner = false;

    initializeBoard();
    placeMines();
    collectNeighborTiles();



}


void Board::placeMines() {
    //create a randomization for mines that change the boolean randomly in the 2D vector
    // make sure to count and go all the way up to the total mine count


    random_device rd; // the object that creates a random seed so the random numbers are different every time the program is run
    mt19937 gen(rd()); // generates the random seed
    uniform_int_distribution<int> rowDist(0, row_count-1); // generates random int for row
    uniform_int_distribution<int> colDist(0, column_count - 1); // generates random int for col
    // assign the random mines
    for(int i=0; i<mine_count; i++){
        // assign the generated outputs
        int row = rowDist(gen);
        int col = colDist(gen);
        vectorBoardPointers.at(row)->at(col)->is_mine = true;
    }

}

//******CREATE TILE OBJECTS IN 2D VECTOR*******//
void Board::initializeBoard() {
    //DIMENSIONS PER TILE (add window width variable)
    for(int row = 0; row < this->row_count; row++ ){ // amount of tiles to be created within this loop
        vector<Tile*>* vectorRow = new vector<Tile*>; // pointer to new vector created for every row
        for(int col = 0; col < this->column_count; col++){
            Tile* temp = new Tile(col, row); // will automatically adjust coordinates in Tile constructor
            vectorRow->push_back(temp); // will push a pointer for each column then repeat a after a new vector
        }
        vectorBoardPointers.push_back(vectorRow); // stores the vector within the 2D
    }
}

void Board::draw(sf::RenderWindow &window) {
    //takes in game window
    // iterate through the vectorBoardPointers and get each Tile object within (will have a x coord and y coord)
    // set sprite position to these coordinates
    for(int row = 0; row < row_count; row++){
        for(int col = 0; col < column_count; col++){
            window.draw(vectorBoardPointers.at(row)->at(col)->sprite);
        }
    }
}

void Board::boardUpdate(sf::RenderWindow &gameWindow) {
    // continuously updates each tile sprite after each frame
    for(int i = 0; i < row_count; i++){
        for(int j = 0; j < column_count; j++){
            vectorBoardPointers.at(i)->at(j)->update(gameWindow, is_paused, is_debugMode, is_leaderboard, loser, winner);
        }
    }

}

void Board::pauseGame() {
    for(int i = 0; i < row_count; i++){
        for(int j = 0; j < column_count; j++){
            // switches all the tiles to disabled
            vectorBoardPointers.at(i)->at(j)->is_enabled = !vectorBoardPointers.at(i)->at(j)->is_enabled;
        }
    }
}


void Board::collectNeighborTiles() {
    for (int i = 0; i < row_count; i++) {
        for (int j = 0; j < column_count; j++) {
            Tile* currentTile = vectorBoardPointers.at(i)->at(j);

            // Iterate over neighboring tiles using nested loops
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    // Skip the current tile itself
                    if (dx == 0 && dy == 0)
                        continue;

                    // Calculate neighboring tile coordinates
                    int neighborX = i + dx;
                    int neighborY = j + dy;

                    // Check if neighboring coordinates are within bounds
                    if (neighborX >= 0 && neighborX < row_count && neighborY >= 0 && neighborY < column_count) {
                        currentTile->adjacent_tiles.push_back(vectorBoardPointers.at(neighborX)->at(neighborY));
                    }
                }
            }

            // Count surrounding mines
            for (Tile* neighbor : currentTile->adjacent_tiles) {
                if (neighbor->is_mine)
                    currentTile->mines_num++;
            }
        }
    }
}

void Board::reveal_tiles(sf::RenderWindow& window, Tile* tile) {
    if(tile->is_flagged)
        return;//according to instructions pdf for the project, we are not supposed to reveal any mines that have been flagged (even recursively)

    tile->is_revealed= true;

    if (tile->mines_num == 0&&tile->is_enabled) {//recursive case
        for (unsigned int i=0; i<tile->adjacent_tiles.size();i++) {//cycle through neighboring tiles
            if (!tile->adjacent_tiles.at(i)->is_revealed&&tile->adjacent_tiles.at(i)->is_enabled)
                reveal_tiles(window, tile->adjacent_tiles.at(i));
        }
    }
}

bool Board::checkWin() {
    int count = 0;
    for(auto vectorTile : vectorBoardPointers){
        for(auto tile : *vectorTile){
            if(tile->is_revealed && !tile->is_mine){
                count++; // counts how many tiles are revealed on the board
            }
            if(count == (tile_count - mine_count)){
                return true;
            }
        }
    }
    return false;
}

void Board::boardRestart() {
    // create new board object
}

void Board::clear() {
    for(auto vectorPointer : vectorBoardPointers){
        for(auto tile : *vectorPointer){
            delete tile; // delete each tile on board when restart game
        }
    }
}

