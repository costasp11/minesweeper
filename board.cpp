//
// Created by Costas on 4/17/24.
//
#include <iostream>
#include "board.h"
#include <fstream>
#include <string>
using namespace std;

Board::Board() {
    // CHANGE THIS BOARD CONFIG LATER
    ifstream boardConfig("files/board_config.txt");
    if (boardConfig.is_open()) {
        // read columns
        string col;
        getline(boardConfig, col);
        this->column_count = stoi(col);
        cout << this->column_count;

        //read rows
        string rows;
        getline(boardConfig, rows);
        this->row_count = stoi(rows);
        cout << this->row_count;


        //read minecount
        string minecount;
        getline(boardConfig, minecount);
        this->mine_count = stoi(minecount);
        cout << this->mine_count;

    }
    else cout << "Cannot open file" << endl;


}
