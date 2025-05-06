#include "Board.h"
#include "Piece.h"
#include "Rook.h"
#include "King.h"
#include "Knight.h"
#include "Queen.h"
#include "Pawn.h"
#include "Bishop.h"
#include <iostream>


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
        board[6][i] = new Pawn(1, i, false);
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
            if (p == nullptr){std::cout << ". ";}

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
                if (p->getPieceType() == PAWN){std::cout << "P ";}
                else if (p->getPieceType() == BISHOP){std::cout << "b ";}
                else if (p->getPieceType() == KNIGHT){std::cout << "n ";}
                else if (p->getPieceType() == ROOK){std::cout << "r ";}
                else if (p->getPieceType() == QUEEN){std::cout << "q ";}
                else if (p->getPieceType() == KING){std::cout << "k ";}
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

bool Board::squareUnderAtatck(unsigned char checkRow, unsigned char checkCol, bool byWhite, Board& b) const{
    //check if square is being attacked by one of whites pieces
    if (byWhite)
    {
        for (int i = 0; i < 8; i ++)
        {
            for (int j = 0; j < 8; j++)
            {
                Piece* piece = b.getBoard(i, j);
                if (piece == nullptr) {continue;}
                if (!piece->getIsWhite()) {continue;}

                if (piece->isLegalMove(checkRow, checkCol, b)) {return true;}
            }
        }
        return false;
    }
    
    //checks if square is being attacked by one of blacks pieces
    for (int i = 0; i < 8; i ++)
        {
            for (int j = 0; j < 8; j++)
            {
                Piece* piece = b.getBoard(i, j);
                if (piece == nullptr) {continue;}
                if (piece->getIsWhite()) {continue;}

                if (piece->isLegalMove(checkRow, checkCol, b)) {return true;}
            }
        }
        return false;
   
}

