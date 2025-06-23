#include "Pieces/Piece.h"
#include "Pieces/Rook.h"
#include "Pieces/Bishop.h"
#include "Game/Board.h"
#include "Pieces/King.h"
#include "Pieces/Knight.h"
#include "Pieces/Pawn.h"
#include "Pieces/Queen.h"
#include "Game/Game.h"







int main(){
    //Game game;

    //game.playGame();

    // Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");

    // Board board2("8/8/8/4k3/8/8/4K3/8");

    // Board board3("r1bqkb1r/pppp1ppp/2n2n2/4p3/2B1P3/5Q2/PPPP1PPP/RNB1K2R");

    // Board board4("8/8/8/8/8/8/8/1k6");

    // Board board5("pppppppp/8/8/8/8/8/PPPPPPPP/RNBQKBNR");

    // Board board6("r3kb1r/ppp2ppp/2n1bn2/3pp3/2B1P3/2N2N2/PPPP1PPP/R1BQ1RK1");


    // board.displayBoard();
    // board2.displayBoard();
    // board3.displayBoard();
    // board4.displayBoard();
    // board5.displayBoard();
    // board6.displayBoard();

    Board board;

    board.displayBoard();

    board.generateBoardFromFENString("8/8/8/8/8/8/8/1k6");

    board.displayBoard();

    board.restartBoard();

    board.displayBoard();




    


    return 0;
}