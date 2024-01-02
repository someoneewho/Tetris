#include "board.h"
#include <iostream>

Board::Board(int width, int height) : _width(width), _height(height) {
    // Allocate memory for the 2D array
    _grid = new int*[_height]{};
    for (int i = 0; i < _height; ++i) {
        _grid[i] = new int[_width]{};
    }

    _cellShape.setSize(sf::Vector2f(30.f, 30.f));
    _cellShape.setOutlineThickness(1.f);
    _cellShape.setOutlineColor(sf::Color::White);
}

/**
 * @brief Sets the current piece on the board.
 *
 * This function places the given Tetris piece on the board at its initial position.
 * It checks if the destination cells on the board are empty; if not, the function returns false,
 * indicating that the game should end.
 *
 * @param currentPiece Pointer to the Tetris piece to be placed on the board.
 * @return True if the piece is successfully placed on the board, false otherwise.
 */
bool Board::SetCurrentPiece(Piece *currentPiece){
    //initial position
    _currentPiecePosX = (_width - currentPiece->getNumColumns()) / 2;
    _currentPiecePosY = 0;

    _currentPiece = currentPiece;

    for(int row = 0; row < _currentPiece->getNumRows(); row++){
        for(int col = 0; col < _currentPiece->getNumColumns(); col++){
            // Check if the current cell on the board is not empty.
            if(_grid[_currentPiecePosY + row][_currentPiecePosX + col] != 0){
                // There is a filled cell, indicating a collision, so return false.
                return false;
            }
        }
    }

    return true;
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

void Board::ClearRow(int rowIndex) {
    // Shift rows above the cleared row down
    int *tempRow = _grid[rowIndex];
    for (int i = rowIndex; i > 0; --i) {
        _grid[i] = _grid[i - 1];
    }

    //clear the top tow
    _grid[0] = tempRow;
    for (int j = 0; j < _width; ++j) {
        _grid[0][j] = 0;
    }
}

void Board::Clear() {
    for (unsigned row = 0; row < _height; ++row) {
        for (unsigned col = 0; col < _width; ++col) {
            _grid[row][col] = 0; 
        }
    }
    
    _currentPiece = nullptr;
}


/**
 * @brief Moves the current piece down and handles locking and row clearing.
 *
 * Moves the current piece down on the game board. If the move is not valid, the piece is locked
 * in place, and any full rows are cleared.
 *
 * @return A pair indicating whether the piece is locked and the number of cleared full rows.
 *         If no piece is present, an empty pair is returned.
 */
std::pair<bool, int> Board::MovePieceDown() {
    if (_currentPiece == nullptr) { 
        return {};
    }
 
    int newY = _currentPiecePosY + 1;
    
    if (IsValidMove(_currentPiecePosX, newY)) {
        _currentPiecePosY = newY;
        return {};
    }
    
    LockCurrentPiece();

    int fullRowIndex = getFullRow();
    unsigned clearedRows = 0;

    while (fullRowIndex != -1){
        ClearRow(fullRowIndex);
        clearedRows++;
        fullRowIndex = getFullRow();
    }

    return {true, clearedRows};
}

void Board::LockCurrentPiece(){
    int pieceRows = _currentPiece->getNumRows();
    int pieceCols = _currentPiece->getNumColumns();

    for(int i = 0; i < pieceRows; i++){
        for(int j = 0; j < pieceCols; j++){
            if(_currentPiece->getMatrix().data[i][j] != 0){
                _grid[_currentPiecePosY + i][_currentPiecePosX + j] = 1;
            }
        }
    }

    _currentPiece = nullptr;
}

int Board::getFullRow(){

    for(int i = _height - 1 ; i > 0; i--){
        bool rowFull = true;
        for(int j = 0; j < _width; j++){
            if(_grid[i][j] == 0){
                rowFull = false;
                break;
            }
        }

        if(rowFull == true){
            return i;
        }
    }

    return -1;
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