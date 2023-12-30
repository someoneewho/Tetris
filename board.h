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

    void RotatePieceCW();
    void RotatePieceCCW();

    void MovePieceRight();
    void MovePieceLeft();
    void MovePieceDown();
    bool IsValidMove(int newX, int newY);
    bool IsRotationValid(Piece::RotateType rt);

    int getFullRow();
    void ClearRow(int rowIndex);



private:
    int _width;
    int _height;
    sf::RectangleShape _cellShape;
    int** _grid; // 2D array representing the game board

    Piece *_currentPiece = nullptr;
    int _currentPiecePosX = 0;
    int _currentPiecePosY = 0;
};
