#pragma once

class Board;

class Piece {
public: 

    Piece() = default; ////BU NE DEMEK???????

    struct ShapeMatrix {
        int rows = 0;
        int cols = 0;
        int data[3][3] = {};
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

    enum RotateType{
        ROTATE_CW,
        ROTATE_CCW,
    };

    Piece(const ShapeMatrix &matrix);
    Piece(PieceType pt);

    bool Rotate(RotateType rt);
    ShapeMatrix getRotatedShape(RotateType rt);

    int getNumRows() {
        return _matrix.rows;
    }

    int getNumColumns() {
        return _matrix.cols;
    }

    const ShapeMatrix& getMatrix() {
        return _matrix;
    }   

    unsigned getRotationsLeft();

    static Piece getRandomPiece();
    static void addCustomPiece();

private:
    ShapeMatrix _matrix;
    int _cntRotate = 0;

    static ShapeMatrix customPieces[3];
    static int customPieceCount;

};
