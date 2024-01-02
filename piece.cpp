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

Piece::ShapeMatrix Piece::customPieces[3];
int Piece::customPieceCount = 0;

Piece Piece::getRandomPiece()
{
    int randomIndex = rand() % (Piece::END + customPieceCount);
    if (randomIndex < Piece::END) {
        return Piece(static_cast<PieceType>(randomIndex));
    } else {
        return Piece(customPieces[randomIndex - Piece::END]);
    }
}

Piece::Piece(PieceType pt) : _matrix(shapeMatrices[pt])
{
}

Piece::Piece(const ShapeMatrix& matrix) : _matrix(matrix)
{
}

void Piece::addCustomPiece()
{
    if (customPieceCount < 3) {
        std::cout << "Enter the number of rows for the custom ShapeMatrix: ";
        std::cin >> customPieces[customPieceCount].rows;

        std::cout << "Enter the number of columns for the custom ShapeMatrix: ";
        std::cin >> customPieces[customPieceCount].cols;

        std::cout << "Enter the elements of the custom ShapeMatrix (0 or 1):\n";
        for (int i = 0; i < customPieces[customPieceCount].rows; ++i) {
            for (int j = 0; j < customPieces[customPieceCount].cols; ++j) {
                std::cin >> customPieces[customPieceCount].data[i][j];
            }
        }

        customPieceCount++;
    } else {
        std::cout << "You can add a maximum of 3 custom pieces." << std::endl;
    }
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

unsigned Piece::getRotationsLeft()
{
    if (ROTATE_MAX >= _cntRotate)
        return (ROTATE_MAX - _cntRotate);

    return 0;
}