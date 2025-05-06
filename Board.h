#pragma once

class Piece;


class Board {
    public:
    /*
        Brief: Board Constructor. Sets board to starting chess position 
    */
    Board();
    
    /*
        Brief: Board copy constrcutor
    */
    Board(const Board& other);


    /*  
        Brief: Board Assignment
    */
    Board& operator=(const Board& other);


    /*
        Brief: Board deconstructor. Deletes all Piece pointers in 2d array
    */
    ~Board();


    /*
        Brief: Displays the current state of the board
    */
    void displayBoard() const;

    /*
        Brief: Returns a Piece pointer of a specified board index
    */
    Piece* getBoard(unsigned char row, unsigned char col) const;


     /*
        Brief: Determines if a square is being attacked by opponent

        checkRow: The row of the square that needs checked
        checkCol: The column of the square that needs checked
        byWhite: TRUE when wanting to see if WHITE is attacking a square
        b: The board being asessed
    */
    bool squareUnderAttack(unsigned char checkRow, unsigned char checkCol, bool byWhite) const;


    /*
        Brief: Returns true if the specified king is in check
    */
    bool Board::kingInCheck(bool whiteKing) const;


    /*
        Brief: Returns king piece from baord
    */
    Piece* findKing(bool whiteKing) const;


    private:
    Piece* board[8][8]; // Row | Column






};
