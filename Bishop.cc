#include "Bishop.h"

Bishop::Bishop(unsigned char r, unsigned char c, bool isW)
    : Piece(r, c, isW){}

Piece* Bishop::clone() const{
    return new Bishop(row, col, isWhite);
}
