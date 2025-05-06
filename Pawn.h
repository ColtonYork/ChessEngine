#pragma once
#include "Piece.h"

class Pawn: public Piece{
    public:
     /*
        Pawn constructor
        Brief: Calls the Piece class' constructor for row, column, and isWhite;

        r: The row to set the Rook to
        c: the column to set the Rook to
        isW: true if Pawn IS white

        Personal Member hasMoved: set to false
    */
    Pawn(unsigned char r, unsigned char c, bool isW);


    /*
        Brief: Purely Virtual Overridereturns piece type PAWN
    */
    pieceType getPieceType() const;


     /*
        Purely Virtual override from Piece Class
        Brief: Returns a cloned Pawn
    */
    Piece* clone() const;


    /*
        Purely Virtual override from Piece Class
        brief: Checks if a particular Pawn move is legal

        toRow: The row that the Pawn wants to move to
        toCol: The column that the Pawn wnats to move to
    */
    bool isLegalMove(unsigned char toRow, unsigned char toCol, const Board& b) const;


    /*
        Brief: determines if the simple up-one-move is valid

        toRow: The row that the piece is moving to
        toCol: The column that the piece is moving to
        b: The current board to asess
    */
    bool isLegalUpOneMove(unsigned char toRow, unsigned char toCol, const Board& b) const;


    /*
        Brief: Determines if the take piece movement is valid

        toRow: The row that the piece is moving to
        toCol: The column that the piece is moving to
        b: The current board to asess
    */
    bool isLegalTakePieceMove(unsigned char toRow, unsigned char toCol, const Board& b) const;


    /*
        Brief: Determines if the two-up move is valid

        toRow: The row that the piece is moving to
        toCol: The column that the piece is moving to
        b: The current board to asess
    */
    bool isLegalTwoUpMove(unsigned char toRow, unsigned char toCol, const Board& b) const;


    /*
        Brief: Determines if a pawn move awards promotion. Will return TRUE if the pawn reaches the opposite side of the board.

        toRow: The row that the piece is moving to
    */
    bool promotionMove(unsigned char toRow) const;



    private:
    bool hasMoved;




};