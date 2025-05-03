#include "Pawn.h"


Pawn::Pawn(unsigned char r, unsigned char c, bool isW)
    : Piece(r, c, isW)
    {
        hasMoved = false;
    }
