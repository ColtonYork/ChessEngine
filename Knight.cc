#include "Knight.h"

Knight::Knight(unsigned char r, unsigned char c, bool isW)
    : Piece(r, c, isW){}

Piece* Knight::clone() const{
    return new Knight(row, col, isWhite);
}
