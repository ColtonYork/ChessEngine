#include <string>
#include <vector>
#include <stack>
#include "Board.h"
#include "undoMoveInfo.h"

class Move{
    public:

    /*
        Brief: move constructor.

        whiteToPlay: Determines who's turn it is. sets the whiteTurn private variable;
    */
    Move(bool whiteToPlay);


    /*
        Brief: Makes a move on the board without creating a new board

        move: The move being made
        b: The board to be assesed
    */
    void makeMove(Board* b, const std::string& move);


    /*
        Brief: Unmaes the previous move only. Only the previous board state is remembered so you can only do this one time per move made
    */
    void unmakeMove();


    /*
        Brief: Checks if the move string is properly formatted

        move: The move string being checked
    */
    bool correctMoveFormat(const std::string& move) const;


    /*
        Brief: Returns the all CAPS version of input string

        s: The string being manipulated
    */
    std::string lowerToUpperString(const std::string& s) const;


    /*
        brief: Handles the logic for making a castle move. 0-0 for kingside 0-0-0 for queenside

        b: The board being asessed
        move: The specified castle move being played
    */
    void makeCastleMove(Board* b, std::string move);

    /*
        Brief: Undoes the specifed move type on the board without creating copies

        b: The board being asessed
    */
    void undoCastleMove(Board* b);
    void undoCaptureMove(Board* b);
    void undoRegularMove(Board* b);
    void undoPromotionMove(Board* b);
    void undoDoublePawnPushMove(Board* b);



    private:
    std::stack<undoMoveInfo> previousPositions;
    bool whiteTurn;





    
};