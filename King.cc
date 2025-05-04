#include "King.h"

King::King(unsigned char r, unsigned char c, bool isW)
    : Piece(r, c, isW)
{
    hasMoved = false;
    inCheck = false;
}

Piece* King::clone() const{
    King* k = new King(row, col, isWhite);
    k->hasMoved = hasMoved;
    k->inCheck = inCheck;
    return k;
}

pieceType King::getPieceType() const{
    return KING;
}




