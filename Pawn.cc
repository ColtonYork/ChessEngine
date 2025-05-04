#include "Pawn.h"


Pawn::Pawn(unsigned char r, unsigned char c, bool isW)
    : Piece(r, c, isW)
{
        hasMoved = false;
}

Piece* Pawn::clone() const{
    Pawn* p = new Pawn(row, col, isWhite);
    p->hasMoved = hasMoved;
    return p;
}

pieceType Pawn::getPieceType() const{
    return PAWN;
}

bool Pawn::isLegalMove(unsigned char toRow, unsigned char toCol, Board& b) const{}


