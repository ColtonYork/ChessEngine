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

bool Pawn::isLegalMove(unsigned char toRow, unsigned char toCol, Board& b) const{
    //check if move is inbounds
    if(!moveIsInbounds(toRow, toCol)) {return false;}

    //capture move logic
    /*
        ??????????????????????????????????????????????
        ??????????????????????????????????????????????
        Need to check en passant here probably
    */
    if (col != toCol) {return takePieceLegalMove(toRow, toCol, b);}

    




}

bool Pawn::takePieceLegalMove(unsigned char toRow, unsigned char toCol, Board& b) const{    
    if (!spotIsOpponent(toRow, toCol, b)) {return false;}
    return true;
}



