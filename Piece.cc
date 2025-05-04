#include "Piece.h"


Piece::Piece(unsigned char r, unsigned char c, bool isW){
    row = r;
    col = c;
    isWhite = isW;
}

bool Piece::getIsWhite(){
    return isWhite;
}

bool Piece::moveIsInbounds(unsigned char toRow, unsigned char toCol) const{
    if (toRow > 7 || toCol > 7) {return false;}
    else{return true;}
}

bool Piece::endSpotLegal(unsigned char checkRow, unsigned char checkColumn, Board& b) const{
    Piece* piece = b.getBoard(checkRow, checkColumn);

    if (piece == nullptr) {return true;}
    else if (isWhite == piece->getIsWhite()) {return false;}
    
    return true;
}
