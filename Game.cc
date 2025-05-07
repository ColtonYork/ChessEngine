#include "Game.h"
#include "Piece.h"
#include "Board.h"
#include <string>
#include <iostream>



Game::Game(){
    movesPlayed = 0;
    whiteTurn = true;
}

void Game::makeMove(unsigned char fromRow, unsigned char fromCol, unsigned char toRow, unsigned char toCol){
    //get piece to move
    Piece* piece = board.getBoard(fromRow, fromCol);
    if (piece == nullptr) {return;}
    if (piece->getIsWhite() != whiteTurn) {return;}

    Board checkForSelfCheck = board;
    checkForSelfCheck.setSpace(toRow, toCol, piece);
    checkForSelfCheck.setSpace(fromRow, fromCol, nullptr);

    if(checkForSelfCheck.kingInCheck(whiteTurn)) {return;}





    whiteTurn = whiteTurn;

}

void Game::playGame(){
    
    board.displayBoard();

    std::string move;
    
    if(whiteTurn){std::cout << "Make a move, WHITE (format: re4e6): "; std::cin >> move;}
    else {"Make a move, BLACK (format: re4e6): "; std::cin >> move;}

    
}

int Game::letterToArrayIndex(char letter) const{
    char l = toupper(letter);
    if (l < 'A' || l > 'F') {return -1;}

    return l - 'A';
}

 
int Game::numberToArrayIndex(char number) const{
    if (number > '8' || number < '1') {return -1;};

    return number - '1';
}

