#include "../Pieces/Piece.h"


struct undoMoveInfo {
    ~undoMoveInfo() {
        delete capturedPiece;
    }

    bool whiteMove;

    bool kingsideCastleMove = 0;
    bool queensideCastleMove = 0;
    bool captureMove = 0;
    bool regularMove = 0;
    bool promotionMove = 0;

    int fromrow, fromcol, torow, tocol;
    Piece* movedPiece = nullptr;
    Piece* capturedPiece = nullptr;


};