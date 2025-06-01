#include "Board.h"
#include "Piece.h"
#include "Rook.h"
#include "King.h"
#include "Knight.h"
#include "Queen.h"
#include "Pawn.h"
#include "Bishop.h"
#include <iostream>
#define BROWN "\033[33;2m"       // or "\033[33;1m" for a different shade
#define RESET "\033[0m"
#define DARK_GRAY "\033[90m"


Board::Board(){
    //sets whites pieces
    board[0][0] = new Rook(0, 0, true);
    board[0][1] = new Knight(0, 1, true);
    board[0][2] = new Bishop(0, 2, true);
    board[0][3] = new Queen(0, 3, true);
    board[0][4] = new King(0, 4, true);
    board[0][5] = new Bishop(0, 5, true);
    board[0][6] = new Knight(0, 6, true);
    board[0][7] = new Rook(0, 7, true);

    


    //set white pawns
    for(int i = 0; i < 8; i++){
        board[1][i] = new Pawn(1, i, true);
    }

    //sets blacks pieces
    board[7][7] = new Rook(7, 7, false);
    board[7][6] = new Knight(7, 6, false);
    board[7][5] = new Bishop(7, 5, false);
    board[7][4] = new King(7, 4, false);
    board[7][3] = new Queen(7, 3, false);
    board[7][2] = new Bishop(7, 2, false);
    board[7][1] = new Knight(7, 1, false);
    board[7][0] = new Rook(7, 0, false);

    //set black pawns
    for(int i = 0; i < 8; i++){
        board[6][i] = new Pawn(6, i, false);
    }

    //set empty spaces to nullptr
    for(int i = 2; i < 6; i++){
        for (int j = 0; j < 8; j++){
            board[i][j] = nullptr;
        }
    }
}

Board::Board(const Board& other){
    for (int i = 0; i < 8; i ++){
        for(int j = 0; j < 8; j++){
            if (other.board[i][j] == nullptr)
            {
                board[i][j] = nullptr;
            }
            else{
                board[i][j] = other.board[i][j]->clone();
            }
        }
    }
}

Board::~Board(){
    for (int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            delete board[i][j];
            board[i][j] = nullptr;
        }
    }
}

Board& Board::operator=(const Board& other){
    //self assignment
    if (this == &other){return *this;}

    //clear 2d array
    for (int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            delete board[i][j];
            board[i][j] = nullptr;
        }
    }

    //copy 2d array to caller
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if (other.board[i][j] == nullptr)
            {
                board[i][j] = nullptr;
            } else{
                board[i][j] = other.board[i][j]->clone();
            }
        }
    }

    return *this;
}

void Board::displayBoard() const{
    //line 1
    for (int i = 7; i >= 0; i--){
        std::cout << i+1 << " | ";
        for(int j = 0; j < 8; j++){
            Piece* p = board[i][j];

            //checks for empty spot
            if (p == nullptr)
                {
                    if ((i + j) % 2 == 0) {std::cout << BROWN << ". " << RESET;}
                    else{std::cout << ". " << RESET;}
                }

            //checks for white pieces
            else if (p->getIsWhite() == 1){
                if (p->getPieceType() == PAWN){std::cout << "P ";}
                else if (p->getPieceType() == BISHOP){std::cout << "B ";}
                else if (p->getPieceType() == KNIGHT){std::cout << "N ";}
                else if (p->getPieceType() == ROOK){std::cout << "R ";}
                else if (p->getPieceType() == QUEEN){std::cout << "Q ";}
                else if (p->getPieceType() == KING){std::cout << "K ";}
            }
            
            //checks for black pieces
            else{
                if (p->getPieceType() == PAWN){std::cout << DARK_GRAY << "p " << RESET;}
                else if (p->getPieceType() == BISHOP){std::cout << DARK_GRAY << "B " << RESET;}
                else if (p->getPieceType() == KNIGHT){std::cout << DARK_GRAY << "N " << RESET;}
                else if (p->getPieceType() == ROOK){std::cout << DARK_GRAY << "R " << RESET;}
                else if (p->getPieceType() == QUEEN){std::cout << DARK_GRAY << "Q " << RESET;}
                else if (p->getPieceType() == KING){std::cout << DARK_GRAY << "K " << RESET;}
            }

            if(j == 7){std::cout << '\n';}
            

        }

    }

    std::cout << "  ------------------" << '\n';
    std::cout << "    A B C D E F G H" << '\n';



}

Piece* Board::getBoard(unsigned char row, unsigned char col) const{
    return board[row][col];
}

bool Board::squareUnderAttack(unsigned char checkRow, unsigned char checkCol, bool byWhite) const{
    //check if square is being attacked by one of whites pieces
    if (byWhite)
    {
        for (int i = 0; i < 8; i ++)
        {
            for (int j = 0; j < 8; j++)
            {
                Piece* piece = getBoard(i, j);
                if (piece == nullptr) {continue;}
                if (!piece->getIsWhite()) {continue;}

                if (piece->isLegalMove(checkRow, checkCol, *this)) {std::cout << "Square is under attack by Piece:" << " at " << static_cast<int>(piece->getRow()) << " " << static_cast<int>(piece->getCol()) << '\n'; return true;}
            }
        }
        return false;
    }
    
    //checks if square is being attacked by one of blacks pieces
    for (int i = 0; i < 8; i ++)
        {
            for (int j = 0; j < 8; j++)
            {
                Piece* piece = getBoard(i, j);
                if (piece == nullptr) {continue;}
                if (piece->getIsWhite()) {continue;}

                if (piece->isLegalMove(checkRow, checkCol, *this)) {std::cout << "Square is under attack by Piece:" << " at " << static_cast<int>(piece->getRow()) << " " << static_cast<int>(piece->getCol()) << '\n'; return true;}
            }
        }
        return false;
   
}

bool Board::kingInCheck(bool white) const{
    Piece* king = findKing(white);
    
    if (king == nullptr) {std::cout << "King not found" << '\n'; return false;}
    std::cout << "King found" << static_cast<int>(king->getRow()) << " " << static_cast<int>(king->getCol()) << '\n';

    //Whites king's coordinates are found, check if any enenmy pieces can target that square
    if (squareUnderAttack(king->getRow(), king->getCol(), !white)) {std::cout << "King is in check by: " << '\n'; return true;}
    std::cout << "King is not in check" << '\n';
    return false;   
}

Piece* Board::findKing(bool whiteKing) const{
    for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
                {
                    Piece* piece = getBoard(i, j);
                    if (piece == nullptr) {continue;}

                    // A king found
                    else if (piece->getPieceType() == KING && piece->getIsWhite() == whiteKing) {return piece;}
                   
                }
        }
    // This case should never happen
    return nullptr;
}

void Board::setSpace(unsigned char row, unsigned char col, Piece* piece){
    delete board[row][col];
    board[row][col] = piece;
}

bool Board::playerHasLegalMoveByDeletion(bool white){
    //loop thru white pieces
    for(int i = 0; i < 8; i ++)
        {
            for(int j = 0; j < 8; j++)
                {
                    Piece* piece = getBoard(i, j);

                    //make sure piece is correct color and make sure it has a legal move around it
                    if (piece == nullptr || piece->getIsWhite() != white || !piece->hasOneSpaceLegalMove(this)) {continue;}
                    
                    Piece* pieceCopy = piece->clone();

                    setSpace(i, j, nullptr);
                    if (kingInCheck(white)) {setSpace(i, j, pieceCopy); continue;}

                    setSpace(i, j, pieceCopy); 
                    return 1;   
                }
        }
        return 0;
}

bool Board::playerHasLegalMoveAfterDeletion(bool white){
    
}










