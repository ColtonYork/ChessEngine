#include "Piece.h"

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


    private:
    Piece* board[8][8]; // Row | Column






};
