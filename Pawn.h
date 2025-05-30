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


    /*
        Virtual Override from Piece class
        Brief: returns hasMoved private member variable
    */
    bool getHasMoved() const;


    /*
        Purely Virtual override from Piece class
        brief: Checks if the pawn has a legal move

        b: The board being asessed
    */
    bool hasOneSpaceLegalMove(const Board* b) const;


    /*
        Purely virtual overide from piece class
        Brief: determines if the final square of the move is legal. returns TRUE if legal

        checkRow: the row of the square to be checked
        checkCol: the Column of the square to be checked
        b: The board being asessed
    */
    bool endSpotLegal(unsigned char checkRow, unsigned char checkColumn, const Board& b) const;




    private:
    bool hasMoved;




};