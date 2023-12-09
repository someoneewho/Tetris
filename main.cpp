#include <time.h>
#include <iostream>
#include "board.h"
#include "game.h"

using namespace std;

int main()
{
    srand(time(NULL));
    Board board(10, 20);
    Game game;
    Piece p(3, 3);
    p.print();
    p.Rotate();
    p.print();
    return 0;
}