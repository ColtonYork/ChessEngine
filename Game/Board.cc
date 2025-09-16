#include "Board.h"
#include "../Pieces/Piece.h"
#include "../Pieces/Rook.h"
#include "../Pieces/King.h"
#include "../Pieces/Knight.h"
#include "../Pieces/Queen.h"
#include "../Pieces/Pawn.h"
#include "../Pieces/Bishop.h"
#include <iostream>
#include <queue>
#define BROWN "\033[33;2m"       // or "\033[33;1m" for a different shade
#define RESET "\033[0m"
#define DARK_GRAY "\033[90m"


Board::Board()
{

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

    //set empty squares to nullptr
    for(int i = 2; i < 6; i++){
        for (int j = 0; j < 8; j++){
            board[i][j] = nullptr;
        }
    }
}

Board::Board(const Board& other)
{
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
                if (p->getPieceType() == PAWN){std::cout << DARK_GRAY << "P " << RESET;}
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
    //std::cout << "King found" << static_cast<int>(king->getRow()) << " " << static_cast<int>(king->getCol()) << '\n';

    //Whites king's coordinates are found, check if any enenmy pieces can target that square
    if (squareUnderAttack(king->getRow(), king->getCol(), !white)) {std::cout << "King is in check by: " << '\n'; return true;}
    //std::cout << "King is not in check" << '\n';
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
    //loop thru pieces
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

bool Board::moveCausesSelfCheck(int fromRow, int fromCol, int toRow, int toCol){
    if (!coordsAreInbounds(fromRow, fromCol) || !coordsAreInbounds(toRow, toCol)) {return false;}

    bool causesSelfCheck = false;

    Piece* piece = board[fromRow][fromCol];

    piece->setRow(toRow);
    piece->setCol(toCol);

   board[fromRow][fromCol] = nullptr;
    
    //clone the take piece if the move is taking an opponents peice
    if (board[toRow][toCol] != nullptr)
        {
            Piece* takePiece = board[toRow][toCol];
            board[toRow][toCol] = piece;

            if (kingInCheck(piece->getIsWhite())) {causesSelfCheck = 1;}

            //revert board to original position
            piece->setRow(fromRow);
            piece->setCol(fromCol);
            board[fromRow][fromCol] = piece;
            board[toRow][toCol] = takePiece;            
            return causesSelfCheck;
        }
    //if toRow, toCol is an empty space
    else{ 
        
            board[toRow][toCol] = piece;

            if (kingInCheck(piece->getIsWhite())) {causesSelfCheck = 1;}

            piece->setRow(fromRow);
            piece->setCol(fromCol);
            board[fromRow][fromCol] = piece;
            board[toRow][toCol] = nullptr;

            return causesSelfCheck;
        }

}

bool Board::playerHasLegalMoveByPiece(bool white){
    for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if (board[i][j] == nullptr || board[i][j]->getIsWhite() != white) {continue;}

                //std::cout << "Checking piece at " << i << "," << j << '\n';
                if (board[i][j]->hasVerifiedMove(this)) {
                    //std::cout << "Found legal move for piece at " << i << "," << j << '\n';
                    return true;
                }
        }
        }
        std::cout << "No legal moves found" << '\n';
        return false;
}

bool Board::playerHasLegalMove(bool white){
        if (playerHasLegalMoveByPiece(white)) {return true;}
        return false;
}

bool Board::coordsAreInbounds(int row, int col) const{
    if (row > 7 || row < 0 || col > 7 || col < 0) {return false;}   
    
    return true;

}

Board::Board(const std::string& fen){
    initializeBoard();

    int row = 7;
    int col = 0;
    for (size_t i = 0; i < fen.length(); i++)
        {
            char character = fen.at(i);

            //empty spaces
            if (isdigit(character))
                {
                    col += character - '0';
                    continue;
                }
            else if (character == ' ') {break;}
                

            switch (character)
                {
                    case '/':  
                        row--;
                        col = 0;
                        break;

                    //black pieces
                    case 'p':
                        board[row][col] = new Pawn(row, col, false);
                        col++;
                        break;

                    case 'r':
                        board[row][col] = new Rook(row, col, false);
                        col++;
                        break;

                    case 'n':
                        board[row][col] = new Knight(row, col, false);
                        col++;
                        break; 

                    case 'b':
                        board[row][col] = new Bishop(row, col, false);
                        col++;
                        break;

                    case 'q':
                        board[row][col] = new Queen(row, col, false);
                        col++;
                        break;

                    case 'k':
                        board[row][col] = new King(row, col, false);
                        col++;
                        break;
                    
                    //white pieces
                    case 'P':
                        board[row][col] = new Pawn(row, col, true);
                        col++;
                        break;

                    case 'R':
                        board[row][col] = new Rook(row, col, true);
                        col++;
                        break;

                    case 'N':
                        board[row][col] = new Knight(row, col, true);
                        col++;
                        break; 

                    case 'B':
                        board[row][col] = new Bishop(row, col, true);
                        col++;
                        break;

                    case 'Q':
                        board[row][col] = new Queen(row, col, true);
                        col++;                        
                        break;
                        
                    case 'K':
                        board[row][col] = new King(row, col, true);
                        col++;
                        break;

                    default:
                        std::cout << "Invalid character in FEN string: " << character << '\n';
                        break;
                }
            
        }
}

void Board::clearBoard(){
    for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
                {
                    delete board[i][j];
                    board[i][j] = nullptr;
                }
        }
}

void Board::initializeBoard(){
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
                {
                    board[i][j] = nullptr;
                }
        }
}

void Board::restartBoard(){
    clearBoard();
    
    std::string startFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

    generateBoardFromFENString(startFEN);

    
}

void Board::generateBoardFromFENString(const std::string& fen){
    clearBoard();

    int row = 7;
    int col = 0;
    for (size_t i = 0; i < fen.length(); i++)
        {
            char character = fen.at(i);

            //empty spaces
            if (isdigit(character))
                {
                    col += character - '0';
                    continue;
                }
            else if (character == ' ') {break;}
                

            switch (character)
                {
                    case '/':  
                        row--;
                        col = 0;
                        break;

                    //black pieces
                    case 'p':
                        board[row][col] = new Pawn(row, col, false);
                        col++;
                        break;

                    case 'r':
                        board[row][col] = new Rook(row, col, false);
                        col++;
                        break;

                    case 'n':
                        board[row][col] = new Knight(row, col, false);
                        col++;
                        break; 

                    case 'b':
                        board[row][col] = new Bishop(row, col, false);
                        col++;
                        break;

                    case 'q':
                        board[row][col] = new Queen(row, col, false);
                        col++;
                        break;

                    case 'k':
                        board[row][col] = new King(row, col, false);
                        col++;
                        break;
                    
                    //white pieces
                    case 'P':
                        board[row][col] = new Pawn(row, col, true);
                        col++;
                        break;

                    case 'R':
                        board[row][col] = new Rook(row, col, true);
                        col++;
                        break;

                    case 'N':
                        board[row][col] = new Knight(row, col, true);
                        col++;
                        break; 

                    case 'B':
                        board[row][col] = new Bishop(row, col, true);
                        col++;
                        break;

                    case 'Q':
                        board[row][col] = new Queen(row, col, true);
                        col++;                        
                        break;
                        
                    case 'K':
                        board[row][col] = new King(row, col, true);
                        col++;
                        break;

                    default:
                        std::cout << "Invalid character in FEN string: " << character << '\n';
                        break;
                }
            
        }

}

void Board::setSpaceWithoutDeleting(const int& row, const int& col, Piece* piece){
    board[row][col] = piece;
 }

bool Board::pieceCoordsAreAccurate() const{
    for (int i = 0; i < 8; i ++)
        {
            for( int j = 0; j < 8; j++)
                {
                    Piece* currentPiece = getBoard(i, j);
                    if (currentPiece == nullptr) {continue;}

                    if (currentPiece->getRow() != i || currentPiece->getCol() != j)
                        {
                            std::cout << "[0][DEBUG][Board::pieceCoordsAreAccurate]\n";
                            return false;
                        }
                }
        }
        return true;
}

std::priority_queue<moveStringAndScore> Board::computePossibleMoves(bool white){
    std::priority_queue<moveStringAndScore> returnQueue;

    for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j ++)    
                {
                    Piece* piece = board[i][j];

                    if (piece != nullptr && piece->getIsWhite() == white) {piece->computePossibleMoves(this, returnQueue);}
                }
        }

        return returnQueue;

    
}

std::vector<float> Board::currentBoardToInputTensor() const{
    std::vector<float> inputTensor(768, 0.0f);

    // First 2 for loops are for the baord
    for (int i = 0; i < 8; i++) 
        {
            for (int j = 0; j < 8; j++)
                {
                    Piece* piece = board[i][j];
                    if (piece == nullptr) continue;
    
                    int boardSpace = (i* 8 + j) * 12;
                    inputTensor[boardSpace + piece->getPieceType()*2 + static_cast<int>(piece->getIsWhite())] = 1;
                }
        }

    return inputTensor;
}

          






















