#include "Knight.h"
#include "../Game/Board.h"
#include <cmath>
Knight::Knight(unsigned char r, unsigned char c, bool isW)
    : Piece(r, c, isW){}

Piece* Knight::clone() const{
    return new Knight(row, col, isWhite);
}

pieceType Knight::getPieceType() const{
    return KNIGHT;
}

bool Knight::isLegalMove(unsigned char toRow, unsigned char toCol, const Board& b) const{
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

bool Knight::hasOneSpaceLegalMove(const Board* b) const{
    //see if there is a legal 1-space move
    if (endSpotLegal(row+2, col+1, *b) || endSpotLegal(row+2, col-1, *b) || endSpotLegal(row-2, col+1, *b) || endSpotLegal(row-2, col-1, *b) || endSpotLegal(row+1, col+2, *b) || 
    endSpotLegal(row+1, col-2, *b) || endSpotLegal(row-1, col+2, *b) || endSpotLegal(row-1, col-2, *b)) {return true;}

    return false;
}

bool Knight::endSpotLegal(unsigned char checkRow, unsigned char checkColumn, const Board& b) const{
    //check inboubnds
    if (checkRow > 7 || checkRow < 0 || checkColumn > 7 || checkColumn < 0) {return 0;}

    Piece* piece = b.getBoard(checkRow, checkColumn);

    if (piece == nullptr) {return true;}
    else if (isWhite == piece->getIsWhite()) {return false;}
    
    return true;
}



bool Knight::hasVerifiedMove(Board* b){
    if (isLegalMove(row + 2, col + 1, *b) && !b->moveCausesSelfCheck(row, col, row + 2, col + 1)) {return true;}
    if (isLegalMove(row + 2, col - 1, *b) && !b->moveCausesSelfCheck(row, col, row + 2, col - 1)) {return true;}
    if (isLegalMove(row - 2, col + 1, *b) && !b->moveCausesSelfCheck(row, col, row - 2, col + 1)) {return true;}
    if (isLegalMove(row - 2, col - 1, *b) && !b->moveCausesSelfCheck(row, col, row - 2, col - 1)) {return true;}
    if (isLegalMove(row + 1, col + 2, *b) && !b->moveCausesSelfCheck(row, col, row + 1, col + 2)) {return true;}
    if (isLegalMove(row + 1, col - 2, *b) && !b->moveCausesSelfCheck(row, col, row + 1, col - 2)) {return true;}
    if (isLegalMove(row - 1, col + 2, *b) && !b->moveCausesSelfCheck(row, col, row - 1, col + 2)) {return true;}
    if (isLegalMove(row - 1, col - 2, *b) && !b->moveCausesSelfCheck(row, col, row - 1, col - 2)) {return true;}

    return false;
}

int Knight::getPieceValue() const{
    return 3;
}



