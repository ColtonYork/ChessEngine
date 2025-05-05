#include "Knight.h"
#include <cmath>
Knight::Knight(unsigned char r, unsigned char c, bool isW)
    : Piece(r, c, isW){}

Piece* Knight::clone() const{
    return new Knight(row, col, isWhite);
}

pieceType Knight::getPieceType() const{
    return KNIGHT;
}

bool Knight::isLegalMove(unsigned char toRow, unsigned char toCol, Board& b) const{
    //checks if move is in bounds
    if (!moveIsInbounds(toRow, toCol)) {return false;}

    //Check for correct knight movement
    int rowDiffs = abs(row - toRow);
    int colDiffs = abs(col - toCol);

    if (!((rowDiffs == 2 && colDiffs == 1) || (rowDiffs == 1 && colDiffs == 2))) {return false;}

    //Checks for end spot legality
    if (!endSpotLegal(toRow, toCol, b)) {return false;}

    return true;
}


