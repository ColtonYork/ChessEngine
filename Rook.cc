#include "Rook.h"

Rook::Rook(unsigned char r, unsigned char c, bool isW)
    : Piece(r, c, isW)
{
    hasMoved = false;
}

Piece* Rook::clone() const{
    Rook* r = new Rook(row, col, isWhite);
    r->hasMoved = hasMoved;
    return r;
}

