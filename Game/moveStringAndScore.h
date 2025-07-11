#pragma once
#include <string>
class Piece;
class Board;

struct moveStringAndScore{
        
    std::string move = "";
    int moveQuickScore = 0;


    bool operator<(const moveStringAndScore &other) const{
        return moveQuickScore < other.moveQuickScore;
    }
};