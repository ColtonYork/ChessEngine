#include "../Pieces/Piece.h"


struct undoMoveInfo {
    ~undoMoveInfo() {
        delete capturedPiece;
    }

    bool whiteMove;

    bool kingsideCastleMove = false;
    bool queensideCastleMove = false;
    bool captureMove = false;
    bool regularMove = false;
    bool promotionMove = false;

    bool hasMoved = false;

    int fromrow, fromcol, torow, tocol;
    Piece* movedPiece = nullptr;
    Piece* capturedPiece = nullptr;


};