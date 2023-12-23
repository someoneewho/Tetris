#include "piece.h"
#include <iostream>
#include <cstring>
using namespace std;

static const int ROTATE_MAX = 3;

struct ShapeMatrix {
    int rows;
    int cols;
    int data[3][3];
};

ShapeMatrix shapeMatrices[] = {
    {3, 3, {{0, 1, 0}, {1, 1, 1}, {0, 1, 0}}},      // Plus Sign
    {2, 2, {{1, 1}, {1, 1}}},                       // Small Square
    {2, 2, {{1, 0}, {1, 1}}},                       // Corner Piece
    {3, 1, {{1}, {1}, {1}}},                        // Tall Tower
    {2, 3, {{0, 1, 1}, {1, 1, 0}}},                 // Zigzag
    {2, 3, {{1, 0, 1}, {1, 1, 1}}},                 // U Shape
    {3, 2, {{1, 0}, {1, 1}, {0, 1}}},               // Step Shape
    {3, 3, {{0, 1, 0}, {1, 1, 1}, {1, 0, 1}}},      // Arrow Pointing Up
    {3, 3, {{1, 0, 0}, {1, 1, 1}, {0, 0, 1}}},      // Double Zigzag
    {2, 3, {{0, 1, 0}, {1, 1, 1}}}                  // Pyramid
};

Piece::Piece(int numRows, int numColumns) : _numRows(numRows), _numColumns(numColumns)
{
    _matrix = new int*[_numRows]{};

    for (int i = 0; i < _numRows; i++) {
        _matrix[i] = new int[_numColumns]{};
    }
}

Piece::Piece(PieceType pt) : Piece(shapeMatrices[pt].rows, shapeMatrices[pt].cols)
{
    for(int i = 0; i < _numRows; i++){
        for(int j = 0; j < _numColumns; j++){
            _matrix[i][j] = shapeMatrices[pt].data[i][j];
        }
    }
}

bool Piece::RotateCW()
{
    if (_cntRotate >= ROTATE_MAX){
        return false;
    }

    _cntRotate++;

    int **temp = new int*[_numColumns];

    for(int i = 0 ; i < _numColumns; i++){
        temp[i] = new int[_numRows];
    }

    for(int i = 0; i < _numRows; i++){
        for(int j = 0; j < _numColumns; j++){
            temp[j][_numRows - i - 1] = _matrix[i][j];
        }
    }

    for (int i = 0; i < _numRows; i++) {
        delete[] _matrix[i];
    }
    delete[] _matrix;

    std::swap(_numRows, _numColumns);
    _matrix = temp;

    return true;
}

bool Piece::RotateCCW(){

    if (_cntRotate >= ROTATE_MAX){
        return false;
    }

    _cntRotate++;

    int **temp = new int*[_numColumns];

    for(int i = 0 ; i < _numColumns; i++){
        temp[i] = new int[_numRows];
    }

    for(int i = 0; i < _numRows; i++){
        for(int j = 0; j < _numColumns; j++){
            temp[_numColumns - j - 1][i] = _matrix[i][j];
        }
    }

    for (int i = 0; i < _numRows; i++) {
        delete[] _matrix[i];
    }
    delete[] _matrix;

    std::swap(_numRows, _numColumns);
    _matrix = temp;

    return true;
}

void Piece::print(){
    std::cout << _numRows << " x " << _numColumns << "\n";

    for(int i = 0; i < _numRows; i++){
        for(int j = 0; j < _numColumns; j++){
           std::cout << (_matrix[i][j] ? 'X' : '.') << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;

}

Piece::~Piece()
{
    for (int i = 0; i < _numRows; i++) {
        delete[] _matrix[i];
    }
    delete[] _matrix;
}
