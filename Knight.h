#include "Piece.h"

class Knight: public Piece{
    public:
    /*
        Virtual override from Piece class;
        brief: Checks if a particular Knight move is legal

        toRow: The row that the Knight wants to move to
        toCol: The column that the Knight wnats to move to
    */
    bool isLegalMove(unsigned char toRow, unsigned char toCol) const;



    private:
    bool hasMoved;




};