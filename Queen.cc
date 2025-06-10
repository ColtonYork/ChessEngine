#include "Queen.h"
#include "Board.h"
#include <cmath>
#include <iostream>

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

bool Queen::endSpotLegal(unsigned char checkRow, unsigned char checkColumn, const Board& b) const{
    //check inboubnds
    if (checkRow > 7 || checkRow < 0 || checkColumn > 7 || checkColumn < 0) {return 0;}

    Piece* piece = b.getBoard(checkRow, checkColumn);

    if (piece == nullptr) {return true;}
    else if (isWhite == piece->getIsWhite()) {return false;}
    
    return true;
}

bool Queen::hasOneSpaceLegalMove(const Board* b) const{
    if (endSpotLegal(row+1, col, *b) || endSpotLegal(row-1, col, *b) || endSpotLegal(row, col-1, *b) || endSpotLegal(row, col+1, *b) 
    || endSpotLegal(row+1, col+1, *b) || endSpotLegal(row-1, col-1, *b) || endSpotLegal(row+1, col-1, *b) || endSpotLegal(row-1, col+1, *b)) {return true;}
    
    return false;
}

bool Queen::hasVerifiedMove(Board* b){
    //check which Bishop directions are blocked
    bool upRight = endSpotLegal(row + 1, col + 1, *b);
    bool upLeft = endSpotLegal(row + 1, col - 1, *b);
    bool downRight = endSpotLegal(row - 1, col + 1, *b);
    bool downLeft = endSpotLegal(row - 1, col - 1, *b);

    if (upRight)
        {
        for (int i = row + 1, j = col + 1; i < 8 && j < 8; i++, j++)
            {
                //break when path gets cut off by own piece
                if (getIsWhite() == (b->getBoard(i, j)->getIsWhite())) {break;}

                if (isLegalMove(i, j, *b) && !b->moveCausesSelfCheck(row, col, i, j)) {std::cout << "Bishop can move to: " << i << ", " << j << '\n'; return true;}
            }
        }

    if (upLeft)
        {
        for (int i = row + 1, j = col - 1; i < 8 && j >= 0; i++, j--)
            {
                //break when path gets cut off by own piece
                if (getIsWhite() == (b->getBoard(i, j)->getIsWhite())) {break;}

                if (isLegalMove(i, j, *b) && !b->moveCausesSelfCheck(row, col, i, j)) {std::cout << "Bishop can move to: " << i << ", " << j << '\n'; return true;}
            }
        }

    if (downRight)
        {
        for (int i = row - 1, j = col + 1; i >= 0 && j < 8; i--, j++)
            {
                //break when path gets cut off by own piece
                if (getIsWhite() == (b->getBoard(i, j)->getIsWhite())) {break;}

                if (isLegalMove(i, j, *b) && !b->moveCausesSelfCheck(row, col, i, j)) {std::cout << "Bishop can move to: " << i << ", " << j << '\n'; return true;}
            }
        }

    if (downLeft)
        {
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
            {
                //break when path gets cut off by own piece
                if (getIsWhite() == (b->getBoard(i, j)->getIsWhite())) {break;}

                if (isLegalMove(i, j, *b) && !b->moveCausesSelfCheck(row, col, i, j)) {std::cout << "Bishop can move to: " << i << ", " << j << '\n'; return true;}
            }
        }

    //Check which Rook directions are blocked
    bool up = endSpotLegal(row + 1, col, *b);
    bool down = endSpotLegal(row - 1, col, *b);
    bool left = endSpotLegal(row, col - 1, *b);
    bool right = endSpotLegal(row, col + 1, *b);

    if (up)
        {
        for (int i = row + 1; i < 8; i++)
            {
                //break when path gets cut off by own piece
                if (getIsWhite() == (b->getBoard(i, col)->getIsWhite())) {break;}

                if (isLegalMove(i, col, *b) && !b->moveCausesSelfCheck(row, col, i, col)) {std::cout << "Rook can move to: " << i << ", " << col << '\n'; return true;}
            }
        }

    if (down)
        {
        for (int i = row - 1; i >= 0; i--)
            {
                //break when path gets cut off by own piece
                if (getIsWhite() == (b->getBoard(i, col)->getIsWhite())) {break;}

                if (isLegalMove(i, col, *b) && !b->moveCausesSelfCheck(row, col, i, col)) {std::cout << "Rook can move to: " << i << ", " << col << '\n'; return true;}
            }
        }

    if (left)
        {
        for (int i = col - 1; i >= 0; i--)
            {
                //break when path gets cut off by own piece
                if (getIsWhite() == (b->getBoard(i, col)->getIsWhite())) {break;}

                if (isLegalMove(row, i, *b) && !b->moveCausesSelfCheck(row, col, row, i)) {std::cout << "Rook can move to: " << row << ", " << i << '\n'; return true;}
            }
        }
        
    if (right)
        {
        for (int i = col + 1; i < 8; i++)
            {
                //break when path gets cut off by own piece
                if (getIsWhite() == (b->getBoard(i, col)->getIsWhite())) {break;}

                if (isLegalMove(row, i, *b) && !b->moveCausesSelfCheck(row, col, row, i)) {std::cout << "Rook can move to: " << row << ", " << i << '\n'; return true;}
            }
        }

        return false;



}




