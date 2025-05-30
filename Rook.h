#pragma once
#include "Piece.h"

class Rook: public Piece{
    public:
    /*
        Rook constructor
        Brief: Calls the Piece class' constructor for row, column, and isWhite;

        r: The row to set the Rook to
        c: the column to set the Rook to
        isW: true if Rook IS white

        Personal Member hasMoved: set to false
    */
    Rook(unsigned char r, unsigned char c, bool isW);


    /*
        Brief: Purely Virtual Overridereturns piece type ROOK
    */
    pieceType getPieceType() const;


    /*
        Purely Virtual override from Piece Class
        Brief: Returns a cloned Rook
    */
    Piece* clone() const;


    /*
        Purely Virtual override from Piece Class
        Brief: Returns TRUE if a specified Rook move is legal

        toRow: The row that the Rook want to move to
        toCol: The column that the Rook wants to move to
    */
    bool isLegalMove(unsigned char toRow, unsigned char toCol, const Board& b) const;


    /*
        Brief: Checks the spaces between current position and end position. Returns TRUE if all spaces in between are nullptr

        rowMove: True is the current move is only changing rows
        from: the row/col that the Rook starts at
        to: the row/col that the Rook ends at
        Board: current board to check, passed by reference
    */
    bool isLegalBetween(bool rowMove, unsigned char from, unsigned char to, const Board& b) const;


    /*
        Virtual Override from Piece class
        Brief: returns hasMoved private member variable
    */
    bool getHasMoved() const;


    /*
        Purely virtual overide from piece class
        Brief: determines if the final square of the move is legal. returns TRUE if legal

        checkRow: the row of the square to be checked
        checkCol: the Column of the square to be checked
        b: The board being asessed
    */
    bool endSpotLegal(unsigned char checkRow, unsigned char checkColumn, const Board& b) const;


    /*
        Purely Virtual override from Piece class
        brief: Checks if the Rook has a legal one-space move

        b: The board being asessed
    */
    bool hasOneSpaceLegalMove(const Board* b) const;





    private:
    bool hasMoved;




};