#include "Piece.h"

class Bishop: public Piece{
    public:
    /*
        Virtual override from Piece class;
        brief: Checks if a particular Bishop move is legal

        toRow: The row that the Bishhop wants to move to
        toCol: The column that the Bishop wnats to move to
    */
    bool isLegalMove(unsigned char toRow, unsigned char toCol) const;



    private:
    bool hasMoved;




};