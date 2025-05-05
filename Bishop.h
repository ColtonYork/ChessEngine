#pragma once
#include "Piece.h"

class Bishop: public Piece{
    public:
     /*
        Bishop constructor
        Brief: Calls the Piece class' constructor for row, column, and isWhite;

        r: The row to set the Rook to
        c: the column to set the Rook to
        isW: true if Bishop IS white
    */
    Bishop(unsigned char r, unsigned char c, bool isW);


    /*
        Brief: Purely Virtual Override returns piece type BISHOP
    */
    pieceType getPieceType() const;


    /*
        Purely Virtual override from Piece class
        Brief: Returns a cloned bishop
    */
    Piece* clone() const;


    /*
        Purely Virtual override from Piece class
        brief: Checks if a particular Bishop move is legal

        toRow: The row that the Bishhop wants to move to
        toCol: The column that the Bishop wnats to move to
    */
    bool isLegalMove(unsigned char toRow, unsigned char toCol, Board& b) const;


    /*
        Brief: checks if spaces between a specified bishop move are empty

        Booleans: gets the direction of the bishop move
        toRow: The row that the bishop is moving to 
        toCol: The column the bishop is moving to
        b: Current board to asess
    */
    bool isLegalBetween(bool upleft, bool upright, bool downleft, bool downright, unsigned char toRow, unsigned char toCol, Board& b) const;




    private:




};