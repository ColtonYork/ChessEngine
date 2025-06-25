#include "move.h"
#include "../Pieces/Pawn.h"
#include "../Pieces/Piece.h"
#include <iostream>



MoveMaker::MoveMaker(bool whiteToPlay){
    whiteTurn = whiteToPlay;
}

void MoveMaker::makeMove(Board* b,const std::string& move){
    if (!correctMoveFormat(move)) {std::cout << "Incorect Move Format\n"; return;}
}

bool MoveMaker::correctMoveFormat(const std::string& move) const{

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

std::string MoveMaker::lowerToUpperString(const std::string& s) const{

    std::string returnString = "";

    for(size_t i = 0; i < s.length(); i ++)
        {
            returnString += toupper(s.at(i));
        }
    
    return returnString;
}

void MoveMaker::makeCastleMove(Board* b, std::string move){
    if (move != "0-0" && move != "0-0-0") {std::cout << "[0][DEBUG][moveMaker::makeCastleMove]\n"; return;}

    if (whiteTurn)
        {
            Piece* king = b->getBoard(0, 4);
            if(king == nullptr || king->getPieceType() != KING) {std::cout << "[1][DEBUG][moveMaker::makeCastleMove]\n"; return;}

            //white kingside castle
            if (move == "0-0")
                {
                    if (!king->isLegalCastleMove(true, *b)){std::cout << "[2][DEBUG][moveMaker::makeCastleMove]\n"; return;}

                    Piece* rook = b->getBoard(0, 7);
                    b->setSpaceWithoutDeleting(0, 7, nullptr);
                    b->setSpaceWithoutDeleting(0, 6, king);
                    b->setSpaceWithoutDeleting(0, 5, rook);
                    rook->setCol(5);
                    king->setCol(6);
                    rook->setHasMoved(true);
                    king->setHasMoved(true);

                    undoMoveInfo info;
                    info.whiteMove = 1;
                    info.kingsideCastleMove = 1;

                    previousPositions.push(info);
                    return;
                }
            //white queenside castle
            else
                {
                    if (!king->isLegalCastleMove(false, *b)){std::cout << "[3][DEBUG][moveMaker::makeCastleMove]\n"; return;}

                    Piece* rook = b->getBoard(0, 0);
                    b->setSpaceWithoutDeleting(0, 0, nullptr);
                    b->setSpaceWithoutDeleting(0, 2, king);
                    b->setSpaceWithoutDeleting(0, 3, rook);
                    rook->setCol(3);
                    king->setCol(2);
                    rook->setHasMoved(true);
                    king->setHasMoved(true);

                    undoMoveInfo info;
                    info.whiteMove = 1;
                    info.queensideCastleMove = 1;

                    previousPositions.push(info);
                    return;
                }
        }

    //black logic now
    else
        {
            Piece* king = b->getBoard(7, 4);
            if(king == nullptr || king->getPieceType() != KING) {std::cout << "[4][DEBUG][moveMaker::makeCastleMove]\n"; return;}

            //black kingside castle
            if (move == "0-0")
                {
                    if (!king->isLegalCastleMove(true, *b)){std::cout << "[5][DEBUG][moveMaker::makeCastleMove]\n"; return;}

                    Piece* rook = b->getBoard(7, 7);
                    b->setSpaceWithoutDeleting(7, 7, nullptr);
                    b->setSpaceWithoutDeleting(7, 6, king);
                    b->setSpaceWithoutDeleting(7, 5, rook);
                    rook->setCol(5);
                    king->setCol(6);
                    rook->setHasMoved(true);
                    king->setHasMoved(true);

                    undoMoveInfo info;
                    info.whiteMove = 0;
                    info.kingsideCastleMove = 1;

                    previousPositions.push(info);
                    return;
                }
            //black queenside castle
            else
                {
                    if (!king->isLegalCastleMove(false, *b)){std::cout << "[6][DEBUG][moveMaker::makeCastleMove]\n"; return;}

                    Piece* rook = b->getBoard(7, 0);
                    b->setSpaceWithoutDeleting(7, 0, nullptr);
                    b->setSpaceWithoutDeleting(7, 2, king);
                    b->setSpaceWithoutDeleting(7, 3, rook);
                    rook->setCol(3);
                    king->setCol(2);
                    rook->setHasMoved(true);
                    king->setHasMoved(true);

                    undoMoveInfo info;
                    info.whiteMove = 0;
                    info.queensideCastleMove = 1;

                    previousPositions.push(info);
                    return;
                }
        }       
}

void MoveMaker::undoCastleMove(Board* b, undoMoveInfo& info){
    //white kingside
    Piece* king = b->getBoard(0, 2);
    if (king != nullptr && king->getPieceType() == KING && king->getIsWhite() == 1)
        {
            Piece* rook = b->getBoard(0, 3);
            b->setSpaceWithoutDeleting(0, 3, nullptr);
            b->setSpaceWithoutDeleting(0, 0, rook);
            b->setSpaceWithoutDeleting(0, 2, nullptr);
            b->setSpaceWithoutDeleting(0, 4, king);

            rook->setRow(0);
            rook->setCol(0);
            king->setRow(0);
            king->setCol(4);

            king->setHasMoved(false);
            rook->setHasMoved(false);

            return;
        }

    //white queenside
    king = b->getBoard(0, 6);
    if (king != nullptr && king->getPieceType() == KING && king->getIsWhite() == 1)
        {
            Piece* rook = b->getBoard(0, 5);
            b->setSpaceWithoutDeleting(0, 5, nullptr);
            b->setSpaceWithoutDeleting(0, 7, rook);
            b->setSpaceWithoutDeleting(0, 6, nullptr);
            b->setSpaceWithoutDeleting(0, 4, king);

            rook->setRow(0);
            rook->setCol(7);
            king->setRow(0);
            king->setCol(4);

            king->setHasMoved(false);
            rook->setHasMoved(false);

            return;
        }
    //black kingside
    king = b->getBoard(7, 2);
    if (king != nullptr && king->getPieceType() == KING && king->getIsWhite() == 0)
        {
            Piece* rook = b->getBoard(7, 3);
            b->setSpaceWithoutDeleting(7, 3, nullptr);
            b->setSpaceWithoutDeleting(7, 0, rook);
            b->setSpaceWithoutDeleting(7, 2, nullptr);
            b->setSpaceWithoutDeleting(7, 4, king);

            rook->setRow(7);
            rook->setCol(0);
            king->setRow(7);
            king->setCol(4);

            king->setHasMoved(false);
            rook->setHasMoved(false);
            
            return;
        }
    //black queenside
    king = b->getBoard(7, 6);
    if (king != nullptr && king->getPieceType() == KING && king->getIsWhite() == 0)
        {
            Piece* rook = b->getBoard(7, 5);
            b->setSpaceWithoutDeleting(7, 5, nullptr);
            b->setSpaceWithoutDeleting(7, 7, rook);
            b->setSpaceWithoutDeleting(7, 6, nullptr);
            b->setSpaceWithoutDeleting(7, 4, king);

            rook->setRow(7);
            rook->setCol(7);
            king->setRow(7);
            king->setCol(4);

            king->setHasMoved(false);
            rook->setHasMoved(false);

            return;
        }

    std::cout << "[1][DEBUG][MoveMaker::undoCastleMove]\n"; 
    return; 

}

void MoveMaker::undoCaptureMove(Board* b, undoMoveInfo& info){
    info.movedPiece->setRow(info.fromrow);
    info.movedPiece->setCol(info.fromcol);
    b->setSpaceWithoutDeleting(info.fromrow, info.fromcol, info.movedPiece);
    b->setSpaceWithoutDeleting(info.torow, info.tocol, info.capturedPiece);

    info.capturedPiece = nullptr;

}

void MoveMaker::undoRegularMove(Board* b, undoMoveInfo& info){
    info.movedPiece->setRow(info.fromrow);
    info.movedPiece->setCol(info.fromcol);
    b->setSpaceWithoutDeleting(info.fromrow, info.fromcol, info.movedPiece);
    b->setSpaceWithoutDeleting(info.torow, info.tocol, nullptr);
}

void MoveMaker::undoPromotionMove(Board* b, undoMoveInfo& info){
    Piece* capturedPiece = info.capturedPiece;
    Piece* replacementPawn = new Pawn(info.fromrow, info.fromcol, info.whiteMove);

    //to determine if we need to put a capotured piece back along with undoing promotion
    if (capturedPiece != nullptr)  
        {
            //this deletes the promoted piece and puts the captured piece back in the correct position
            b->setSpace(info.torow, info.tocol, info.capturedPiece);
            b->setSpaceWithoutDeleting(info.fromrow, info.fromcol, replacementPawn);
            info.capturedPiece = nullptr;
        }
    else 
        {
            b->setSpace(info.torow, info.tocol, nullptr);
            b->setSpaceWithoutDeleting(info.fromrow, info.fromcol, replacementPawn);
        }
}

void MoveMaker::makeCaptureMove(Board* b, std::string move){
    if (!correctMoveFormat(move)) {std::cout << "[0][DEBUG][MoveMaker::makeCaptureMove]\n"; return;}

    int fromrow, fromcol, torow, tocol;
    fromrow = letterToArrayIndex(move.at(1));
    torow = letterToArrayIndex(move.at(3));
    fromcol = numberToArrayIndex(move.at(2));
    tocol = numberToArrayIndex(move.at(4));

    Piece* movePiece = b->getBoard(fromrow, fromcol);

    if(!movePiece->isLegalMove(torow, tocol, *b)) {std::cout << "[1][DEBUG][MoveMaker::makeCaptureMove]\n"; return;}
    if(b->moveCausesSelfCheck(fromrow, fromcol, torow, tocol)) {std::cout << "[2][DEBUG][MoveMaker::makeCaptureMove]\n"; return;}

    Piece* capturePiece = b->getBoard(torow, tocol);

    //make move on board now
    b->setSpaceWithoutDeleting(fromrow, fromcol, nullptr);
    b->setSpaceWithoutDeleting(torow, tocol, movePiece);

    movePiece->setRow(torow);
    movePiece->setCol(tocol);

    //und0move information
    undoMoveInfo info;
    info.capturedPiece = capturePiece;
    info.movedPiece = movePiece;
    info.captureMove = 1;
    info.whiteMove = movePiece->getIsWhite();
    
    info.fromrow = fromrow;
    info.fromcol = fromcol;
    info.torow = torow;
    info.tocol = tocol;

    previousPositions.push(info);
}

Piece* MoveMaker::getPieceFromMoveString(const Board* b, const std::string& move) const{
    int fromRow, fromCol;

    //get from 
    fromCol = letterToArrayIndex(move.at(1));
    fromRow = numberToArrayIndex(move.at(2));

    return b->getBoard(fromRow, fromCol);
}

int MoveMaker::letterToArrayIndex(char letter) const{
    char l = toupper(letter);
    if (l < 'A' || l > 'H') {return -1;}

    return l - 'A';
}
 
int MoveMaker::numberToArrayIndex(char number) const{
    if (number > '8' || number < '1') {return -1;};

    return number - '1';
}







