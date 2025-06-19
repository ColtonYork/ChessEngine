#pragma once
#include "Piece.h"

class Knight: public Piece{
    public:
     /*
        Knight constructor
        Brief: Calls the Piece class' constructor for row, column, and isWhite;

        r: The row to set the Rook to
        c: the column to set the Rook to
        isW: true if Knight IS white    
    */
    Knight(unsigned char r, unsigned char c, bool isW);


    /*
        Brief: Purely Virtual Override returns piece type KNIGHT
    */
    pieceType getPieceType() const;


    /*
        Purely Virtual override from Piece Class
        Brief: Returns a cloned Knight
    */
    Piece* clone() const;


    /*
        Purely Virtual override from Piece class
        brief: Checks if a particular Knight move is legal

        toRow: The row that the Knight wants to move to
        toCol: The column that the Knight wnats to move to
    */
    bool isLegalMove(unsigned char toRow, unsigned char toCol, const Board& b) const;


    /*
        Purely Virtual override from Piece class
        brief: Checks if the knight has any legal moves on the board by deletion

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

    
    /*
        Virtual Override from piece class
        Breif: determines if a knight has a fully legal and verified move possible on the baord

        b: the board being asessed
    */
    bool hasVerifiedMove(Board* b);


    /*
        Purely Virtual Override fork piece class
        Brief: returns the value of a Knight (3) 
    */
    int getPieceValue() const;



    private:




};