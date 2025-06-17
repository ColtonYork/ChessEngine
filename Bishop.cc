#include "Bishop.h"
#include "Board.h"
#include <cmath>
#include <iostream>

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

bool Bishop::endSpotLegal(unsigned char checkRow, unsigned char checkColumn, const Board& b) const{
    //check inboubnds
    if (checkRow > 7 || checkRow < 0 || checkColumn > 7 || checkColumn < 0) {return 0;}

    Piece* piece = b.getBoard(checkRow, checkColumn);

    if (piece == nullptr) {return true;}
    else if (isWhite == piece->getIsWhite()) {return false;}
    
    return true;
}

bool Bishop::hasOneSpaceLegalMove(const Board* b) const{
    //see if there is a legal 1-space move
    if (endSpotLegal(row+1, col+1, *b) || endSpotLegal(row-1, col-1, *b) || endSpotLegal(row+1, col-1, *b) || endSpotLegal(row-1, col+1, *b)) {return true;}
    return false;
}

bool Bishop::hasVerifiedMove(Board* b) {
    //check which direction are blocked
    bool upRight = endSpotLegal(row + 1, col + 1, *b);
    bool upLeft = endSpotLegal(row + 1, col - 1, *b);
    bool downRight = endSpotLegal(row - 1, col + 1, *b);
    bool downLeft = endSpotLegal(row - 1, col - 1, *b);

  
    if (upRight)
        {
        for (int i = row + 1, j = col + 1; i < 8 && j < 8; i++, j++)
            {
                //break when path gets cut off by own piece
                if (b->getBoard(i, j) != nullptr && getIsWhite() == (b->getBoard(i, j)->getIsWhite())) {break;}

                if (isLegalMove(i, j, *b) && !b->moveCausesSelfCheck(row, col, i, j)) {std::cout << "Bishop can move to: " << i << ", " << j << '\n'; return true;}
            }
        }

    if (upLeft)
        {
        for (int i = row + 1, j = col - 1; i < 8 && j >= 0; i++, j--)
            {
                //break when path gets cut off by own piece
                if (b->getBoard(i, j) != nullptr && getIsWhite() == (b->getBoard(i, j)->getIsWhite())) {break;}

                if (isLegalMove(i, j, *b) && !b->moveCausesSelfCheck(row, col, i, j)) {std::cout << "Bishop can move to: " << i << ", " << j << '\n'; return true;}
            }
        }

    if (downRight)
        {
        for (int i = row - 1, j = col + 1; i >= 0 && j < 8; i--, j++)
            {
                //break when path gets cut off by own piece
                if (b->getBoard(i, j) != nullptr && getIsWhite() == (b->getBoard(i, j)->getIsWhite())) {break;}

                if (isLegalMove(i, j, *b) && !b->moveCausesSelfCheck(row, col, i, j)) {std::cout << "Bishop can move to: " << i << ", " << j << '\n'; return true;}
            }
        }

    if (downLeft)
        {
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
            {
                //break when path gets cut off by own piece
                
                if (b->getBoard(i, j) != nullptr && getIsWhite() == (b->getBoard(i, j)->getIsWhite())) {break;}

                if (isLegalMove(i, j, *b) && !b->moveCausesSelfCheck(row, col, i, j)) {std::cout << "Bishop can move to: " << i << ", " << j << '\n'; return true;}
            }
        }

        return false;

}



