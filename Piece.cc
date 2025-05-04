#include "Piece.h"


Piece::Piece(unsigned char r, unsigned char c, bool isW){
    row = r;
    col = c;
    isWhite = isW;
}

bool Piece::getIsWhite(){
    return isWhite;
}