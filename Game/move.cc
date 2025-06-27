#include "move.h"
#include "../Pieces/Pawn.h"
#include "../Pieces/Queen.h"
#include "../Pieces/Piece.h"
#include <iostream>



MoveMaker::MoveMaker(bool whiteToPlay){
    whiteTurn = whiteToPlay;
}

void MoveMaker::makeMove(const std::string& move){
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

bool MoveMaker::makeCastleMove(std::string move){
    if (move != "0-0" && move != "0-0-0") {std::cout << "[0][DEBUG][moveMaker::makeCastleMove]\n"; return false;}

    if (whiteTurn)
        {
            Piece* king = board->getBoard(0, 4);
            if(king == nullptr || king->getPieceType() != KING) {std::cout << "[1][DEBUG][moveMaker::makeCastleMove]\n"; return false;}

            //white kingside castle
            if (move == "0-0")
                {
                    if (!king->isLegalCastleMove(true, *board)){std::cout << "[2][DEBUG][moveMaker::makeCastleMove]\n"; return false;}

                    Piece* rook = board->getBoard(0, 7);
                    board->setSpaceWithoutDeleting(0, 7, nullptr);
                    board->setSpaceWithoutDeleting(0, 6, king);
                    board->setSpaceWithoutDeleting(0, 5, rook);
                    rook->setCol(5);
                    king->setCol(6);
                    rook->setHasMoved(true);
                    king->setHasMoved(true);

                    undoMoveInfo info;
                    info.whiteMove = 1;
                    info.kingsideCastleMove = 1;

                    previousPositions.push(info);
                    return true;
                }
            //white queenside castle
            else
                {
                    if (!king->isLegalCastleMove(false, *board)){std::cout << "[3][DEBUG][moveMaker::makeCastleMove]\n"; return false;}

                    Piece* rook = board->getBoard(0, 0);
                    board->setSpaceWithoutDeleting(0, 0, nullptr);
                    board->setSpaceWithoutDeleting(0, 2, king);
                    board->setSpaceWithoutDeleting(0, 3, rook);
                    rook->setCol(3);
                    king->setCol(2);
                    rook->setHasMoved(true);
                    king->setHasMoved(true);

                    undoMoveInfo info;
                    info.whiteMove = 1;
                    info.queensideCastleMove = 1;

                    previousPositions.push(info);
                    return true;
                }
        }

    //black logic now
    else
        {
            Piece* king = board->getBoard(7, 4);
            if(king == nullptr || king->getPieceType() != KING) {std::cout << "[4][DEBUG][moveMaker::makeCastleMove]\n"; return false;}

            //black kingside castle
            if (move == "0-0")
                {
                    if (!king->isLegalCastleMove(true, *board)){std::cout << "[5][DEBUG][moveMaker::makeCastleMove]\n"; return false;}

                    Piece* rook = board->getBoard(7, 7);
                    board->setSpaceWithoutDeleting(7, 7, nullptr);
                    board->setSpaceWithoutDeleting(7, 6, king);
                    board->setSpaceWithoutDeleting(7, 5, rook);
                    rook->setCol(5);
                    king->setCol(6);
                    rook->setHasMoved(true);
                    king->setHasMoved(true);

                    undoMoveInfo info;
                    info.whiteMove = 0;
                    info.kingsideCastleMove = 1;

                    previousPositions.push(info);
                    return true;
                }
            //black queenside castle
            else
                {
                    if (!king->isLegalCastleMove(false, *board)){std::cout << "[6][DEBUG][moveMaker::makeCastleMove]\n"; return false;}

                    Piece* rook = board->getBoard(7, 0);
                    board->setSpaceWithoutDeleting(7, 0, nullptr);
                    board->setSpaceWithoutDeleting(7, 2, king);
                    board->setSpaceWithoutDeleting(7, 3, rook);
                    rook->setCol(3);
                    king->setCol(2);
                    rook->setHasMoved(true);
                    king->setHasMoved(true);

                    undoMoveInfo info;
                    info.whiteMove = 0;
                    info.queensideCastleMove = 1;

                    previousPositions.push(info);
                    return true;
                }
        }       
}

void MoveMaker::undoCastleMove(undoMoveInfo& info){
    //white kingside
    Piece* king = board->getBoard(0, 2);
    if (king != nullptr && king->getPieceType() == KING && king->getIsWhite() == 1)
        {
            Piece* rook = board->getBoard(0, 3);
            board->setSpaceWithoutDeleting(0, 3, nullptr);
            board->setSpaceWithoutDeleting(0, 0, rook);
            board->setSpaceWithoutDeleting(0, 2, nullptr);
            board->setSpaceWithoutDeleting(0, 4, king);

            rook->setRow(0);
            rook->setCol(0);
            king->setRow(0);
            king->setCol(4);

            king->setHasMoved(false);
            rook->setHasMoved(false);

            return;
        }

    //white queenside
    king = board->getBoard(0, 6);
    if (king != nullptr && king->getPieceType() == KING && king->getIsWhite() == 1)
        {
            Piece* rook = board->getBoard(0, 5);
            board->setSpaceWithoutDeleting(0, 5, nullptr);
            board->setSpaceWithoutDeleting(0, 7, rook);
            board->setSpaceWithoutDeleting(0, 6, nullptr);
            board->setSpaceWithoutDeleting(0, 4, king);

            rook->setRow(0);
            rook->setCol(7);
            king->setRow(0);
            king->setCol(4);

            king->setHasMoved(false);
            rook->setHasMoved(false);

            return;
        }
    //black kingside
    king = board->getBoard(7, 2);
    if (king != nullptr && king->getPieceType() == KING && king->getIsWhite() == 0)
        {
            Piece* rook = board->getBoard(7, 3);
            board->setSpaceWithoutDeleting(7, 3, nullptr);
            board->setSpaceWithoutDeleting(7, 0, rook);
            board->setSpaceWithoutDeleting(7, 2, nullptr);
            board->setSpaceWithoutDeleting(7, 4, king);

            rook->setRow(7);
            rook->setCol(0);
            king->setRow(7);
            king->setCol(4);

            king->setHasMoved(false);
            rook->setHasMoved(false);
            
            return;
        }
    //black queenside
    king = board->getBoard(7, 6);
    if (king != nullptr && king->getPieceType() == KING && king->getIsWhite() == 0)
        {
            Piece* rook = board->getBoard(7, 5);
            board->setSpaceWithoutDeleting(7, 5, nullptr);
            board->setSpaceWithoutDeleting(7, 7, rook);
            board->setSpaceWithoutDeleting(7, 6, nullptr);
            board->setSpaceWithoutDeleting(7, 4, king);

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

void MoveMaker::undoCaptureMove(undoMoveInfo& info){
    info.movedPiece->setRow(info.fromrow);
    info.movedPiece->setCol(info.fromcol);
    info.movedPiece->setHasMoved(info.hasMoved);
    board->setSpaceWithoutDeleting(info.fromrow, info.fromcol, info.movedPiece);
    board->setSpaceWithoutDeleting(info.torow, info.tocol, info.capturedPiece);

    info.capturedPiece = nullptr;

}

void MoveMaker::undoRegularMove(undoMoveInfo& info){
    info.movedPiece->setRow(info.fromrow);
    info.movedPiece->setCol(info.fromcol);
    info.movedPiece->setHasMoved(info.hasMoved);
    board->setSpaceWithoutDeleting(info.fromrow, info.fromcol, info.movedPiece);
    board->setSpaceWithoutDeleting(info.torow, info.tocol, nullptr);
}

void MoveMaker::undoPromotionMove(undoMoveInfo& info){
    Piece* replacementPawn = new Pawn(info.fromrow, info.fromcol, info.whiteMove);
    //this deletes the promoted piece and puts the captured piece back in the correct position
    board->setSpace(info.torow, info.tocol, info.capturedPiece);
    board->setSpaceWithoutDeleting(info.fromrow, info.fromcol, replacementPawn);
    info.capturedPiece = nullptr;

}

bool MoveMaker::makeCaptureMove(std::string move){
    if (!correctMoveFormat(move)) {std::cout << "[0][DEBUG][MoveMaker::makeCaptureMove]\n"; return false;}

    int fromrow, fromcol, torow, tocol;
    fromrow = letterToArrayIndex(move.at(1));
    torow = letterToArrayIndex(move.at(3));
    fromcol = numberToArrayIndex(move.at(2));
    tocol = numberToArrayIndex(move.at(4));

    Piece* movePiece = board->getBoard(fromrow, fromcol);

    if(!movePiece->isLegalMove(torow, tocol, *board)) {std::cout << "[1][DEBUG][MoveMaker::makeCaptureMove]\n"; return false;}
    if(board->moveCausesSelfCheck(fromrow, fromcol, torow, tocol)) {std::cout << "[2][DEBUG][MoveMaker::makeCaptureMove]\n"; return false;}

    Piece* capturePiece = board->getBoard(torow, tocol);

    //make move on board now
    board->setSpaceWithoutDeleting(fromrow, fromcol, nullptr);
    board->setSpaceWithoutDeleting(torow, tocol, movePiece);

    bool hasMoved = movePiece->getHasMoved();
    movePiece->setHasMoved(true);
    movePiece->setRow(torow);
    movePiece->setCol(tocol);

    //und0move information
    undoMoveInfo info;
    info.capturedPiece = capturePiece;
    info.movedPiece = movePiece;
    info.captureMove = true;
    info.whiteMove = movePiece->getIsWhite();
    info.hasMoved = hasMoved;
    
    info.fromrow = fromrow;
    info.fromcol = fromcol;
    info.torow = torow;
    info.tocol = tocol;

    previousPositions.push(info);
    return true;
}

Piece* MoveMaker::getPieceFromMoveString(const std::string& move) const{
    int fromRow, fromCol;

    //get from 
    fromCol = letterToArrayIndex(move.at(1));
    fromRow = numberToArrayIndex(move.at(2));

    return board->getBoard(fromRow, fromCol);
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

bool MoveMaker::makeRegularMove(std::string move){
    if (!correctMoveFormat(move)) {std::cout << "[0][DEBUG][MoveMaker::makeRegularMove]\n"; return false;}

    int fromrow, fromcol, torow, tocol;
    fromrow = letterToArrayIndex(move.at(1));
    torow = letterToArrayIndex(move.at(3));
    fromcol = numberToArrayIndex(move.at(2));
    tocol = numberToArrayIndex(move.at(4));

    Piece* movePiece = board->getBoard(fromrow, fromcol);

    if(!movePiece->isLegalMove(torow, tocol, *board)) {std::cout << "[1][DEBUG][MoveMaker::makeRegularMove]\n"; return false;}
    if(board->moveCausesSelfCheck(fromrow, fromcol, torow, tocol)) {std::cout << "[2][DEBUG][MoveMaker::makeRegularMove]\n"; return false;}

    bool hasMoved = movePiece->getHasMoved();
    movePiece->setHasMoved(true);
    movePiece->setRow(torow);
    movePiece->setCol(tocol);

    board->setSpaceWithoutDeleting(fromrow, fromcol, nullptr);
    board->setSpaceWithoutDeleting(torow, tocol, movePiece);

    undoMoveInfo info;
    info.movedPiece = movePiece;
    info.regularMove = true;
    info.hasMoved = hasMoved;
    info.whiteMove = movePiece->getIsWhite();

    info.fromrow = fromrow;
    info.fromcol = fromcol;
    info.torow = torow;
    info.tocol = tocol;

    previousPositions.push(info);

    return true;
}

bool MoveMaker::makePromotionMove(std::string move){
    if (!correctMoveFormat(move)) {std::cout << "[0][DEBUG][MoveMaker::makePromotionMove]\n"; return false;}

    int fromrow, fromcol, torow, tocol;
    fromrow = letterToArrayIndex(move.at(1));
    torow = letterToArrayIndex(move.at(3));
    fromcol = numberToArrayIndex(move.at(2));
    tocol = numberToArrayIndex(move.at(4));

    Piece* movePiece = board->getBoard(fromrow, fromcol);
    if (movePiece != nullptr && movePiece->getPieceType() != PAWN) {std::cout << "[1][DEBUG][MoveMaker::makePromotionMove]\n"; return false;}

    Piece* takePiece = board->getBoard(torow, tocol);

    if(!movePiece->isLegalMove(torow, tocol, *board)) {std::cout << "[2][DEBUG][MoveMaker::makePromotionMove]\n"; return false;}
    if(board->moveCausesSelfCheck(fromrow, fromcol, torow, tocol)) {std::cout << "[3][DEBUG][MoveMaker::makePromotionMove]\n"; return false;}

        
    Piece* promotedQueen = new Queen(torow, tocol, movePiece->getIsWhite());
    delete movePiece;

    board->setSpaceWithoutDeleting(fromrow, fromcol, nullptr);
    board->setSpaceWithoutDeleting(torow, tocol, promotedQueen);

    undoMoveInfo info;
    info.promotionMove = 1;
    info.capturedPiece = takePiece;
    info.whiteMove = promotedQueen->getIsWhite();

    info.fromrow = fromrow;
    info.fromcol = fromcol;
    info.torow = torow;
    info.tocol = tocol;

    previousPositions.push(info);
        
}

bool MoveMaker::makeMove(const std::string& move){
    if (!correctMoveFormat(move)) {std::cout << "Incorrect Move Format"; return false;}

    if (move == "0-0" || move == "0-0-0") 
        {
            if (makeCastleMove(move)) {whiteTurn = !whiteTurn; return true;} 
            return false;
        }

    int fromrow, fromcol, torow, tocol;
    fromrow = letterToArrayIndex(move.at(1));
    torow = letterToArrayIndex(move.at(3));
    fromcol = numberToArrayIndex(move.at(2));
    tocol = numberToArrayIndex(move.at(4));

    Piece* movePiece = board->getBoard(fromrow, fromcol);
    Piece* endPiece = board->getBoard(torow, tocol);

    if (movePiece == nullptr || movePiece->getIsWhite() != whiteTurn) {std::cout << "cannot move this piece\n"; return false;}
    
    if (movePiece->getPieceType() == PAWN && (torow == 0 || torow == 7)) 
        {   
            if (makePromotionMove(move)) {whiteTurn = !whiteTurn; return true;}
            return false;
        }

    if (endPiece == nullptr)    
        {
            if (makeRegularMove(move)) {whiteTurn = !whiteTurn; return true;}
            return false;
        }

    if (endPiece != nullptr)
        {
            if (makeCaptureMove(move)) {whiteTurn = !whiteTurn; return true;}
            return false;
        }

    std::cout << "[0][DEBUG][MoveMaker::makeMove]";
    return false;
}






