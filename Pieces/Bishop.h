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
    bool isLegalMove(unsigned char toRow, unsigned char toCol, const Board& b) const;


    /*
        Brief: checks if spaces between a specified bishop move are empty

        Booleans: gets the direction of the bishop move
        toRow: The row that the bishop is moving to 
        toCol: The column the bishop is moving to
        b: Current board to asess
    */
    bool isLegalBetween(bool upleft, bool upright, bool downleft, bool downright, unsigned char toRow, unsigned char toCol, const Board& b) const;


    /*
        Purely Virtual override from Piece class
        brief: Checks if the bishop has any legal moves on the board by deletion

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
        Breif: determines if bishop has a fully legal and verified move possible on the baord

        b: the board being asessed
    */
    bool hasVerifiedMove(Board* b);


    /*
        Purely Virtual Override fork piece class
        Brief: returns the value of a bishop (3) 
    */
    int getPieceValue() const;


    /*
        Brief: determines if there is a possible move for this bishop to make given the sides to check for

        b: the board being assesed
    */
    bool existsPossibleMove(Board* b, bool upright, bool upleft, bool downright, bool downleft);


    /*
        Brief: Returns board copies of all possible moves for a piece as an array

        board: The current board being asessed
    */
    //std::vector<moveResult> computePossibleMoves(Board* b);

    













    private:




};