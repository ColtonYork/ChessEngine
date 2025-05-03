#include "Piece.h"

class Knight: public Piece{
    public:
     /*
        Knight constructor
        Brief: Calls the Piece class' constructor for row, column, and isWhite;

        r: The row to set the Rook to
        c: the column to set the Rook to
        isW: true if Knight IS white    
    */
    Knight(unsigned char r, unsigned char c, bool isW);
    /*
        Virtual override from Piece class;
        brief: Checks if a particular Knight move is legal

        toRow: The row that the Knight wants to move to
        toCol: The column that the Knight wnats to move to
    */
    bool isLegalMove(unsigned char toRow, unsigned char toCol) const;



    private:




};