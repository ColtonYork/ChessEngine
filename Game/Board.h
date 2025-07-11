#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <queue>
#include "moveStringAndScore.h"

class Piece;


class Board {
    public:
    /*
        Brief: Board Constructor. Sets board to starting chess position 
    */
    Board();
    
    /*
        Brief: Board copy constrcutor

        other: the board to be copied
    */
    Board(const Board& other);


    /*  
        Brief: Board Assignment

        other: the board to be assigned
    */
    Board& operator=(const Board& other);


    /*
        Brief: Board deconstructor. Deletes all Piece pointers in 2d array
    */
    ~Board();


    /*
        Brief: Displays the current state of the board
    */
    void displayBoard() const;


    /*
        Brief: Returns a Piece pointer of a specified board index

        row: The row of the board to get the piece from
        col: The column of the board to get the piece from
    */
    Piece* getBoard(unsigned char row, unsigned char col) const;


    /*
        Brief: Determines if a square is being attacked by opponent

        checkRow: The row of the square that needs checked
        checkCol: The column of the square that needs checked
        byWhite: TRUE when wanting to see if WHITE is attacking a square
        b: The board being asessed
    */
    bool squareUnderAttack(unsigned char checkRow, unsigned char checkCol, bool byWhite) const;


    /*
        Brief: Returns true if the specified king is in check

        whiteKing: TRUE when wanting to see if WHITE king is in check
    */
    bool kingInCheck(bool whiteKing) const;


    /*
        Brief: Returns king piece from board

        whiteKing: TRUE when wanting to find WHITE king
    */
    Piece* findKing(bool whiteKing) const;

    /*
        Brief: Sets a board space to a specified piece

        row: The row to set the piece to
        col: The column to set the piece
        piece: The piece that is being set at the row/coulm provided
    */
    void setSpace(unsigned char row, unsigned char col, Piece* piece);
   
   
   /*
        Brief: returns TRUE if the specified player has a legal move by deletion optimization. The function will get to a specified colors piece, 
        check if it has space to move around it, then delete it and check if it causes selfcheck when deleted

        white: TRUE when checking if white has a legal move
    */
    bool playerHasLegalMoveByDeletion(bool white);

    /*
        Brief: The function above, playerHasLegalMovebyDeletion, is only an optimization to find any legal moves. This function will check the rest of the possible moves if checking by deletion does not find a legal move.

        white: TRUE when checking if white has a legal move
    */
    bool playerHasLegalMoveByPiece(bool white);


    /*
        Brief: Returns TRUE if the specified player has a legal move available.

        white: the player being checked for a possible legal move.
    */
    bool playerHasLegalMove(bool white);


    /*
        Brief: Simulates a move on the board ot determine if it causes self check

        fromRow: The row that the piece is at
        fromCol: The col that the piece is at
        toRow: The row the piece is moving to
        toCol; The column that the pece is moving to
    */
    bool moveCausesSelfCheck(int fromRow, int fromCol, int toRow, int toCol);

    /*
        Brief: determines if a set of board coordinates are inbounds

        row: row coordinate
        col: column coordinate
    */
    bool coordsAreInbounds(int row, int col) const;


    /*
        Brief: generates all possible Moves of a current board and returns an array of Board pointers that point to every possbile position. 

        white: The player we are checking moves for
    */
    //std::priority_queue<Board*> Board::generateLegalMoves(bool white);


    /*
        Brief: Takes a FEN string and loads a specified coard

        FEN: The FEN string that will be put ot the baord
    */
    Board(const std::string& fen);


    /*
        Brief: deletes every space on the board AND sets all spaces to nullptr
    */
    void clearBoard();


    /*
        Brief: Sets all spaces on the board to nullptr. DOES NOT delete all prior board spaces
    */
    void initializeBoard();

    /*
        Brief: Sets the board back to the starting positon
    */
    void restartBoard();


    /*
        allows any board to be cleared and then set to a different position

        fen: The fen string being used
    */
    void generateBoardFromFENString(const std::string& fen);

    
    /*
        Brief: sets a space on the board without deleting the piece that was their prior

        row: The row of the space
        col: The column of the space
        piece: The piece to be placed on this space
    */
    void setSpaceWithoutDeleting(const int& row, const int& col, Piece* piece);


    /*
        brief: Loops thru all board spaces and makes sure all pieces internal row and col match the baords representation
    */
    bool pieceCoordsAreAccurate() const;


    /*
        Brief: computes all possible pieces for the specified player and returns in order of quickvalue (piece value - captured piece value)

        white: The player to compute moves for
    */
    std::priority_queue<moveStringAndScore> computePossibleMoves(bool white);











    


    private:
    Piece* board[8][8]; // Row | Column






};
