#include "Piece.h"

class Queen: public Piece{
    public:
     /*
        Queen constructor
        Brief: Calls the Piece class' constructor for row, column, and isWhite;

        r: The row to set the Rook to
        c: the column to set the Rook to
        isW: true if Queen IS white
    */
    Queen(unsigned char r, unsigned char c, bool isW);

    /*
        Virtual override from Piece class;
        brief: Checks if a particular Bishop move is legal

        toRow: The row that the Bishhop wants to move to
        toCol: The column that the Bishop wnats to move to
    */
    bool isLegalMove(unsigned char toRow, unsigned char toCol) const;



    private:




};