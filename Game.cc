#include "Game.h"
#include "Piece.h"
#include "Board.h"
#include <string>
#include <iostream>



Game::Game(){
    movesPlayed = 0;
    whiteTurn = true;
    board = new Board();
}

bool Game::makeMove(std::string move){
    Board* copy = verifyMove(move);

    //check if move is valid
    if(copy == nullptr) {return false;}



    delete board;
    whiteTurn = !whiteTurn;
    movesPlayed++;
    board = copy;
    return 1;
    
}

void Game::playGame(){
    
    board->displayBoard();
    while(true)
        {
            //while !isGameOver needs implemented
            while(true)
                {
                    std::string move = getUserMove();
                    if (!makeMove(move)) {std:: cout << "Illegal move" << '\n'; continue;}

                    board->displayBoard();

                }


        } 
}

int Game::letterToArrayIndex(char letter) const{
    char l = toupper(letter);
    if (l < 'A' || l > 'H') {return -1;}

    return l - 'A';
}
 
int Game::numberToArrayIndex(char number) const{
    if (number > '8' || number < '1') {return -1;};

    return number - '1';
}

std::string Game::getUserMove() const{
    std::string move;

    while (true)
    {
        if(whiteTurn){std::cout << "Make a move, WHITE (format: re4e6): "; std::cin >> move;}
        else {std::cout << "Make a move, BLACK (format: re4e6): "; std::cin >> move;}

        if(!correctUserMoveFormat(move)) {std::cout << "Illegal move format" << '\n'; continue;}
        else
            {
                break;
            }
        
    }
    return move;
}


bool Game::correctUserMoveFormat(std::string move) const{
    if (move == "0-0" || move == "0-0-0") {return true;}
    if (move.length() != 5) {return false;}

    std::string checkMove = lowerToUpperString(move);

    //Checks for first letter indicating piece type
    if (checkMove.at(0) != 'P' && checkMove.at(0) != 'K' && checkMove.at(0) != 'B' && checkMove.at(0) != 'R' && checkMove.at(0) != 'Q' && checkMove.at(0) != 'N') {return false;}

    //check that letters are valid indexes
    if (checkMove.at(1) != 'A' && checkMove.at(1) != 'B' && checkMove.at(1) != 'C' && checkMove.at(1) != 'D' && checkMove.at(1) != 'E' && checkMove.at(1) != 'F' && checkMove.at(1) != 'G' && checkMove.at(1) != 'H') {return false;}
    if (checkMove.at(3) != 'A' && checkMove.at(3) != 'B' && checkMove.at(3) != 'C' && checkMove.at(3) != 'D' && checkMove.at(3) != 'E' && checkMove.at(3) != 'F' && checkMove.at(3) != 'G' && checkMove.at(3) != 'H') {return false;}

    //check that numbers are valid indexes
    if(checkMove.at(2) != '1' && checkMove.at(2) != '2' && checkMove.at(2) != '3' && checkMove.at(2) != '4' && checkMove.at(2) != '5' && checkMove.at(2) != '6' && checkMove.at(2) != '7' && checkMove.at(2) != '8') {return false;}
    if(checkMove.at(4) != '1' && checkMove.at(4) != '2' && checkMove.at(4) != '3' && checkMove.at(4) != '4' && checkMove.at(4) != '5' && checkMove.at(4) != '6' && checkMove.at(4) != '7' && checkMove.at(4) != '8') {return false;}

    return true;
}

std::string Game::lowerToUpperString(std::string s) const{
    std::string returnString = "";

    for(size_t i = 0; i < s.length(); i ++)
        {
            returnString += toupper(s.at(i));
        }
    
    return returnString;
}

Piece* Game::getPieceFromMoveString(std::string move) const{
    int fromRow, fromCol;

    //get from 
    fromCol = letterToArrayIndex(move.at(1));
    fromRow = numberToArrayIndex(move.at(2));

    return board->getBoard(fromRow, fromCol);
}

bool Game::isMoversPiece(Piece* piece) const{
    if (piece == nullptr) {return false;}
    if (piece->getIsWhite() != whiteTurn) { std::cout << "This is not your piece" << '\n'; return false;}
    return true;
}

Board* Game::verifyMove(std::string move) const{
    //check for castle moves
    if(move == "0-0" || move == "0-0-0") {return verifyCastleMove(move);}

    //validate move format
    if (!correctUserMoveFormat(move)) {std::cout << "Incorrect Move Format" << '\n'; return nullptr;}

    //get piece on current board and determine if the mover owns it
    Piece* originalPiece = getPieceFromMoveString(move);
    if (!isMoversPiece(originalPiece)) {return nullptr;}

    int fromRow, fromCol, toRow, toCol;
    fromRow = originalPiece->getRow();
    fromCol = originalPiece->getCol();
    toCol = letterToArrayIndex(move.at(3));
    toRow = numberToArrayIndex(move.at(4));

    if (!originalPiece->isLegalMove(toRow, toCol, *board)) {std::cout << "isLegalMove Fail" << '\n'; return nullptr;}

    //make board copy and piece copy if the move is legal so far
    Board* copy = new Board(*board);
    Piece* copyPiece = originalPiece->clone();

    //make move on copy board
    copy->setSpace(fromRow, fromCol, nullptr);
    copyPiece->setCol(toCol);
    copyPiece->setRow(toRow);
    copy->setSpace(toRow, toCol, copyPiece);


    //check if the move puts yourself in check
    if(copy->kingInCheck(whiteTurn)) {delete copy; std::cout << "Self Check Illegal" << '\n'; return nullptr;}

    std::cout << "Piece move from: " << static_cast<int>(originalPiece->getRow()) <<" " << static_cast<int>(originalPiece->getCol()) << " TO: " << static_cast<int>(copyPiece->getRow()) << " " << static_cast<int>(copyPiece->getCol()) << '\n';
 
    return copy;
}

Board* Game::verifyCastleMove(std::string move) const{
    //check king side castle
    if (move == "0-0")  
        {
            Piece* piece = board->findKing(whiteTurn);
            if (!piece->isLegalCastleMove(true, *board)) {std::cout << "Illegal caslt move" << '\n'; return nullptr;}
            
            //make board copy and piece copy
            Board* copy = new Board(*board);
            Piece* rook = board->getBoard(piece->getRow(), piece->getCol() + 3)->clone();
            Piece* king = piece->clone();

            copy->setSpace(piece->getRow(), 4, nullptr);
            copy->setSpace(piece->getRow(), 7, nullptr);
            copy->setSpace(piece->getRow(), 5, king);
            copy->setSpace(piece->getRow(), 6, rook);

            return copy;



        }
    //check queen side castle
    else if (move == "0-0-0")    
        {
            Piece* piece = board->findKing(whiteTurn);
            if (!piece->isLegalCastleMove(false, *board)) {std::cout << "Illegal caslt move" << '\n'; return nullptr;}

            //make board copy and piece copy
            Board* copy = new Board(*board);
            Piece* rook = board->getBoard(piece->getRow(), piece->getCol() - 4)->clone();
            Piece* king = piece->clone();

            copy->setSpace(piece->getRow(), 4, nullptr);
            copy->setSpace(piece->getRow(), 0, nullptr);
            copy->setSpace(piece->getRow(), 3, king);
            copy->setSpace(piece->getRow(), 2, rook);

            return copy;
        }
        return nullptr;
}








