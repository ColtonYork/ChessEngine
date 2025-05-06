#include "King.h"
#include <cmath>

King::King(unsigned char r, unsigned char c, bool isW)
    : Piece(r, c, isW)
{
    hasMoved = false;
    inCheck = false;
}

Piece* King::clone() const{
    King* k = new King(row, col, isWhite);
    k->hasMoved = hasMoved;
    k->inCheck = inCheck;
    return k;
}

pieceType King::getPieceType() const{
    return KING;
}

bool King::isLegalMove(unsigned char toRow, unsigned char toCol, const Board& b) const{
    //Check if move is inbounds
    if(!moveIsInbounds(toRow, toCol)) {return false;}

    //get change in rows/cols
    int rowChange = abs(row - toRow);
    int colChange = abs(col - toCol);

    if (!((rowChange == 1 && colChange == 1) || (rowChange == 0 && colChange == 1) || (rowChange == 1 && colChange == 0))) {return false;}

    //check legal end spot
    if (!endSpotLegal(toRow, toCol, b)) {return false;}

    return true;
}

bool King::isLegalCastleMove(bool kingSide, const Board& b) const{

}






