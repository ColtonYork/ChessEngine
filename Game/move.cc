#include "move.h"
#include <iostream>



Move::Move(bool whiteToPlay){
    whiteTurn = whiteToPlay;
}

void Move::makeMove(Board* b,const std::string& move){
    if (!correctMoveFormat(move)) {std::cout << "Incorect Move Format\n"; return;}
}

bool Move::correctMoveFormat(const std::string& move) const{

    if (move == "0-0" || move == "0-0-0") {return true;}
    if (move.length() != 5) {return false;}

    std::string checkMove = lowerToUpperString(move);

    //Checks for first letter indicating piece type
    if (checkMove.at(0) != 'P' && checkMove.at(0) != 'K' && checkMove.at(0) != 'B' && checkMove.at(0) != 'R' && checkMove.at(0) != 'Q' && checkMove.at(0) != 'N') {return false;}

    //check that letters are valid indexes
    if (checkMove.at(1) != 'A' && checkMove.at(1) != 'B' && checkMove.at(1) != 'C' && checkMove.at(1) != 'D' && checkMove.at(1) != 'E' && checkMove.at(1) != 'F' && checkMove.at(1) != 'G' && checkMove.at(1) != 'H') {return false;}
    if (checkMove.at(3) != 'A' && checkMove.at(3) != 'B' && checkMove.at(3) != 'C' && checkMove.at(3) != 'D' && checkMove.at(3) != 'E' && checkMove.at(3) != 'F' && checkMove.at(3) != 'G' && checkMove.at(3) != 'H') {return false;}

    //check that numbers are valid indexes
    if (checkMove.at(2) != '1' && checkMove.at(2) != '2' && checkMove.at(2) != '3' && checkMove.at(2) != '4' && checkMove.at(2) != '5' && checkMove.at(2) != '6' && checkMove.at(2) != '7' && checkMove.at(2) != '8') {return false;}
    if (checkMove.at(4) != '1' && checkMove.at(4) != '2' && checkMove.at(4) != '3' && checkMove.at(4) != '4' && checkMove.at(4) != '5' && checkMove.at(4) != '6' && checkMove.at(4) != '7' && checkMove.at(4) != '8') {return false;}

    return true;

}

std::string Move::lowerToUpperString(const std::string& s) const{

    std::string returnString = "";

    for(size_t i = 0; i < s.length(); i ++)
        {
            returnString += toupper(s.at(i));
        }
    
    return returnString;
}

void Move::makeCastleMove(Board* b, std::string move){
    if (move != "0-0" && move != "0-0-0") {return;}

        {
            Piece* piece = b->findKing(whiteTurn);
            if (!piece->isLegalCastleMove(true, *b)) {std::cout << "Illegal castle move" << '\n'; return;}
            
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

void Move::undoCastleMove(Board* b){
    //undo kingside castle
    if (b->getBoard())
}





