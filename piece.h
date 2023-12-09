#pragma once

class Piece {
public: 
    enum PieceType {
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
    void Rotate();
    void print();
    

private:
    int _numRows = 0;
    int _numColumns = 0;
    char **_shape = nullptr;

};
