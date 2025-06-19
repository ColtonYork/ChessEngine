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
    bool isLegalMove(unsigned char toRow, unsigned char toCol, const Board& b) const;


    /*
        Brief: Determines if Queen movement is Rook-based and if it is valid

        toRow: The row that the Queen wants to move to
        toCol: The column that the Queen wnats to move to
    */
    bool isLegalRookMovement(unsigned char toRow, unsigned char toCol, const Board& b) const;


    /*
        Brief: Determines if Queen movement is Bishop-based and if it is valid

        toRow: The row that the Queen wants to move to
        toCol: The column that the Queen wnats to move to
        b: the board being asessed 
    */
    bool isLegalBishopMovement(unsigned char toRow, unsigned char toCol, const Board& b) const;


    /*
        Brief: Checks if the Queens' Rook movement path is clear

        toRow: The row that the Queen wants to move to
        toCol: The column that the Queen wnats to move to
        b: the board being asessed 
    */
    bool isLegalBetweenRookMovement(bool rowMove, unsigned char from, unsigned char to, const Board& b) const;


    /*
        Brief: Checks if the Queens' Bishop movement path is clear

        toRow: The row that the Queen wants to move to
        toCol: The column that the Queen wnats to move to
        b: the board being asessed 
    */
    bool isLegalBetweenBishopMovement(bool upleft, bool upright, bool downleft, bool downright, unsigned char toRow, unsigned char toCol, const Board& b) const;


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
        brief: Checks if the Queen has a legal one-space move

        b: The board being asessed
    */
    bool hasOneSpaceLegalMove(const Board* b) const;



    /*
        Virtual Override from piece class
        Breif: determines if bishop has a fully legal and verified move possible on the baord
        ~This function is just the methods for the bishop and rook hasVerifiedMove function copy and pasted

        b: the board being asessed
    */
    bool hasVerifiedMove(Board* b);


    /*
        Purely Virtual Override fork piece class
        Brief: returns the value of a Queen (9) 
    */
    int getPieceValue() const;


    /*  
        Brief: determines if there is a possible Bishop move for this Queen to make given the sides to check for

        b: the board being assesed
    */
    bool existsPossibleMoveBishopMovement(Board* b, bool upright, bool upleft, bool downright, bool downleft);


    /*  
        Brief: determines if there is a possible Rook move for this Queen to make given the sides to check for

        b: the board being assesed
    */
    bool Queen::existsPossibleMoveRookMovement(Board* b, bool up, bool down, bool left, bool right);


    /*  
        Brief: determines if there is a possible move for this Queen to make given the sides to check for

        b: the board being assesed
    */
    bool Queen::existsPossibleMove(Board* b, bool upright, bool upleft, bool downright, bool downleft, bool up, bool down, bool left, bool right);





    private:




};