#include "Piece.h"

class Rook: public Piece{
    public:
    /*
        Virtual override from Piece class;
        brief: Checks if a particular Rook move is legal

        toRow: The row that the Rook wants to move to
        toCol: The column that the Rook wnats to move to
    */
    bool isLegalMove(unsigned char toRow, unsigned char toCol) const;



    private:
    bool hasMoved;




};