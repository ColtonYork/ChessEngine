#include "Board.h"


class Evaluator{
    public:

    
    Board* minimax(Board* board, int depth, bool maximizeWhite, int alpha, int beta);

    /*
        Brief: Evaluates a position given a board state. returns an integer with negative being good for black and Positive being good for White. Value of 0 would represent even position

        Board: The board that is being evaulated
    */
    virtual int evaluatePosition(const Board* board) const = 0;

};