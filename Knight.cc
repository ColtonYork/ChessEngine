#include "Knight.h"

Knight::Knight(unsigned char r, unsigned char c, bool isW)
    : Piece(r, c, isW){}

Piece* Knight::clone() const{
    return new Knight(row, col, isWhite);
}

pieceType Knight::getPieceType() const{
    return KNIGHT;
}

bool Knight::isLegalMove(unsigned char toRow, unsigned char toCol, Board& b) const{}

