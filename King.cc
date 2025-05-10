#include "King.h"
#include "Board.h"
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

    if (!((abs(rowChange) == 1 && abs(colChange) == 1) || (abs(rowChange) == 0 && abs(colChange) == 1) || (abs(rowChange) == 1 && abs(colChange) == 0))) {return false;}

    //check legal end spot
    if (!endSpotLegal(toRow, toCol, b)) {return false;}

    return true;
}

bool King::isLegalCastleMove(bool kingSide, const Board& b) const{
    //Check inbounds
    if (!moveIsInbounds(row, col + 3) || !moveIsInbounds(row, col - 4)) {return false;}
    
    //False if king has moved
    if (hasMoved) {return false;}
    
    //Illegal if king is in check
    if (b.squareUnderAttack(row, col, !isWhite)) {return false;}

    //kingside castle logic
    if (kingSide)
        {
            //return if castle spots arent open
            if (b.getBoard(row, col + 1) != nullptr || b.getBoard(row, col + 2) != nullptr) {return false;}

            //check if castle spots are attacked
            if (b.squareUnderAttack(row, col + 1, !isWhite) || b.squareUnderAttack(row, col + 2, !isWhite)) {return false;}

            //Determine if rook is at correct spot and same color and hasnt moved
            Piece* piece = b.getBoard(row, col + 3);
            if (piece == nullptr) {return false;}
            if (piece->getPieceType() != ROOK) {return false;}
            if (piece->getIsWhite() != isWhite) {return false;}
            if (piece->getHasMoved()) {return false;}  
            
            return true;
        }

    //queen side castle logic
    if (b.getBoard(row, col - 1) != nullptr || b.getBoard(row, col - 2) != nullptr || b.getBoard(row, col - 3) != nullptr) {return false;}

    //check if castle spots are attacked
    if (b.squareUnderAttack(row, col - 1, !isWhite) || b.squareUnderAttack(row, col - 2, !isWhite)) {return false;}

    //Determine if rook is at correct spot and same color and hasnt moved
    Piece* piece = b.getBoard(row, col - 4);
    if (piece == nullptr) {return false;}
    if (piece->getPieceType() != ROOK) {return false;}
    if (piece->getIsWhite() != isWhite) {return false;}
    if (piece->getHasMoved()) {return false;} 

    return true;
}

bool King::getHasMoved() const{
    return hasMoved;
}






