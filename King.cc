#include "King.h"

King::King(unsigned char r, unsigned char c, bool isW)
    : Piece(r, c, isW)
    {
    hasMoved = false;
    inCheck = false;
    }
