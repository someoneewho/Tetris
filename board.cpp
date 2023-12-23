#include "board.h"
#include <iostream>

Board::Board(int width, int height) : _width(width), _height(height) {
    // Allocate memory for the 2D array
    _grid = new int*[_height]{};
    for (int i = 0; i < _height; ++i) {
        _grid[i] = new int[_width]{};
    }

    // for (int i = 0; i < _height; i++){
    //     _grid[i][2] = _grid[i][7] = 1;
    // }

    _cellShape.setSize(sf::Vector2f(30.f, 30.f));
    _cellShape.setOutlineThickness(1.f);
    _cellShape.setOutlineColor(sf::Color::Black);
}

Board::~Board() {
    // Free the allocated memory for the 2D array
    for (int i = 0; i < _height; ++i) {
        delete[] _grid[i];
    }
    delete[] _grid;
}

void Board::MovePieceRight() {
   int newX = _currentPiecePosX + 1;
    
    if (IsValidMove(newX, _currentPiecePosY)) {
        _currentPiecePosX = newX;
    }
}

void Board::MovePieceLeft() {
    int newX = _currentPiecePosX - 1;
    
    if (IsValidMove(newX, _currentPiecePosY)) {
        _currentPiecePosX = newX;
    }
}

void Board::MovePieceDown() {
    int newY = _currentPiecePosY + 1;
    
    if (IsValidMove(_currentPiecePosX, newY)) {
        _currentPiecePosY = newY;
    }
}

bool Board::IsValidMove(int newX, int newY){
    // boundary control
    if(newX < 0 || newX >= _width || newY < 0 || newY >= _height){
        return false;
    }

    //check for filled cells in the new position
    for(int i = 0; i < _currentPiece->getNumRows(); i++){
        for(int j = 0; j < _currentPiece->getNumColumns(); j++){
            if(_currentPiece->getMatrix()[i][j] != 0 && _grid[newY + i][newX + j]){
                return false;
            }
        }
    }
    return true;
}

void Board::draw(sf::RenderWindow& window) {
    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            if (_grid[i][j] != 0) {
                _cellShape.setFillColor(sf::Color::Blue);
            }
            else {
                _cellShape.setFillColor(sf::Color::White);
            }

            // Hücre pozisyonunu ayarla ve çiz
            _cellShape.setPosition(j * 30.f, i * 30.f);
            window.draw(_cellShape);
        }
    }

    if (_currentPiece) {
        // Draw the current Tetris piece
        const int** pieceMatrix = _currentPiece->getMatrix();

        for (int i = 0; i < _currentPiece->getNumRows(); ++i) {
            for (int j = 0; j < _currentPiece->getNumColumns(); ++j) {
                int x = _currentPiecePosX + j;
                int y = _currentPiecePosY + i;

                if (pieceMatrix[i][j] != 0) {
                    _cellShape.setPosition(x * 30.f, y * 30.f);
                    _cellShape.setFillColor(sf::Color::Red);
                    window.draw(_cellShape);
                }
            }
        }
    }
}