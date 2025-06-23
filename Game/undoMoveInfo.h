#include "../Pieces/Piece.h"


struct undoMoveInfo {
    bool kingsideCastlemove;
    bool queensideCastleMove;
    bool captureMove;
    bool regularMove;
    bool promotionMove;
    bool doublePawnPushMove;

    int fromrow, fromcol, torow, tocol;
    Piece* movedPiece;
    Piece* capturedPiece;

    bool whiteCanCastleKingSide;
    bool whiteCanCastleQueenSide;
    bool blackCanCastleKingSide;
    bool blackCanCastleQueenSide;
};