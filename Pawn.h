#include "Piece.h"

class Pawn: public Piece{
    public:
    /*
        Virtual override from Piece class;
        brief: Checks if a particular Pawn move is legal

        toRow: The row that the Pawn wants to move to
        toCol: The column that the Pawn wnats to move to
    */
    bool isLegalMove(unsigned char toRow, unsigned char toCol) const;



    private:
    bool hasMoved;




};