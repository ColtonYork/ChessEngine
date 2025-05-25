#pragma once

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
        Brief: returns TRUE if a specified position is stalemate for the player inserted. TRUE for white means checking if white is in stalemate.

        white: TRUE when checking if white is in staemate
        b: the board being asessed
    */
    bool positionIsStalemate(bool white, Board* b) const;

    


    private:
    Piece* board[8][8]; // Row | Column






};
