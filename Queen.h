#pragma once
#include "Piece.h"

class Queen: public Piece{
    public:
     /*
        Queen constructor
        Brief: Calls the Piece class' constructor for row, column, and isWhite;

        r: The row to set the Rook to
        c: the column to set the Rook to
        isW: true if Queen IS white
    */
    Queen(unsigned char r, unsigned char c, bool isW);


    /*
        Brief: Purely Virtual Override returns piece type QUEEN
    */
    pieceType getPieceType() const;


    /*
        Purely Virtual override from Piece Class
        Brief: Returns a cloned Queen
    */
    Piece* clone() const;
    

    /*
        Purely Virtual override from Piece Class
        brief: Checks if a particular Bishop move is legal

        toRow: The row that the Queen wants to move to
        toCol: The column that the Queen wnats to move to
    */
    bool isLegalMove(unsigned char toRow, unsigned char toCol, Board& b) const;


    /*
        Brief: Determines if Queen movement is Rook-based and if it is valid

        toRow: The row that the Queen wants to move to
        toCol: The column that the Queen wnats to move to
    */
    bool isLegalRookMovement(unsigned char toRow, unsigned char toCol, Board& b) const;


    /*
        Brief: Determines if Queen movement is Bishop-based and if it is valid

        toRow: The row that the Queen wants to move to
        toCol: The column that the Queen wnats to move to
        b: the board being asessed 
    */
    bool isLegalBishopMovement(unsigned char toRow, unsigned char toCol, Board& b) const;


    /*
        Brief: Checks if the Queens' Rook movement path is clear

        toRow: The row that the Queen wants to move to
        toCol: The column that the Queen wnats to move to
        b: the board being asessed 
    */
    bool isLegalBetweenRookMovement(bool rowMove, unsigned char from, unsigned char to, Board& b) const;


    /*
        Brief: Checks if the Queens' Bishop movement path is clear

        toRow: The row that the Queen wants to move to
        toCol: The column that the Queen wnats to move to
        b: the board being asessed 
    */
    bool isLegalBetweenBishopMovement(bool upleft, bool upright, bool downleft, bool downright, unsigned char toRow, unsigned char toCol, Board& b) const;




    private:




};