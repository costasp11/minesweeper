#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "board.h"
#include <string>
#include <cctype>
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
    Board board;
    // welcome & game welcomeWindow dimensions
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





    return 0;
}


