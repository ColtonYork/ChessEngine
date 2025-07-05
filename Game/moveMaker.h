#include <string>
#include <vector>
#include <stack>
#include "Board.h"
#include "undoMoveInfo.h"

class MoveMaker{
    public:

    /*
        Brief: move constructor.

        whiteToPlay: Determines who's turn it is. sets the whiteTurn private variable;
    */
    MoveMaker(bool whiteToPlay);


    /*
        Brief: Makes a move on the board without creating a new board

        move: The move being made
    */
    bool makeMove(const std::string& move);


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

        move: The specified castle move being played
    */
    bool makeCastleMove(std::string move);
    bool makeCaptureMove( std::string move);
    bool makeRegularMove(std::string move);
    bool makePromotionMove(std::string move);



    /*
        Brief: Undoes the specifed move type on the board without creating copies

    */
    void undoCastleMove(undoMoveInfo& info);
    void undoCaptureMove(undoMoveInfo& info);
    void undoRegularMove(undoMoveInfo& info);
    void undoPromotionMove(undoMoveInfo& info);


    /*
        Brief: Returns the move piece from a move string and returns the piece at that position

        move: The move string being parsed
    */
    Piece* getPieceFromMoveString(const std::string& move) const;
   
   
    /*
        Brief: Returns the integer array-index value of a board number

        number: the number to be converted
    */
    int numberToArrayIndex(char number) const;


    /*
        Brief: Returns the integer array-index value of a board letter

        letter: the letter to be converted
    */
    int letterToArrayIndex(char letter) const;


    /*
        Brief: Sets the board that the move maker object will track moves and make moves from

        b: The baord 
    */
    void setBoard(Board* b);




    private:
    std::stack<undoMoveInfo*> previousPositions;
    bool whiteTurn;
    Board* board;





    
};