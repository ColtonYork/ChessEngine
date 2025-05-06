#pragma once
#include "Piece.h"

class King: public Piece{
    public:
     /*
        King constructor
        Brief: Calls the Piece class' constructor for row, column, and isWhite;

        r: The row to set the Rook to
        c: the column to set the Rook to
        isW: true if King IS white

        Personal Member hasMoved: set to false
        personal Member inCheck: set to false

    */
    King(unsigned char r, unsigned char c, bool isW);


    /*
        Brief: Purely Virtual Override returns piece type KING
    */
    pieceType getPieceType() const;


    /*
        Purely Virtual override from Piece Class
        Brief: Returns a cloned King
    */
    Piece* clone() const;


    /*
        Purely Virtual override from Piece class
        brief: Checks if a particular King move is legal

        castle: runs the isLegalCastleMove function if move is a castle move
        toRow: The row that the King wants to move to
        toCol: The column that the King wnats to move to
    */
    bool isLegalMove(unsigned char toRow, unsigned char toCol, const Board& b) const;

    
    /*
        Brief: checks if a castle move is valid

        kingSide: TRUE if the castle attmept is to the kings side 0-0 
        b: The board being asessed
    */
    bool isLegalCastleMove(bool kingSide, const Board& b) const;


    /*
        Virtual Override from Piece class
        Brief: returns hasMoved private member variable
    */
    bool getHasMoved() const;




    private:
    bool hasMoved;
    bool inCheck;




};