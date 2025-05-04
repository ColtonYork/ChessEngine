#include "Board.h"





class Game{

    public:
    /*
        Brief: initializes movesPlayed = 0 AND whiteTurn = true
    */
    Game();


    /*
        Brief: Makes the move on the board. Should be called after move is found legal

        fromRow: The row that the piece is currently at
        fromCol: The Column that the piece is currently at
        toRow: The row that the piece is moving to
        toCol: The column that the piece is moving to

    */
    void makeMove(unsigned char fromRow, unsigned char fromCol, unsigned char toRow, unsigned char toCol);

    private:
    Board board;
    int movesPlayed;
    bool whiteTurn;

};