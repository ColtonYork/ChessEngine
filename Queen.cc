#include "Queen.h"

Queen::Queen(unsigned char r, unsigned char c, bool isW)
    : Piece(r, c, isW){}

Piece* Queen::clone() const{
    return new Queen(row, col, isWhite);
}

pieceType Queen::getPieceType() const{
    return QUEEN;
}