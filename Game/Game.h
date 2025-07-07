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
        Brief: The main function to start and play game;                        
    */
    void playGame();

    
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

        note: This function was made mostly from ai help. Needed a GUI to be able to test things much easier.
    */
    void playGameSFML();

    



    private:
    Board* board;
    int movesPlayed;
    bool whiteTurn;
    MoveMaker moveMaker;
};