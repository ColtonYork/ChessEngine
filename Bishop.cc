#include "Bishop.h"
#include "Board.h"
#include <cmath>
Bishop::Bishop(unsigned char r, unsigned char c, bool isW)
    : Piece(r, c, isW){}

Piece* Bishop::clone() const{
    return new Bishop(row, col, isWhite);
}

pieceType Bishop::getPieceType() const{
    return BISHOP;
}

bool Bishop::isLegalMove(unsigned char toRow, unsigned char toCol, const Board& b) const{
    //checks if move is inbounds
    if (!moveIsInbounds(toRow, toCol)) {return false;}    

    //Check bishop move legality
    int rowChange = abs(row - toRow);
    int colChange = abs(col - toCol);

    if(rowChange != colChange) {return false;}

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
    if (!isLegalBetween(upLeft, upRight, downLeft, downRight, toRow, toCol, b)) {return false;}

    //Check endspot
    if (!endSpotLegal(toRow, toCol, b)) {return false;}

    return true;
}

bool Bishop::isLegalBetween(bool upleft, bool upright, bool downleft, bool downright, unsigned char toRow, unsigned char toCol, const Board& b) const {
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





