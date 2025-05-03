


class Piece {

    public:
    /*
        Brief: Checks if a particular move is legal to make

        toRow: The row that the piece wants to move to
        toCol: The column that the piece wants to move to
    */
    virtual bool isLegalMove(unsigned char toRow, unsigned char toCol) const = 0;


    protected:
    unsigned char row;
    unsigned char col;
    bool isWhite;



};





