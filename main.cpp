#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <time.h>
#include "game.h"

using namespace std;


int main() {
    srand(std::time(nullptr));


    unsigned boardWidth, boardHeight, level, speed;
    std::string userName;

    std::cout << "Enter Board Width: ";
    std::cin >> boardWidth;

    std::cout << "Enter Board Height: ";
    std::cin >> boardHeight;

    // std::cout << "Select Level (1-10): ";
    // std::cin >> level;

    // std::cout << "Select Speed (1-10): ";
    // std::cin >> speed;

    // std::cout << "Select Username: ";
    // std::cin >> userName; 

    sf::RenderWindow window(sf::VideoMode(30 * boardWidth + 200, 30 * boardHeight), "Tetris");

    Game tetrisGame(boardWidth, boardHeight, window);
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
