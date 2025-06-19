#include "Rook.h"
#include "Board.h"
#include <iostream>

Rook::Rook(unsigned char r, unsigned char c, bool isW)
    : Piece(r, c, isW)
{
    hasMoved = false;
}

Piece* Rook::clone() const{
    Rook* r = new Rook(row, col, isWhite);
    r->hasMoved = hasMoved;
    return r;
}

pieceType Rook::getPieceType() const{
    return ROOK;
}

bool Rook::isLegalBetween(bool rowMove, unsigned char from, unsigned char to, const Board& b) const{
    int difference = from - to;

    //check for move left/down
    if (difference > 0)
    {
        for (int i = from - 1; i > to; i--)
        {
            //checks for row movement
            if (rowMove)
            {
                if (b.getBoard(i, col) != nullptr) {return false;}
            }
            //checks for column movement
            else 
            {
                if (b.getBoard(row, i) != nullptr) {return false;}
            }
        }
    }
    //checks for move right/up
    else
    {
        for (int i = from + 1; i < to; i++)
        {
            if (rowMove)
            {
                if (b.getBoard(i, col) != nullptr) {return false;}
            }

            else 
            {
                if (b.getBoard(row, i) != nullptr) {return false;}
            }
        }
        
    }

    return true;
}

bool Rook::isLegalMove(unsigned char toRow, unsigned char toCol, const Board& b) const{
    //check for move inbounds
    if (!moveIsInbounds(toRow, toCol)) {return false;}

    //checks for correct Rook movement
    if((row == toRow && col == toCol) || (row != toRow && col != toCol)) {return false;}

    //check for pieces in between
    bool rowMove = false;

    if (row != toRow) {rowMove = true;}

    if (rowMove)
        {
            if(!isLegalBetween(true, row, toRow, b)) {return false;}
        }
    else 
        {
            if(!isLegalBetween(false, col, toCol, b)) {return false;}
        }   

    //check end spot
    if (!endSpotLegal(toRow, toCol, b)){return false;}

    return true;    
}

bool Rook::getHasMoved() const{
    return hasMoved;
}

bool Rook::endSpotLegal(unsigned char checkRow, unsigned char checkColumn, const Board& b) const{
    //check inboubnds
    if (checkRow > 7 || checkRow < 0 || checkColumn > 7 || checkColumn < 0) {return false;}

    Piece* piece = b.getBoard(checkRow, checkColumn);

    if (piece == nullptr) {return true;}
    else if (isWhite == piece->getIsWhite()) {return false;}
    
    return true;
}

bool Rook::hasOneSpaceLegalMove(const Board* b) const{
    //see if there is a legal 1-space move
    if (endSpotLegal(row+1, col, *b) || endSpotLegal(row-1, col, *b) || endSpotLegal(row, col-1, *b) || endSpotLegal(row, col+1, *b)) {return true;}
    return false;
}

bool Rook::hasVerifiedMove(Board* b) {
    bool up = endSpotLegal(row + 1, col, *b);
    bool down = endSpotLegal(row - 1, col, *b);
    bool left = endSpotLegal(row, col - 1, *b);
    bool right = endSpotLegal(row, col + 1, *b);

    return existsPossibleMove(b, up, down, left, right);
}

int Rook::getPieceValue() const{
    return 5;
}

bool Rook::existsPossibleMove(Board* b, bool up, bool down, bool left, bool right){

    if (up)
        {
        for (int i = row + 1; i < 8; i++)
            {
                bool takesPiece = false;
                //break when path gets cut off by own piece
                if (b->getBoard(i, col) != nullptr && getIsWhite() == (b->getBoard(i, col)->getIsWhite())) {break;}
                if (b->getBoard(i, col) != nullptr && getIsWhite() != (b->getBoard(i, col)->getIsWhite())) {takesPiece = true;}


                if (isLegalMove(i, col, *b) && !b->moveCausesSelfCheck(row, col, i, col)) {std::cout << "Rook can move to: " << i << ", " << col << '\n'; return true;}\

                if (takesPiece) {break;}
            }
        }

    if (down)
        {
        for (int i = row - 1; i >= 0; i--)
            {
                bool takesPiece = false;

                //break when path gets cut off by own piece
                if (b->getBoard(i, col) != nullptr && getIsWhite() == (b->getBoard(i, col)->getIsWhite())) {break;}
                if (b->getBoard(i, col) != nullptr && getIsWhite() != (b->getBoard(i, col)->getIsWhite())) {takesPiece = true;}


                if (isLegalMove(i, col, *b) && !b->moveCausesSelfCheck(row, col, i, col)) {std::cout << "Rook can move to: " << i << ", " << col << '\n'; return true;}
                
                if (takesPiece) {break;}
            }
        }

    if (left)
        {
        for (int i = col - 1; i >= 0; i--)
            {
                bool takesPiece = false;

                //break when path gets cut off by own piece
                if (b->getBoard(row, i) != nullptr && getIsWhite() == (b->getBoard(row, i)->getIsWhite())) {break;}
                if (b->getBoard(row, i) != nullptr && getIsWhite() != (b->getBoard(row, i)->getIsWhite())) {takesPiece = true;}


                if (isLegalMove(row, i, *b) && !b->moveCausesSelfCheck(row, col, row, i)) {std::cout << "Rook can move to: " << row << ", " << i << '\n'; return true;}

                if (takesPiece) {break;}
            }
        }
        
    if (right)
        {
        for (int i = col + 1; i < 8; i++)
            {
                bool takesPiece = false;

                //break when path gets cut off
                if (b->getBoard(row, i) != nullptr && getIsWhite() == (b->getBoard(row, i)->getIsWhite())) {break;}
                if (b->getBoard(row, i) != nullptr && getIsWhite() != (b->getBoard(row, i)->getIsWhite())) {takesPiece = true;}
                
                if (isLegalMove(row, i, *b) && !b->moveCausesSelfCheck(row, col, row, i)) {std::cout << "Rook can move to: " << row << ", " << i << '\n'; return true;}

                if (takesPiece) {break;}
            }
        }
    return false;
}












