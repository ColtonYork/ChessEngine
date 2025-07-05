#include "../Pieces/Piece.h"


struct undoMoveInfo {
    ~undoMoveInfo() {
        if (capturedPiece != nullptr) 
            {
                delete capturedPiece;
            }
        if (promotedPawn != nullptr) 
            {
                delete promotedPawn;
            }
            
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
    Piece* promotedPawn = nullptr;


};