#include "King.h"
#include "../Game/Board.h"
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

bool King::endSpotLegal(unsigned char checkRow, unsigned char checkColumn, const Board& b) const{
        //check inboubnds
    if (checkRow > 7 || checkRow < 0 || checkColumn > 7 || checkColumn < 0) {return 0;}

    Piece* piece = b.getBoard(checkRow, checkColumn);

    if (piece == nullptr) {return true;}
    else if (isWhite == piece->getIsWhite()) {return false;}
    
    return true;
}

bool King::hasOneSpaceLegalMove(const Board* b) const{
    if (endSpotLegal(row+1, col, *b) || endSpotLegal(row-1, col, *b) || endSpotLegal(row, col-1, *b) || endSpotLegal(row, col+1, *b) 
    || endSpotLegal(row+1, col+1, *b) || endSpotLegal(row-1, col-1, *b) || endSpotLegal(row+1, col-1, *b) || endSpotLegal(row-1, col+1, *b)) {return true;}
    return false;
}

bool King::hasVerifiedMove(Board* b){
    //up down left right
    if (isLegalMove(row + 1, col, *b) && !b->moveCausesSelfCheck(row, col, row + 1, col)) {return true;}
    if (isLegalMove(row - 1, col, *b) && !b->moveCausesSelfCheck(row, col, row - 1, col)) {return true;}
    if (isLegalMove(row, col - 1, *b) && !b->moveCausesSelfCheck(row, col, row, col - 1)) {return true;}
    if (isLegalMove(row, col + 1, *b) && !b->moveCausesSelfCheck(row, col, row, col + 1)) {return true;}

    //upleft upright downleft downright
    if (isLegalMove(row + 1, col - 1, *b) && !b->moveCausesSelfCheck(row, col, row + 1, col - 1)) {return true;}
    if (isLegalMove(row + 1, col + 1, *b) && !b->moveCausesSelfCheck(row, col, row + 1, col + 1)) {return true;}
    if (isLegalMove(row - 1, col - 1, *b) && !b->moveCausesSelfCheck(row, col, row - 1, col - 1)) {return true;}
    if (isLegalMove(row - 1, col + 1, *b) && !b->moveCausesSelfCheck(row, col, row - 1, col + 1)) {return true;}

    return false;
}

int King::getPieceValue() const{
    return 1000;
}

void King::setHasMoved(bool hm){
    hasMoved = hm;
}








