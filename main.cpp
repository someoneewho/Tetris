#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <time.h>
#include "game.h"

using namespace std;

int getBoundedInput(const string& prompt, int minValue, int maxValue) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            // Input was an integer
            if (value >= minValue && value <= maxValue) {
                // Valid input, break the loop
                break;
            } else {
                cout << "Value must be between " << minValue << " and " << maxValue << ". Try again." << endl;
            }
        } else {
            // Input was not an integer
            cout << "Invalid input. Please enter an integer." << endl;
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
    }

    return value;
}

int main() {
    srand(time(nullptr));


    unsigned boardWidth, boardHeight, level, speed;
    string userName;

    boardWidth = getBoundedInput("Enter Board Width (min 5, max 50): ", 5, 50);
    boardHeight = getBoundedInput("Enter Board Height (min 10, max 100): ", 10, 100);
    level = getBoundedInput("Select Level (1-10): ", 1, 10);
    speed = getBoundedInput("Select Speed (1-10): ", 1, 10);

    // cout << "Select Username: ";
    // cin >> userName; 


    int numCustomPiecesToAdd;
    numCustomPiecesToAdd = getBoundedInput("How many custom pieces do you want to add? (0-3): ", 0, 3);

    for (int i = 0; i < numCustomPiecesToAdd; ++i) {
        cout << "\nCustom Piece #" << i + 1 << ":\n";
        Piece::addCustomPiece();
    }

    cout << "Tetris Game starting!" << endl;

    sf::RenderWindow window(sf::VideoMode(30 * boardWidth + 200, 30 * boardHeight), "Tetris");

    Game tetrisGame(boardWidth, boardHeight, window, level, speed);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                tetrisGame.HandleKeyPress(event.key.code);
            }
        }
        tetrisGame.Update();
        tetrisGame.Draw();
        window.display();
    }

    return 0;
}
