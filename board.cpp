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
    _cellShape.setOutlineColor(sf::Color::White);
}

Board::~Board() {
    // Free the allocated memory for the 2D array
    for (int i = 0; i < _height; ++i) {
        delete[] _grid[i];
    }
    delete[] _grid;
}

void Board::MovePieceRight() {
    if (_currentPiece == nullptr){
        return;
    }
    
    int newX = _currentPiecePosX + 1;

    if(IsValidMove(newX, _currentPiecePosY)){
        _currentPiecePosX = newX;
    }
}

void Board::MovePieceLeft() {
    if (_currentPiece == nullptr) { 
        return;
    }
    
    int newX = _currentPiecePosX - 1;
    
    if (IsValidMove(newX, _currentPiecePosY)) {
        _currentPiecePosX = newX;
    }
}

void Board::MovePieceDown() {
    if (_currentPiece == nullptr) { 
        return;
    }
 
    int newY = _currentPiecePosY + 1;
    
    if (IsValidMove(_currentPiecePosX, newY)) {
        _currentPiecePosY = newY;
    }
    else {

        int pieceRows = _currentPiece->getNumRows();
        int pieceCols = _currentPiece->getNumColumns();

        for (int i = 0; i < pieceRows; i++) {
            for (int j = 0; j < pieceCols; j++) {
                if (_currentPiece->getMatrix().data[i][j] != 0) {
                    _grid[_currentPiecePosY + i][_currentPiecePosX + j] = 1;
                }
            }
        }

        _currentPiece = nullptr;
    }
}

bool Board::IsValidMove(int newX, int newY){
    // boundary control
    if(newX < 0 || newX + _currentPiece->getNumColumns() > _width || 
       newY < 0 || newY + _currentPiece->getNumRows() > _height){
        return false;
    }

    //check for filled cells in the new position
    for(int i = 0; i < _currentPiece->getNumRows(); i++){
        for(int j = 0; j < _currentPiece->getNumColumns(); j++){
            if(_currentPiece->getMatrix().data[i][j] != 0 && _grid[newY + i][newX + j]){
                return false;
            }
        }
    }
    return true;
}

bool Board::IsRotationValid(Piece::RotateType rt) {
    // Create a temporary shape for rotation validation
    Piece::ShapeMatrix rotatedMatrix = _currentPiece->getRotatedShape(rt);

    // Check for collisions in the new position
    for (int i = 0; i < rotatedMatrix.rows; ++i) {
        for (int j = 0; j < rotatedMatrix.cols; ++j) {
            int x = _currentPiecePosX + j;
            int y = _currentPiecePosY + i;

            // Check if out of bounds
            if (x < 0 || x >= _width || y >= _height) {
                return false;  // Collision detected
            }

            // Check if the cell is already occupied
            if (rotatedMatrix.data[i][j] != 0 && _grid[y][x] != 0) {
                return false;  // Collision detected
            }
        }
    }

    return true;  // Rotation is valid
}

void Board::draw(sf::RenderWindow& window) { 
    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            if (_grid[i][j] != 0) {
                _cellShape.setFillColor(sf::Color::Blue);
            }
            else {
                _cellShape.setFillColor(sf::Color::Black);
            }

            // Hücre pozisyonunu ayarla ve çiz
            _cellShape.setPosition(j * 30.f, i * 30.f);
            window.draw(_cellShape);
        }
    }

    if (_currentPiece) {
        // Draw the current Tetris piece
        const Piece::ShapeMatrix& pieceMatrix = _currentPiece->getMatrix();

        for (int i = 0; i < pieceMatrix.rows; ++i) {
            for (int j = 0; j < pieceMatrix.cols; ++j) {
                int x = _currentPiecePosX + j;
                int y = _currentPiecePosY + i;

                if (pieceMatrix.data[i][j] != 0) {
                    _cellShape.setPosition(x * 30.f, y * 30.f);
                    _cellShape.setFillColor(sf::Color::Red);
                    window.draw(_cellShape);
                }
            }
        }
    }
}

void Board::RotatePieceCW() {
    if (_currentPiece && IsRotationValid(Piece::ROTATE_CW)) {
        _currentPiece->Rotate(Piece::ROTATE_CW);
    }
}

void Board::RotatePieceCCW() {
    if (_currentPiece && IsRotationValid(Piece::ROTATE_CCW)) {
        _currentPiece->Rotate(Piece::ROTATE_CCW);
    }
}