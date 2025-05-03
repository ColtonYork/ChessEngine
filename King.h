#include "Piece.h"

class King: public Piece{
    public:
    /*
        Virtual override from Piece class;
        brief: Checks if a particular King move is legal

        toRow: The row that the King wants to move to
        toCol: The column that the King wnats to move to
    */
    bool isLegalMove(unsigned char toRow, unsigned char toCol) const;



    private:
    bool hasMoved;
    bool inCheck;




};