#include "Piece.h"

class Board {
    public:
    Board();
    
    Board(const Board& other);

    Board& operator=(const Board& other);
    
    ~Board();


    void displayBoard() const;


    private:
    Piece* board[8][8];






};
