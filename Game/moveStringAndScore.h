#include "Board.h"
class Piece;

struct moveStringAndScore{
        
    std::string move = "";
    int moveQuickScore = 0;


    bool operator<(const moveStringAndScore &other) const{
        return moveQuickScore < other.moveQuickScore;
    }
};