#include "Rook.h"

Rook::Rook(unsigned char r, unsigned char c, bool isW)
    : Piece(r, c, isW)
    {
    hasMoved = false;
    }
