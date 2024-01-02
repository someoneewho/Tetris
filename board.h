#pragma once
#include "piece.h"
#include <SFML/Graphics.hpp>

constexpr int CELL_SIZE = 30;
class Board {
public:
    Board(int width, int height);
    ~Board();

    // Draw the game board on the specified SFML window
    void draw(sf::RenderWindow& window);
    bool SetCurrentPiece(Piece *currentPiece);

    void RotatePieceCW();
    void RotatePieceCCW();

    void MovePieceRight();
    void MovePieceLeft();
    std::pair<bool, int> MovePieceDown();
    bool IsValidMove(int newX, int newY);
    bool IsRotationValid(Piece::RotateType rt);

    int getFullRow();
    void ClearRow(int rowIndex);
    int getWidth() { return _width; }
    int getHeight() { return _height; }
    void Clear();

private:
    void LockCurrentPiece();


private:
    int _width;
    int _height;
    sf::RectangleShape _cellShape;
    int** _grid; // 2D array representing the game board

    Piece *_currentPiece = nullptr;
    int _currentPiecePosX = 0;
    int _currentPiecePosY = 0;
};
