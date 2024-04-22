#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "board.h"
#include <string>
#include <cctype>
#include "Clock.h"
using namespace std;

void getTextRectangle(sf::Text &text, float x, float y){
    sf::FloatRect bounds = text.getGlobalBounds(); // creates rectangle object
    text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    text.setPosition(sf::Vector2f(x, y)); // sets position on window
}

// creates the text and styles it
sf::Text create_text(string text_str, sf::Font& font, int font_size, sf::Color color, float x, float y){
    sf::Text text(text_str, font, font_size);
    text.setFillColor(color);
    getTextRectangle(text, x, y);
    return text;
}

int main() {
    // welcome & game welcomeWindow dimensions
    Board board;
    int window_height = (board.row_count * 32) + 100;
    int window_width = (board.column_count * 32);

    // leaderboard dimensions
    int leaderboardWindow_Width = (board.column_count) * 16;
    int leaderboardWindow_Height = (board.row_count * 16) +50;

    //load font from file + CHANGE THIS LATER WHEN SUBMISSION
    sf::Font font;
    ifstream fontFile("files/font.ttf");
    // loads font from file & checks if its valid
    if(!font.loadFromFile("files/font.ttf")){
        cout << "Failed to open font file" << endl;
    }

    // name that will be entered into the textbox
    sf::Text nameText;
    sf::String name_input = "";

    //********WELCOME WINDOW*********//
    sf::RenderWindow welcomeWindow(sf::VideoMode(window_width, window_height), "SFML Window");
    while(welcomeWindow.isOpen()) {
        sf::Event event;

        //create welcome text
        sf::Text welcomeText = create_text("WELCOME TO MINESWEEPER!", font, 22, sf::Color::White, window_width/2.0f, window_height/2.0f-100);
        welcomeText.setStyle((sf::Text::Bold | sf::Text::Underlined));

        //create enter name text
        sf::Text enterName = create_text("Enter your name:", font, 20, sf::Color::White, window_width/2.0f, window_height/2.0f-50);

        while(welcomeWindow.pollEvent(event)) { // reading events continuously
            if(event.type == sf::Event::Closed) {
                welcomeWindow.close();
            }
//
//            else if(event.type == sf::Event::MouseButtonPressed){
//                sf::Mouse mouse;
//                // obtain coordinates of mouse
//                int mousex = mouse.getPosition(welcomeWindow).x;
//                int mousey = mouse.getPosition(welcomeWindow).y;
//                // shape.getGlobalBounds().contains(mousex,mousey); => returns boolean if click is within the shape
//            }

            else if (event.type == sf::Event::TextEntered) { // if keyboard typing is triggered
                 if (isalpha(event.text.unicode) && name_input.getSize() < 10) { // if alphabetical and < 10?
                        char letter = static_cast<char>(event.text.unicode);
                        if (name_input.getSize() == 0) { // convert first letter to uppercase
                            letter = toupper(letter);
                            name_input += letter;
                        } else {
                            letter = tolower(letter);
                            name_input += letter;
                        }
                        // update text
                         nameText = create_text(name_input + "|", font, 18, sf::Color::Yellow, window_width / 2.0f, (window_height / 2.0f) - 10);
                         nameText.setStyle(sf::Text::Bold);
                 }
            }
            else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace && name_input.getSize() != 0){
                name_input.erase(name_input.getSize()-1); // delete last char
                nameText = create_text(name_input + "|", font, 18, sf::Color::Yellow, window_width / 2.0f, (window_height / 2.0f) - 10);
                nameText.setStyle(sf::Text::Bold);
            }
            else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return && name_input.getSize() != 0 ){ // closes when RETURN is pressed
                welcomeWindow.close();
            }
        }
            // UPDATE EVERY FRAME
            welcomeWindow.clear(sf::Color::Blue);
            welcomeWindow.draw(welcomeText);
            welcomeWindow.draw(enterName);
            welcomeWindow.draw(nameText);
            welcomeWindow.display();
    }

    //*****LOAD ICONS*****//

    //FACE ICON
    sf::Texture faceHappy;
    faceHappy.loadFromFile("files/images/face_happy.png");
    sf::Sprite faceSprite;
    sf::Texture faceWin;
    faceWin.loadFromFile("files/images/face_win.png");
    sf::Texture faceLose;
    faceLose.loadFromFile("files/images/face_lose.png");
    faceSprite.setTexture(faceHappy);
    faceSprite.setPosition((board.column_count/2.0f*32)-32,32*(board.row_count+0.5));

    // DEBUG.PNG
    sf::Texture debugIcon;
    debugIcon.loadFromFile("files/images/debug.png");
    sf::Sprite debugSprite;
    debugSprite.setTexture(debugIcon);
    debugSprite.setPosition((board.column_count*32)-304,32*(board.row_count+0.5));

    //PAUSE.PNG
    sf::Texture pauseIcon;
    pauseIcon.loadFromFile("files/images/pause.png");
    sf::Texture playIcon;
    playIcon.loadFromFile("files/images/play.png");
    sf::Sprite pauseSprite;
    pauseSprite.setTexture(pauseIcon);
    pauseSprite.setPosition((board.column_count*32)-240,32*(board.row_count+0.5));

    //LEADERBOARD.PNG
    sf::Texture leaderboardIcon;
    leaderboardIcon.loadFromFile("files/images/leaderboard.png");
    sf::Sprite leaderboardSprite;
    leaderboardSprite.setTexture(leaderboardIcon);
    leaderboardSprite.setPosition((board.column_count*32)-176,32*(board.row_count+0.5));

    //LOAD NUMBER IMAGE FILE AND CREATE CLOCK
    sf::Sprite digSprite[11];
    sf::Texture digTexture;
    digTexture.loadFromFile("files/images/digits.png");
    for(int i = 0; i < 11; i++){
        digSprite[i].setTexture(digTexture);
        // cuts each texture by using Texture Rect (left will change based on i) (21 pixels wide)
        digSprite[i].setTextureRect(sf::IntRect (i * 21,0,21,32));
    }

    int hundredCounterX = 33;
    int counterY = ((board.row_count * 32 + 0.5) + 16);
    // INITIALIZE MINUTES COORDINATE
    int minutesX = (board.column_count * 32) - 97;
    int secondsX = (board.column_count * 32) - 54;
    int digitsY = 32 * (board.row_count + 0.5) + 16;

    // ENABLING OF BUTTONS
    bool debugButtonEnabled = true;
    bool pauseButtonEnabled = true;

    //******GAME WINDOW******//
    sf::RenderWindow gameWindow(sf::VideoMode(window_width, window_height), "SFML Window");
    //START CLOCK
    Clock clock;
    clock.start();
    while(gameWindow.isOpen()) {
        float elapsedSeconds = chrono::duration_cast<chrono::seconds>(clock.elapsed()).count();
        int minutes = static_cast<int>(elapsedSeconds / 60);
        int seconds = static_cast<int>(elapsedSeconds) % 60;

        int mouse_pos_x = sf::Mouse::getPosition(gameWindow).x;
        int mouse_pos_y = sf::Mouse::getPosition(gameWindow).y;

        int absFlagCount = abs(board.flag_count);

        sf::Event event; // create event
        while (gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                board.clear();
                gameWindow.close();
            } else if (event.type == sf::Event::MouseButtonPressed) { // checks if mouse button pressed is the event
                int clicked_row = mouse_pos_y / 32;
                int clicked_col = mouse_pos_x / 32;

                if (event.mouseButton.button == sf::Mouse::Left) { // if its a left click, obtain coordinates
                    if (debugSprite.getGlobalBounds().contains(mouse_pos_x,mouse_pos_y) && debugButtonEnabled && !board.is_paused) { // if its within the debug sprite
                        board.is_debugMode = !board.is_debugMode;// toggle debug mode
                    }
                    // if row clicked is valid and it is NOT A MINE
                    else if(clicked_row >= 0 && clicked_row < board.row_count && clicked_col >= 0 && clicked_col < board.column_count && !board.vectorBoardPointers.at(clicked_row)->at(clicked_col)->is_mine && !board.is_paused) {
                        // recursively reveal tiles

                        // Toggle revealed state of the clicked tile
                        // Call reveal function to reveal neighboring tiles recursively
                        board.reveal_tiles(gameWindow, board.vectorBoardPointers.at(clicked_row)->at(clicked_col));
                    }
                    // else if it IS A MINE LOSE
                    else if(clicked_row >= 0 && clicked_row < board.row_count && clicked_col >= 0 && clicked_col < board.column_count && board.vectorBoardPointers.at(clicked_row)->at(clicked_col)->is_mine && !board.is_paused) {
                        clock.pause();
                        board.loser = true;
                        faceSprite.setTexture(faceLose);
                        debugButtonEnabled = false;
                        pauseButtonEnabled = false;
                        board.is_debugMode = true; // MAKE SURE TO SET THIS FALSE AT THE END
                    }
                    else if(pauseSprite.getGlobalBounds().contains(mouse_pos_x, mouse_pos_y) && pauseButtonEnabled){
                        board.is_paused = !board.is_paused; // toggle pause mode
                        board.pauseGame(); // TOGGLES ALL TILES DISABLED
                        clock.pause();
                        if(board.is_paused){
                            pauseSprite.setTexture(playIcon);
                        }
                        else{
                            pauseSprite.setTexture(pauseIcon);
                            clock.resume();
                        }
                    }
                    else if(faceSprite.getGlobalBounds().contains(mouse_pos_x, mouse_pos_y)){
                        // restartBoard();
                        faceSprite.setTexture(faceHappy);
                        pauseButtonEnabled = true;
                        debugButtonEnabled = true;
                        board.clear();

                    }
                }

                if (event.mouseButton.button == sf::Mouse::Right) {
                    cout << mouse_pos_x << " " << mouse_pos_y << endl;
                    // Check if the clicked coordinates are within the board boundaries and checks that it is not revealed
                    if (clicked_row >= 0 && clicked_row < board.row_count && clicked_col >= 0 && clicked_col < board.column_count && !board.is_paused && !board.vectorBoardPointers.at(clicked_row)->at(clicked_col)->is_revealed) {
                        // Toggle the flag of the clicked tile
                        Tile* clicked_tile = board.vectorBoardPointers.at(clicked_row)->at(clicked_col);
                        clicked_tile->toggleFlag();

                        // Update the flag count
                        if (clicked_tile->is_flagged) {
                            board.flag_count--;
                        } else {
                            board.flag_count++;
                        }
                        cout << "Flag count: " << board.flag_count << endl;
                        cout << clicked_col << " " << clicked_row << endl;
                    }
                }

            }
            // draw all the tiles on the board using draw(gameWindow) func.
        }
            //DRAW ICONS
            gameWindow.clear(sf::Color::White);
            board.draw(gameWindow);
            gameWindow.draw(faceSprite);
            gameWindow.draw(debugSprite);
            gameWindow.draw(pauseSprite);
            gameWindow.draw(leaderboardSprite);
            //UPDATE TIMER
            digSprite[minutes / 10].setPosition(minutesX, digitsY);
            gameWindow.draw(digSprite[minutes / 10]);
            digSprite[minutes % 10].setPosition(minutesX + 21, digitsY);
            gameWindow.draw(digSprite[minutes % 10]);
            digSprite[seconds / 10].setPosition(secondsX, digitsY);
            gameWindow.draw(digSprite[seconds / 10]);
            digSprite[seconds % 10].setPosition(secondsX + 21, digitsY);
            gameWindow.draw(digSprite[seconds % 10]);
            //UPDATE FLAG COUNTER
            if(board.flag_count >= 0){
                digSprite[(board.flag_count / 100)].setPosition(hundredCounterX, counterY);
                gameWindow.draw(digSprite[board.flag_count / 100]); // HUNDREDS
                digSprite[(board.flag_count / 10) % 10].setPosition(hundredCounterX + 21, counterY); // TENS PLACE
                gameWindow.draw(digSprite[(board.flag_count/10) % 10]);
                digSprite[(board.flag_count % 10)].setPosition(hundredCounterX + 42, counterY);
                gameWindow.draw(digSprite[board.flag_count % 10]);
            }
            else{ // when negative
                digSprite[10].setPosition(12, ((32*(board.row_count + 0.5) )));
                gameWindow.draw(digSprite[10]); // DRAW NEGATIVE
                digSprite[(absFlagCount / 100)].setPosition(hundredCounterX, counterY);
                gameWindow.draw(digSprite[absFlagCount/ 100]); // HUNDREDS
                digSprite[(absFlagCount / 10) % 10].setPosition(hundredCounterX + 21, counterY); // TENS PLACE
                gameWindow.draw(digSprite[(absFlagCount/10) % 10]);
                digSprite[(absFlagCount % 10)].setPosition(hundredCounterX + 42, counterY);
                gameWindow.draw(digSprite[absFlagCount % 10]);
            }
            board.boardUpdate(gameWindow);
            gameWindow.display();



    }






    return 0;
}


