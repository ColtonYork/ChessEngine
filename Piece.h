#pragma once

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
    bool endSpotLegal(unsigned char checkRow, unsigned char checkCol, const Board& b) const;


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



    protected:
    unsigned char row;
    unsigned char col;
    bool isWhite;



};





