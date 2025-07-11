#include "Pawn.h"
#include "../Game/Board.h"
#include <cmath>


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

bool Pawn::isLegalMove(unsigned char toRow, unsigned char toCol, const Board& b) const{
    //check if move is inbounds
    if(!moveIsInbounds(toRow, toCol)) {return false;}

    //one-up move
    if (col == toCol && ((isWhite && row + 1 == toRow) || (!isWhite && row - 1 == toRow))) {return isLegalUpOneMove(toRow, toCol, b);}

    //two-up move
    if (col == toCol && ((isWhite && row + 2 == toRow) || (!isWhite && row - 2 == toRow))) {return isLegalTwoUpMove(toRow, toCol, b);}

    //capture move logic
    if ((abs(toCol - col) == 1) && ((isWhite && row + 1 == toRow) || (!isWhite && row - 1 == toRow))) {return isLegalTakePieceMove(toRow, toCol, b);}

    return false;
    
}

bool Pawn::isLegalTakePieceMove(unsigned char toRow, unsigned char toCol, const Board& b) const{    
    if (!spotIsOpponent(toRow, toCol, b)) {return false;}
    return true;
}

bool Pawn::isLegalUpOneMove(unsigned char toRow, unsigned char toCol, const Board& b) const{
    if(b.getBoard(toRow, toCol) != nullptr){return false;}
    return true;
}

bool Pawn::isLegalTwoUpMove(unsigned char toRow, unsigned char toCol, const Board& b) const{
    if (hasMoved) {return false;}

    //make sure path is clear
    if (isWhite)
    {
        if (b.getBoard(row + 1, col) != nullptr || b.getBoard(row + 2, col) != nullptr) {return false;}
    }
    else
    {
        if (b.getBoard(row - 1, col) != nullptr || b.getBoard(row - 2, col) != nullptr) {return false;}
    }

    return true;
}

bool Pawn::promotionMove(unsigned char toRow) const{
    if (isWhite && toRow == 7) {return true;}
    else if (!isWhite && toRow == 0) {return true;}

    return false;
}

bool Pawn::getHasMoved() const{
    return hasMoved;
}

bool Pawn::endSpotLegal(unsigned char checkRow, unsigned char checkColumn, const Board& b) const{
    return true;
}

bool Pawn::hasOneSpaceLegalMove(const Board* b) const{
    if (isWhite)
        {
            if (isLegalMove(row + 2, col, *b) || isLegalMove(row + 1, col, *b) || isLegalMove(row + 1, col + 1, *b) || isLegalMove(row + 1, col - 1, *b)) {return true;}
        }
    else
        {
            if (isLegalMove(row - 2, col, *b) || isLegalMove(row - 1, col, *b) || isLegalMove(row - 1, col - 1, *b) || isLegalMove(row - 1, col + 1, *b)) {return true;}
        }
    return false;
}

bool Pawn::hasVerifiedMove(Board* b){
    if (isWhite)
        {
            if (isLegalMove(row + 2, col, *b) && !b->moveCausesSelfCheck(row, col, row + 2, col)) {return true;}
            if (isLegalMove(row + 1, col, *b) && !b->moveCausesSelfCheck(row, col, row + 1, col)) {return true;}
            if (isLegalMove(row + 1, col - 1, *b) && !b->moveCausesSelfCheck(row, col, row + 1, col - 1)) {return true;}
            if (isLegalMove(row + 1, col + 1, *b) && !b->moveCausesSelfCheck(row, col, row + 1, col + 1)) {return true;}

            return false;
        }
    else
        {
            if (isLegalMove(row - 2, col, *b) && !b->moveCausesSelfCheck(row, col, row - 2, col)) {return true;}
            if (isLegalMove(row - 1, col, *b) && !b->moveCausesSelfCheck(row, col, row - 1, col)) {return true;}
            if (isLegalMove(row - 1, col - 1, *b) && !b->moveCausesSelfCheck(row, col, row - 1, col - 1)) {return true;}
            if (isLegalMove(row -1, col + 1, *b) && !b->moveCausesSelfCheck(row, col, row - 1, col + 1)) {return true;}

            return false;
        }


}

int Pawn::getPieceValue() const{
    return 1;
}

void Pawn::setHasMoved(bool hm){
    hasMoved = hm;
}

void Pawn::computePossibleMoves(Board* b, std::priority_queue<moveStringAndScore>& q){
    std::string startingMove = "p" + getFirstSquareOfMoveString();
    std::string fullMove = startingMove;

    if (isWhite)
        {
            if (isLegalMove(row + 2, col, *b) && !b->moveCausesSelfCheck(row, col, row + 2, col)) 
                {
                    moveStringAndScore moveResult;
                    moveResult.move = fullMove + getLastPartOfMoveString(row + 2, col);
                    q.push(moveResult);
                }
            
            if (isLegalMove(row + 1, col, *b) && !b->moveCausesSelfCheck(row, col, row + 1, col)) 
                {
                    moveStringAndScore moveResult;
                    moveResult.move = fullMove + getLastPartOfMoveString(row + 1, col);
                    q.push(moveResult); 
                }
            
            if (isLegalMove(row + 1, col - 1, *b) && !b->moveCausesSelfCheck(row, col, row + 1, col - 1)) 
                {
                    Piece* takePiece = b->getBoard(row + 1, col - 1);

                    moveStringAndScore moveResult;

                    moveResult.moveQuickScore = takePiece->getPieceValue() - 1;

                    moveResult.move = fullMove + getLastPartOfMoveString(row + 1, col - 1);

                    q.push(moveResult);
                }

            if (isLegalMove(row + 1, col + 1, *b) && !b->moveCausesSelfCheck(row, col, row + 1, col + 1)) 
                {
                    Piece* takePiece = b->getBoard(row + 1, col + 1);

                    moveStringAndScore moveResult;

                    moveResult.moveQuickScore = takePiece->getPieceValue() - 1;

                    moveResult.move = fullMove + getLastPartOfMoveString(row + 1, col + 1);

                    q.push(moveResult);
                }
        }

    else 
        {
            if (isLegalMove(row - 2, col, *b) && !b->moveCausesSelfCheck(row, col, row - 2, col))                
                {
                    moveStringAndScore moveResult;
                    moveResult.move = fullMove + getLastPartOfMoveString(row - 2, col);
                    q.push(moveResult);
                }
        
            if (isLegalMove(row - 1, col, *b) && !b->moveCausesSelfCheck(row, col, row - 1, col)) 
                {
                    moveStringAndScore moveResult;
                    moveResult.move = fullMove + getLastPartOfMoveString(row - 1, col);
                    q.push(moveResult); 
                }
        
            if (isLegalMove(row - 1, col - 1, *b) && !b->moveCausesSelfCheck(row, col, row - 1, col - 1)) 
                {
                    Piece* takePiece = b->getBoard(row - 1, col - 1);

                    moveStringAndScore moveResult;

                    moveResult.moveQuickScore = takePiece->getPieceValue() - 1;

                    moveResult.move = fullMove + getLastPartOfMoveString(row - 1, col - 1);

                    q.push(moveResult);
                }

            if (isLegalMove(row - 1, col + 1, *b) && !b->moveCausesSelfCheck(row, col, row - 1, col + 1)) 
                {
                    Piece* takePiece = b->getBoard(row - 1, col + 1);

                    moveStringAndScore moveResult;

                    moveResult.moveQuickScore = takePiece->getPieceValue() - 1;

                    moveResult.move = fullMove + getLastPartOfMoveString(row - 1, col + 1);

                    q.push(moveResult);
                }
        }


}












