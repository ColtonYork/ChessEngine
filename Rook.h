#include "Piece.h"

class Rook: public Piece{
    public:
    /*
        Rook constructor
        Brief: Calls the Piece class' constructor for row, column, and isWhite;

        r: The row to set the Rook to
        c: the column to set the Rook to
        isW: true if Rook IS white

        Personal Member hasMoved: set to false
    */
    Rook(unsigned char r, unsigned char c, bool isW);

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