#include "Board.h"
#include "moveMaker.h"
#include <SFML/Graphics.hpp>
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

        letter: the letter to be converted
    */
    int letterToArrayIndex(char letter) const;


    /*
        Brief: Returns the integer array-index value of a board number

        number: the number to be converted
    */
    int numberToArrayIndex(char number) const;


    /*
        Brief: Tells the player to input a move and returns it. Also checks if the move format is valid
    */
    std::string getUserMove() const;


    /*
        Brief: returns true if user move format is correct

        move: the move to be checked
    */
    bool correctUserMoveFormat(std::string move) const;


    /*
        Brief: Returns the all CAPS version of input string

        s: the string to be converted
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

        move: the move to be verified
    */
    Board* verifyMove(std::string move) const;
    

    /*
        Brief: Checks if castling is legal when user castles. "0-0" for kingside | "0-0-0" for queen side.

        move: the move to be verified
    */
    Board* verifyCastleMove(std::string move) const;


    /*
        Brief: Determines if a pawn is being promoted in the move and promotes it. Return a new board pointer if the move is legal. Returns nullptr if the move is illegal.

        pawn: the pawn that will be potentially promoted
    */
    Board* verifyPromotionMove(Piece* pawn) const;


    /*
        Brief: returns TRUE if game is over. Checks for stalemante and checkamte.    
    */
    bool isGameOver() const;


    /*
        Brief: Used for training AI by playing games against itself.

        num: the number of games to play
    */
    void trainAISelfPlay(int numGames);


    /*
        brief: allows the user to play the game in a window
    */
    void playGameSFML();

    



    private:
    Board* board;
    int movesPlayed;
    bool whiteTurn;
    MoveMaker moveMaker;
};