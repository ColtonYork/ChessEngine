#include "Piece.h"

class Pawn: public Piece{
    public:
     /*
        Pawn constructor
        Brief: Calls the Piece class' constructor for row, column, and isWhite;

        r: The row to set the Rook to
        c: the column to set the Rook to
        isW: true if Pawn IS white

        Personal Member hasMoved: set to false
    */
    Pawn(unsigned char r, unsigned char c, bool isW);

     /*
        Purely Virtual override from Piece Class
        Brief: Returns a cloned Pawn
    */
    Piece* clone() const;


    /*
        Purely Virtual override from Piece Class
        brief: Checks if a particular Pawn move is legal

        toRow: The row that the Pawn wants to move to
        toCol: The column that the Pawn wnats to move to
    */
    bool isLegalMove(unsigned char toRow, unsigned char toCol) const;



    private:
    bool hasMoved;




};