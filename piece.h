#pragma once

class Piece {
public: 

    struct ShapeMatrix {
        int rows;
        int cols;
        int data[3][3];
    };


    enum PieceType : int {
        PLUS_SIGN,
        SMALL_SQUARE,
        CORNER_PIECE,
        TALL_TOWER,
        ZIGZAG,
        U_SHAPE,
        STEP_SHAPE,
        ARROW_UP,
        DOUBLE_ZIGZAG,
        PYRAMID,
        END
    };


    Piece(int numRows, int numColumns);
    Piece(PieceType pt);
    ~Piece();

    bool RotateCW();
    bool RotateCCW();
    void print();

    int getNumRows() {
        return _numRows;
    }

    int getNumColumns() {
        return _numColumns;
    }

    const int** getMatrix() {
        return const_cast<const int**>(_matrix);
    }   

private:
    int _numRows = 0;
    int _numColumns = 0;
    int **_matrix = nullptr;
    int _cntRotate = 0;

};
