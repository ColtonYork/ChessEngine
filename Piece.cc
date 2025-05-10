#include "Piece.h"
#include "Board.h"
#include <iostream>

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

bool Piece::endSpotLegal(unsigned char checkRow, unsigned char checkColumn, const Board& b) const{
    Piece* piece = b.getBoard(checkRow, checkColumn);

    if (piece == nullptr) {return true;}
    else if (isWhite == piece->getIsWhite()) {return false;}
    
    return true;
}

bool Piece::spotIsOpponent(unsigned char checkRow, unsigned char checkCol, const Board& b) const{
    Piece* p = b.getBoard(checkRow, checkCol);
    if ((p == nullptr) || (isWhite == p->getIsWhite())) {return false;}

    return true;
}

unsigned char Piece::getRow() const{
    return row;
}

unsigned char Piece::getCol() const{
    return col;
}

bool Piece::getHasMoved() const{
    return false;
}

void Piece::setRow (unsigned char r){
    if (r > 7 || r < 0) {std::cout << "invalid index" << '\n'; return;}
    row = r;
}


void Piece::setCol (unsigned char c){
    if (c > 7 || c < 0) {std::cout << "invalid index" << '\n'; return;}
    col = c;

}
bool Piece::isLegalCastleMove(bool kingSide, const Board& b) const{
    return false;
}



