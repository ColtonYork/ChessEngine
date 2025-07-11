#pragma once
#include "../Game/moveStringAndScore.h"
#include <vector>
#include <string>
#include <queue>

class Board;

enum pieceType {PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING, NONE};
class Piece {

    public:
    /*
        Brief: Piece constructor

        r: The row to set the piece to
        c: the column to set the piece to
        isW: true if piece IS white
    
    */
    Piece(unsigned char r, unsigned char c, bool isW);


    /*
        Brief: Returns the child piece as an enum
    */
    virtual pieceType getPieceType() const = 0;


    /*
        Brief: Parent calss destructor
    */
    virtual ~Piece() {}


    /*
        Brief: Returns a clone of itself
    */
    virtual Piece* clone() const = 0;


    /*
        Brief: Checks if a particular move is legal to make

        toRow: The row that the piece wants to move to
        toCol: The column that the piece wants to move to
    */
    virtual bool isLegalMove(unsigned char toRow, unsigned char toCol, const Board& b) const = 0;


    /*
        Brief: Returns isWhite member variable
    */
    bool getIsWhite();


    /*
        Brief: returns True if a move is inbounds
    */
    bool moveIsInbounds(unsigned char toRow, unsigned char toCol) const;


    /*
        Brief: Checks if the space a piece is moving to is allowed to move there. Returns FALSE if piece is occupied by same color. 
        Returns TRUE if space is an opponent piece or space is empty

        checkRow: end spot row to check
        checkColumn: end spot column to check
        b: the Board to check
    */
    virtual bool endSpotLegal(unsigned char checkRow, unsigned char checkCol, const Board& b) const = 0;


    /*
        Brief: returns TRUE when the specified spot has an opponents piece

        checkRow: The row being checked
        checkCol: the column being checked
        b: the board beeing asessed
    */
    bool spotIsOpponent(unsigned char checkRow, unsigned char checkCol, const Board& b) const;


    /*
        Brief: Returns the row of the caller
    */
    unsigned char getRow() const;


    /*
        Brief: Returns the column of the caller
    */
    unsigned char getCol() const;

    /*
        Brief: Implemneted by PAWN, KING, and ROOK. 
        Just returns false for default parent class definition
    */
    virtual bool getHasMoved() const;


    /*
        Brief: sets row to specified value
    */
    void setRow (unsigned char r);


    /*
        Brief: sets col to specified value
    */
    void setCol (unsigned char c);


    /*
        Brief: Implemented only in King class. Returns fals from parent class

        kingSide: TRUE when looking if kingside castle is legal
        b: The board being asessed
    */
    virtual bool isLegalCastleMove(bool kingSide, const Board& b) const;


    /*
        Brief: Implemented by all piece children to determine if the piece has a legal move available. Used for checking stalemate mainly.
        If a piece has legal move by deletion, then it means that the piece has a 1 space move around it AND it doesn't cause check when deleted
        ~This function is intended to make stalemate checking more efficient

        b: the board being asessed
    */
    virtual bool hasOneSpaceLegalMove(const Board* b) const = 0;

    /*
        Breif: determines if a piece has a fully legal and verified move possible on the baord

        b: the board being asessed
        checkOneSpaceMoves: True when needeing to check one space moves. These moves are already checked in hasLegalMoveByDeletion so it may not be needed
    */
    virtual bool hasVerifiedMove(Board* b) = 0;


    /*
        Brief: inputs a specific pieces' possible moves along with ordering the moves by quickvalue (piece value - captured piece value)

        board: The current board being asessed
    */
    virtual void computePossibleMoves(Board* b, std::priority_queue<moveStringAndScore>& q) = 0;


    /*
        Brief: Returns the integer value of a piece
        King = 1000
        Queen = 9
        Rook = 5
        Bishop = 3
        Knight = 3
        Pawn = 1
    */
    virtual int getPieceValue() const = 0;


    /*
        Brief: Takes in a row and col and return the board string representation. EX: 01 = A2

        row: The Row to be converted
        col: The Col to be converted
    */
   std::string arrayIndexToString(const int& row, const int& col) const;


    /*
        Brief: Used to set hasMoved functions in certain piece classes. Notably for King class and maybe Pawn

        hm: the value to set hasMoved to
    */
   virtual void setHasMoved(bool hm);


   /*   
        Brief: returns the first part of a pieces move string 
   */ 
   std::string getFirstSquareOfMoveString();


   /*   
        Brief: returns the last part of the move string given the coordinates

        col: col
        row: row
   */
   std::string getLastPartOfMoveString(const int& col, const int& row);






    protected:
    unsigned char row;
    unsigned char col;
    bool isWhite;



};





