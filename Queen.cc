#include "Queen.h"
#include "Board.h"
#include <cmath>

Queen::Queen(unsigned char r, unsigned char c, bool isW)
    : Piece(r, c, isW){}

Piece* Queen::clone() const{
    return new Queen(row, col, isWhite);
}

pieceType Queen::getPieceType() const{
    return QUEEN;
}

bool Queen::isLegalMove(unsigned char toRow, unsigned char toCol, const Board& b) const{
    //check for move inbounds
    if (!moveIsInbounds(toRow, toCol)) {return false;}

    //Checks for Rook-based queen movement
    if ((row == toRow && col != toCol) || (row != toRow && col == toCol)) {return isLegalRookMovement(toRow, toCol, b);}


    
    //Checks for bishop-based queen movement
    int rowChange = abs(row - toRow);
    int colChange = abs(col - toCol);

    if(rowChange == colChange) {return isLegalBishopMovement(toRow, toCol, b);}

    return false;  
}

bool Queen::isLegalRookMovement(unsigned char toRow, unsigned char toCol, const Board& b) const{
    //check for pieces in between
    bool rowMove = false;

    if (row != toRow) {rowMove = true;}

    if (rowMove)
        {
            if(!isLegalBetweenRookMovement(true, row, toRow, b)) {return false;}
        }
    else 
        {
            if(!isLegalBetweenRookMovement(false, col, toCol, b)) {return false;}
        }   

    //check end spot
    if (!endSpotLegal(toRow, toCol, b)){return false;}

    return true;
}

bool Queen::isLegalBetweenRookMovement(bool rowMove, unsigned char from, unsigned char to, const Board& b) const{
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

bool Queen::isLegalBishopMovement(unsigned char toRow, unsigned char toCol, const Board& b) const{
    //Check which diagonal
    bool upLeft = false;
    bool upRight = false;
    bool downLeft = false;
    bool downRight = false;

    if((row - toRow < 0) && (col - toCol < 0)) {upRight = true;}
    else if ((row - toRow > 0) && (col - toCol > 0)) {downLeft = true;}
    else if ((row - toRow > 0) && (col - toCol < 0)) {downRight = true;}
    else if ((row - toRow < 0) && (col - toCol > 0)) {upLeft = true;}

    //check if path is clear
    if (!isLegalBetweenBishopMovement(upLeft, upRight, downLeft, downRight, toRow, toCol, b)) {return false;}

    //Check endspot
    if (!endSpotLegal(toRow, toCol, b)) {return false;}

    return true;
}

bool Queen::isLegalBetweenBishopMovement(bool upleft, bool upright, bool downleft, bool downright, unsigned char toRow, unsigned char toCol, const Board& b) const{
    //checks all four path directions
    if(upleft)
    {
        for (int i = row + 1, j = col - 1; i < toRow; i++, j--)
        {            
            if (b.getBoard(i, j) != nullptr) {return false;}
        }
    } 
    else if (upright) 
    {
        for (int i = row + 1, j = col + 1; i < toRow; i++, j++)
        {
            if ((b.getBoard(i, j) != nullptr)) {return false;}
        }
    }
    else if (downleft) 
    {
        for (int i = row - 1, j = col - 1; i > toRow; i--, j--)
        {
            if (b.getBoard(i, j) != nullptr) {return false;}
        }
    }
    else if (downright)
    {
        for (int i = row - 1, j = col + 1; i > toRow; i--, j++)
        {
            if (b.getBoard(i, j) != nullptr) {return false;}
        }
    }

    return true;
}



