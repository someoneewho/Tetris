#pragma once
#include "piece.h"
#include <SFML/Graphics.hpp>

class Board {
public:
    Board(int width, int height);
    ~Board();

    // Draw the game board on the specified SFML window
    void draw(sf::RenderWindow& window);
    void setCurrentPiece(Piece *currentPiece) {
        _currentPiece = currentPiece;
        _currentPiecePosX = (_width - currentPiece->getNumColumns()) / 2;
        _currentPiecePosY = 0;
    }

    bool IsValidMove(int newX, int newY);

    void RotatePieceCW() {
        if (_currentPiece){
            _currentPiece->RotateCW();
        }
    }

    void RotatePieceCCW() {
        if (_currentPiece) {
            _currentPiece->RotateCCW();
        }
    }

    void MovePieceRight();
    void MovePieceLeft();
    void MovePieceDown();


private:
    int _width;
    int _height;
    sf::RectangleShape _cellShape;
    int** _grid; // 2D array representing the game board

    Piece *_currentPiece = nullptr;
    int _currentPiecePosX = 0;
    int _currentPiecePosY = 0;
};
