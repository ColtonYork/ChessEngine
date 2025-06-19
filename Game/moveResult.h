#include "Board.h"
#include "Piece.h"





struct moveResult{
    Board* board = nullptr;
    std::string move = "";
    int moveQuickScore = 0;

    bool operator<(const moveResult &other) const{
        return moveQuickScore < other.moveQuickScore;
    }
};