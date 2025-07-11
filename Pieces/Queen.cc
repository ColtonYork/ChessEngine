#include "Queen.h"
#include "../Game/Board.h"
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

    //Check which Rook directions are blocked
    bool up = endSpotLegal(row + 1, col, *b);
    bool down = endSpotLegal(row - 1, col, *b);
    bool left = endSpotLegal(row, col - 1, *b);
    bool right = endSpotLegal(row, col + 1, *b);

    return existsPossibleMove(b, upRight, upLeft, downRight, downLeft, up, down, left, right);

    
}

int Queen::getPieceValue() const{
    return 9;
}

bool Queen::existsPossibleMoveBishopMovement(Board* b, bool upright, bool upleft, bool downright, bool downleft){
    //check bishop movement first
        if (upright)
        {
        for (int i = row + 1, j = col + 1; i < 8 && j < 8; i++, j++)
            {
                bool takePiece = false;

                //break when path gets cut off by own piece
                if (b->getBoard(i, j) != nullptr && getIsWhite() == (b->getBoard(i, j)->getIsWhite())) {break;}
                if (b->getBoard(i, j) != nullptr && getIsWhite() != (b->getBoard(i, j)->getIsWhite())) {takePiece = true;}


                if (isLegalMove(i, j, *b) && !b->moveCausesSelfCheck(row, col, i, j)) {std::cout << "Bishop can move to: " << i << ", " << j << '\n'; return true;}

                if (takePiece) {break;}
            }
        }

    if (upleft)
        {
        for (int i = row + 1, j = col - 1; i < 8 && j >= 0; i++, j--)
            {
                bool takePiece = false;

                //break when path gets cut off by own piece
                if (b->getBoard(i, j) != nullptr && getIsWhite() == (b->getBoard(i, j)->getIsWhite())) {break;}
                if (b->getBoard(i, j) != nullptr && getIsWhite() != (b->getBoard(i, j)->getIsWhite())) {takePiece = true;}


                if (isLegalMove(i, j, *b) && !b->moveCausesSelfCheck(row, col, i, j)) {std::cout << "Bishop can move to: " << i << ", " << j << '\n'; return true;}

                if (takePiece) {break;}
            }
        }

    if (downright)
        {
        for (int i = row - 1, j = col + 1; i >= 0 && j < 8; i--, j++)
            {
                bool takePiece = false;
                //break when path gets cut off by own piece
                if (b->getBoard(i, j) != nullptr && getIsWhite() == (b->getBoard(i, j)->getIsWhite())) {break;}
                if (b->getBoard(i, j) != nullptr && getIsWhite() != (b->getBoard(i, j)->getIsWhite())) {takePiece = true;}


                if (isLegalMove(i, j, *b) && !b->moveCausesSelfCheck(row, col, i, j)) {std::cout << "Bishop can move to: " << i << ", " << j << '\n'; return true;}

                if (takePiece) {break;}
            }
        }

    if (downleft)
        {
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
            {
                bool takePiece = false;
                //break when path gets cut off by own piece
                if (b->getBoard(i, j) != nullptr && getIsWhite() == (b->getBoard(i, j)->getIsWhite())) {break;}
                if (b->getBoard(i, j) != nullptr && getIsWhite() != (b->getBoard(i, j)->getIsWhite())) {takePiece = true;}


                if (isLegalMove(i, j, *b) && !b->moveCausesSelfCheck(row, col, i, j)) {std::cout << "Bishop can move to: " << i << ", " << j << '\n'; return true;}

                if (takePiece) {break;}
            }
        }

        return false;


}

bool Queen::existsPossibleMoveRookMovement(Board* b, bool up, bool down, bool left, bool right){
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

bool Queen::existsPossibleMove(Board* b, bool upright, bool upleft, bool downright, bool downleft, bool up, bool down, bool left, bool right){
    if (existsPossibleMoveBishopMovement(b, upright, upleft, downright, downleft) || existsPossibleMoveRookMovement(b, up, down, left, right)) {return true;}

    return false;
}

void Queen::computePossibleMoves(Board* b, std::priority_queue<moveStringAndScore>& q){
    //get possible bishop starting directions
    bool upRight = endSpotLegal(row + 1, col + 1, *b);
    bool upLeft = endSpotLegal(row + 1, col - 1, *b);
    bool downRight = endSpotLegal(row - 1, col + 1, *b);
    bool downLeft = endSpotLegal(row - 1, col - 1, *b);

    //get possible rook starting directions
    bool up = endSpotLegal(row + 1, col, *b);
    bool down = endSpotLegal(row - 1, col, *b);
    bool left = endSpotLegal(row, col - 1, *b);
    bool right = endSpotLegal(row, col + 1, *b);
    
    std::string startingMove = "q" + getFirstSquareOfMoveString();
    std::string fullMove = startingMove;
    
            
    
            //BISHOP MOVEMENT//
        if (upRight)
            {
                for (int i = row + 1, j = col + 1; i < 8 && j < 8; i++, j++)
                    {
                        bool takePiece = false;

                        //break when path gets cut off by own piece
                        if (b->getBoard(i, j) != nullptr && getIsWhite() == (b->getBoard(i, j)->getIsWhite())) {break;}
                        if (b->getBoard(i, j) != nullptr && getIsWhite() != (b->getBoard(i, j)->getIsWhite())) {takePiece = true;}


                        if (isLegalMove(i, j, *b) && !b->moveCausesSelfCheck(row, col, i, j))
                            {
                                moveStringAndScore moveResult;
                                moveResult.move = fullMove + getLastPartOfMoveString(i, j);
                                
                                if (takePiece)
                                    {
                                        int quickScoreValue = b->getBoard(i, j)->getPieceValue() - 9;
                                        if (quickScoreValue > 0) {moveResult.moveQuickScore = quickScoreValue;}
                                    }

                                q.push(moveResult);

                            }

                        if (takePiece) {break;}
                    }
            }

        if (upLeft)
            {
                for (int i = row + 1, j = col - 1; i < 8 && j >= 0; i++, j--)
                    {
                        bool takePiece = false;

                        //break when path gets cut off by own piece
                        if (b->getBoard(i, j) != nullptr && getIsWhite() == (b->getBoard(i, j)->getIsWhite())) {break;}
                        if (b->getBoard(i, j) != nullptr && getIsWhite() != (b->getBoard(i, j)->getIsWhite())) {takePiece = true;}


                        if (isLegalMove(i, j, *b) && !b->moveCausesSelfCheck(row, col, i, j))
                            {
                                moveStringAndScore moveResult;
                                moveResult.move = fullMove + getLastPartOfMoveString(i, j);

                                if (takePiece)
                                    {
                                        int quickScoreValue = b->getBoard(i, j)->getPieceValue() - 9;
                                        if (quickScoreValue > 0) {moveResult.moveQuickScore = quickScoreValue;}
                                    }

                                q.push(moveResult);

                            }

                        if (takePiece) {break;}
                    }
            }

        if (downRight)
            {
                for (int i = row - 1, j = col + 1; i >= 0 && j < 8; i--, j++)
                    {
                        bool takePiece = false;

                        //break when path gets cut off by own piece
                        if (b->getBoard(i, j) != nullptr && getIsWhite() == (b->getBoard(i, j)->getIsWhite())) {break;}
                        if (b->getBoard(i, j) != nullptr && getIsWhite() != (b->getBoard(i, j)->getIsWhite())) {takePiece = true;}


                        if (isLegalMove(i, j, *b) && !b->moveCausesSelfCheck(row, col, i, j))
                            {
                                moveStringAndScore moveResult;
                                moveResult.move = fullMove + getLastPartOfMoveString(i, j);

                                if (takePiece)
                                    {
                                        int quickScoreValue = b->getBoard(i, j)->getPieceValue() - 9;
                                        if (quickScoreValue > 0) {moveResult.moveQuickScore = quickScoreValue;}
                                    }

                                q.push(moveResult);

                            }

                        if (takePiece) {break;}
                    }
            }

        if (downLeft)
            {
                for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
                    {
                        bool takePiece = false;

                        //break when path gets cut off by own piece
                        if (b->getBoard(i, j) != nullptr && getIsWhite() == (b->getBoard(i, j)->getIsWhite())) {break;}
                        if (b->getBoard(i, j) != nullptr && getIsWhite() != (b->getBoard(i, j)->getIsWhite())) {takePiece = true;}


                        if (isLegalMove(i, j, *b) && !b->moveCausesSelfCheck(row, col, i, j))
                            {
                                moveStringAndScore moveResult;
                                moveResult.move = fullMove + getLastPartOfMoveString(i, j);
                                
                                if (takePiece)
                                    {
                                        int quickScoreValue = b->getBoard(i, j)->getPieceValue() - 9;
                                        if (quickScoreValue > 0) {moveResult.moveQuickScore = quickScoreValue;}
                                    }

                                q.push(moveResult);

                            }

                        if (takePiece) {break;}
                    }
            }

            //ROOK MOVEMENT//

        if (up)
            {
                for (int i = row + 1; i < 8; i++)
                    {
                        bool takesPiece = false;
                        //break when path gets cut off by own piece
                        if (b->getBoard(i, col) != nullptr && getIsWhite() == (b->getBoard(i, col)->getIsWhite())) {break;}
                        if (b->getBoard(i, col) != nullptr && getIsWhite() != (b->getBoard(i, col)->getIsWhite())) {takesPiece = true;}
    
    
                        if (isLegalMove(i, col, *b) && !b->moveCausesSelfCheck(row, col, i, col)) 
                            {
                                moveStringAndScore moveResult;
    
                                moveResult.move = fullMove + getLastPartOfMoveString(i, col);
    
                                if (takesPiece)
                                    {
                                        int quickScore = b->getBoard(i, col)->getPieceValue() - 9;
                                        moveResult.moveQuickScore = quickScore;
                                    }
    
                                q.push(moveResult);
    
                            }
    
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
    
    
                        if (isLegalMove(i, col, *b) && !b->moveCausesSelfCheck(row, col, i, col)) 
                            {
                                moveStringAndScore moveResult;
    
                                moveResult.move = fullMove + getLastPartOfMoveString(i, col);
    
                                if (takesPiece)
                                    {
                                        int quickScore = b->getBoard(i, col)->getPieceValue() - 9;
                                        moveResult.moveQuickScore = quickScore;
                                    }
    
                                q.push(moveResult);
    
                            }
    
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
    
    
                        if (isLegalMove(row, i, *b) && !b->moveCausesSelfCheck(row, col, row, i)) 
                            {
                                moveStringAndScore moveResult;
    
                                moveResult.move = fullMove + getLastPartOfMoveString(row, i);
    
                                if (takesPiece)
                                    {
                                        int quickScore = b->getBoard(row, i)->getPieceValue() - 9;
                                        moveResult.moveQuickScore = quickScore;
                                    }
    
                                q.push(moveResult);
    
                            }
    
                        if (takesPiece) {break;}
                    }
            }
    
        if (right)
            {
                for (int i = col + 1; i < 8; i++)
                    {
                        bool takesPiece = false;
    
                        //break when path gets cut off by own piece
                        if (b->getBoard(row, i) != nullptr && getIsWhite() == (b->getBoard(row, i)->getIsWhite())) {break;}
                        if (b->getBoard(row, i) != nullptr && getIsWhite() != (b->getBoard(row, i)->getIsWhite())) {takesPiece = true;}
    
    
                        if (isLegalMove(row, i, *b) && !b->moveCausesSelfCheck(row, col, row, i)) 
                            {
                                moveStringAndScore moveResult;
    
                                moveResult.move = fullMove + getLastPartOfMoveString(row, i);
    
                                if (takesPiece)
                                    {
                                        int quickScore = b->getBoard(row, i)->getPieceValue() - 9;
                                        moveResult.moveQuickScore = quickScore;
                                    }
    
                                q.push(moveResult);
    
                            }
    
                        if (takesPiece) {break;}
                    }
            }

}






