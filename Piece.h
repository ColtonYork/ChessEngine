


class Piece {

    public:
    /*
        Brief: Piece constructor

        r: The row to set the piece to
        c: the column to set the piece to
        isW: true if piece IS white
    
    */
    Piece(unsigned char r, unsigned char c, bool isW);


    /*
        Brief: Parent calss destructor
    */
    virtual ~Piece() {}


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





