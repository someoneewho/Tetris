#include "piece.h"
#include <iostream>
#include <cstring>
using namespace std;

static const int ROTATE_MAX = 3;

Piece::ShapeMatrix shapeMatrices[] = {
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

Piece::Piece(const ShapeMatrix &matrix) : _matrix(matrix)
{

}

Piece::Piece(PieceType pt) : _matrix(shapeMatrices[pt])
{

}

Piece::ShapeMatrix Piece::getRotatedShape(RotateType rt){
   ShapeMatrix rMatrix;

    for(int i = 0; i < _matrix.rows; i++){
        for(int j = 0; j < _matrix.cols; j++){
            if (rt == ROTATE_CW)
                rMatrix.data[j][_matrix.rows - i - 1] = _matrix.data[i][j];
            else
                rMatrix.data[_matrix.cols - j - 1][i] = _matrix.data[i][j];
        }
    }

    rMatrix.cols = _matrix.rows;
    rMatrix.rows = _matrix.cols;
 
    return rMatrix;
}

bool Piece::Rotate(RotateType rt)
{
    if (_cntRotate >= ROTATE_MAX){
        return false;
    }

    _cntRotate++;

    _matrix = getRotatedShape(rt);

    return true;
}