#include "Rook.h"

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

bool Rook::isLegalBetween(bool rowMove, unsigned char from, unsigned char to, Board& b) const{
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

bool Rook::isLegalMove(unsigned char toRow, unsigned char toCol, Board& b) const{
    //check for move inbounds
    if (!moveIsInbounds(toRow, toCol)) {return false;}

    //checks for correct Rook movement
    if((row == toRow && col == toCol) || (row != toRow && col != toCol)) {return false;}

    //check for pieces in between
    bool rowMove = false;

    if (row != toRow) {rowMove = true;}

    if (rowMove)
        {
            if(isLegalBetween(true, row, toRow, b) == false) {return false;}
        }
    else 
        {
            if(isLegalBetween(false, col, toCol, b) == false) {return false;}
        }   

        //check end spot
        if (!endSpotLegal(toRow, toCol, b)){return false;}

        return true;    
}


