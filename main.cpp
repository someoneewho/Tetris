#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <time.h>
#include "board.h"
#include "game.h"

using namespace std;


Piece::PieceType getNextPieceType()
{
    static Piece::PieceType type = Piece::PLUS_SIGN;

    auto ret = type;

    auto temp = (int)type;
    
    if (++temp == Piece::END)
        type = Piece::PLUS_SIGN;
    else
        type = (Piece::PieceType)temp;

    return ret;
}


Piece::PieceType getRandomPieceType()
{
    return getNextPieceType();
    // return (Piece::PieceType)(rand() % Piece::END);
}

int main() {
    srand(std::time(nullptr));

    sf::RenderWindow window(sf::VideoMode(300, 600), "Tetris");

    Board tetrisBoard(10, 20);
    Piece *piece = new Piece(getRandomPieceType());

    tetrisBoard.setCurrentPiece(piece);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Right) {
                    tetrisBoard.MovePieceRight();
                }
                else if (event.key.code == sf::Keyboard::Left) {
                    tetrisBoard.MovePieceLeft();
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    tetrisBoard.MovePieceDown();
                }
                else if (event.key.code == sf::Keyboard::E) {
                    tetrisBoard.RotatePieceCW();
                }
                else if (event.key.code == sf::Keyboard::Q) {
                    tetrisBoard.RotatePieceCCW();
                }
                else if (event.key.code == sf::Keyboard::R) {   // Reset -- test
                    delete piece;
                    piece = new Piece(getRandomPieceType());
                    tetrisBoard.setCurrentPiece(piece);
                }
            }

        }

        window.clear();
        tetrisBoard.draw(window);
        window.display();
    }

    delete piece;

    return 0;
}
