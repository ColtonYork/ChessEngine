#include "Board.h"
#include <string>




class Game{

    public:
    /*
        Brief: initializes movesPlayed = 0 AND whiteTurn = true
    */
    Game();


    /*
        Brief: Makes sure the move is legal. Returns the new board if legal. Returns NULLPTR if move was illegal

        move: the move to be played
    */
    bool makeMove(std::string move);


    /*
        Brief: The main function to start and play game;                        
    */
    void playGame();


    /*
        Brief: Returns the integer array-index value of a board letter
    */
    int letterToArrayIndex(char letter) const;

    /*
        Brief: Returns the integer array-index value of a board number
    */
    int numberToArrayIndex(char number) const;


    /*
        Brief: Tells the player to input a move and returns it. Also checks if the move format is valid
    */
    std::string getUserMove() const;


    /*
        Brief: returns true if user move format is correct
    */
    bool correctUserMoveFormat(std::string move) const;


    /*
        Brief: Returns the all CAPS version of input string
    */
    std::string lowerToUpperString(std::string s) const;


    /*
        Brief: returns the Piece that the move is moving

        move: the move string being asessed
    */
    Piece* getPieceFromMoveString(std::string move) const;


    /*
        Brief: returns TRUE if the piece inputted is the same color as the current mover. Also checks if piece is nullptr

        piece: The piece being checked
    */
    bool isMoversPiece(Piece* piece) const;


    /*
        Brief verifies a specified move. Retuns the new board if the move is valid. Returns nullptr if move is invalid
    */
    Board* verifyMove(std::string move) const;

   



    private:
    Board* board;
    int movesPlayed;
    bool whiteTurn;
};