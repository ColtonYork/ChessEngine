#include "Board.h"
class Piece;

struct moveResult{
    Board* board = nullptr;
    std::string move = "";
    int moveQuickScore = 0;

    bool operator<(const moveResult &other) const{
        return moveQuickScore < other.moveQuickScore;
    }
};