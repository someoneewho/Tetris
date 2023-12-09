#include "piece.h"
#include <iostream>
#include <cstring>
using namespace std;

const char* shapes[Piece::END] = {"0,1,0;1,1,1;0,1,0", 
                                    "1,1;1,1",
                                    "1,0;1,1",
                                    "1;1;1",
                                    "0,1,1;1,1,0",
                                    "1,0,1;1,1,1",
                                    "1,0,0;1,1,0;0,1,0",
                                    "0,1,0;1,1,1;1,0,1",
                                    "1,0,0;1,1,1;0,0,1",
                                    "0,1,0;1,1,1"};

Piece::Piece(int numRows, int numColumns) {
    _numRows = numRows;
    _numColumns = numColumns;
    _shape = new char*[_numRows];

    for (int i = 0; i < _numRows; i++) {
        _shape[i] = new char[_numColumns];
    }

    for(int i = 0; i < _numRows; i++){
        for(int j = 0; j < _numColumns; j++){
           _shape[i][j] = rand()%2 ? '0' : '1';
        }
    }
}

Piece::Piece(PieceType pt){

}

void Piece::Rotate(){

}

void Piece::print(){
    std::cout << _numRows << " x " << _numColumns << "\n";

    for(int i = 0; i < _numRows; i++){
        for(int j = 0; j < _numColumns; j++){
           std::cout << _shape[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;

}

Piece::~Piece() {
    for (int i = 0; i < _numRows; i++) {
        delete[] _shape[i];
    }
    delete[] _shape;
}
