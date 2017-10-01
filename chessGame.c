//
// Created by ׳�׳•׳¨׳™ ׳—׳‘׳™׳‘ on 05/09/2017.
//

//#include <ctype.h>
#include <ctype.h>
#include "chessGame.h"

void initializeBoard(SPChessGame* game){
    for (int i = 1; i < GAMESIZE - 1; i++) {
        for (int j = 0; j < GAMESIZE; j++) {
            if (i == 1) {
                game->gameBoard[i][j] = PAWNWHITE;
            } else if (i == GAMESIZE - 2) {
                game->gameBoard[i][j] = PAWNBLACK;
            } else { game->gameBoard[i][j] = BLANK; }
        }
    }
    game->gameBoard[0][0] = ROOKWHITE;
    game->gameBoard[0][1] = KNIGHTWHITE;
    game->gameBoard[0][2] = BISHOPWHITE;
    game->gameBoard[0][3] = QUEENWHITE;
    game->gameBoard[0][4] = KINGWHITE;
    game->gameBoard[0][5] = BISHOPWHITE;
    game->gameBoard[0][6] = KNIGHTWHITE;
    game->gameBoard[0][7] = ROOKWHITE;
    game->gameBoard[7][0] = ROOKBLACK;
    game->gameBoard[7][1] = KNIGHTBLACK;
    game->gameBoard[7][2] = BISHOPBLACK;
    game->gameBoard[7][3] = QUEENBLACK;
    game->gameBoard[7][4] = KINGBLACK;
    game->gameBoard[7][5] = BISHOPBLACK;
    game->gameBoard[7][6] = KNIGHTBLACK;
    game->gameBoard[7][7] = ROOKBLACK;

    game->whiteKing.column = 4;
    game->whiteKing.row = 0;
    game->blackKing.column = 4;
    game->blackKing.row = 7;

    game->whiteLeftCastling = 1;
    game->whiteRightCastling = 1;
    game->blackLeftCastling = 1;
    game->blackRightCastling = 1;
}


SPChessGame *chessGameCreate() {
    SPChessGame *game = (SPChessGame *) malloc(sizeof(SPChessGame));
    if (game != NULL) {
        game->lastMoves = spArrayListCreate(HISTORYSIZE);
        if (game->lastMoves != NULL) {
            game->userColor = 1;
            game->currentPlayer = 1;
            game->difficulty = 2;
            game->state = 0;
            game->gameMode = 1;

            initializeBoard(game);

            return game;
        }
        chessGameDestroy(&game);
    } else {
        printf("Error: game create malloc has failed");
    }
    return NULL;
}





SPChessGame *chessGameCopy(SPChessGame *src) {
    if (src != NULL) {
        SPChessGame *game = (SPChessGame *) malloc(sizeof(SPChessGame));
        if (game != NULL) {
            game->lastMoves = spArrayListCopy(src->lastMoves);
            if (game->lastMoves != NULL) {
                game->userColor = src->userColor;
                game->difficulty = src->difficulty;
                game->state = src->state;
                game->gameMode = src->gameMode;
                game->currentPlayer = src->currentPlayer;
                game->whiteKing.column = src->whiteKing.column;
                game->whiteKing.row = src->whiteKing.row;
                game->blackKing.column = src->blackKing.column;
                game->blackKing.row = src->blackKing.row;
                game->whiteLeftCastling = src->whiteLeftCastling;
                game->whiteRightCastling = src->whiteRightCastling;
                game->blackLeftCastling = src->blackLeftCastling;
                game->blackRightCastling = src->blackRightCastling;

                for (int i = 0; i < GAMESIZE; i++) {
                    for (int j = 0; j < GAMESIZE; j++) {
                        game->gameBoard[i][j] = src->gameBoard[i][j];
                    }
                }
                return game;
            }
            chessGameDestroy(&game);
        } else {
            printf("Error: copy malloc has failed");
        }
    }
    return NULL;
}






void chessGameDestroy(SPChessGame** src) {
    if (*src != NULL) {
        if ((*src)->lastMoves != NULL){
            spArrayListDestroy(&((*src)->lastMoves));
        }
        free(*src);
        *src = NULL;
    }
    return;
}



char whosThere(SPChessGame *src, int row, int col) {
    if (col < 0 || col > 7 || row < 0 || row > 7) {
        return '\0';
    }
    return src->gameBoard[row][col];
}


position getKingPosition(SPChessGame *src, int color) {
    if (color == 1){ // white king requested
        return src->whiteKing;
    }
    else {
        return src->blackKing;
    }
}


int getColor(char soldier) {
    switch (soldier) {
        case PAWNWHITE:
        case BISHOPWHITE:
        case ROOKWHITE:
        case KNIGHTWHITE:
        case QUEENWHITE:
        case KINGWHITE:
            return 1;
        case PAWNBLACK:
        case BISHOPBLACK:
        case ROOKBLACK:
        case KNIGHTBLACK:
        case QUEENBLACK:
        case KINGBLACK:
            return 0;
        default:
            return -1;
    }
}


bool pawnsThreatSoldier(SPChessGame *src, int color, position soldier) {
    char pawn = PAWNBLACK;
    if (color == 0) {  // soldier is black
        pawn = PAWNWHITE;
        if ((whosThere(src, soldier.row - 1, soldier.column - 1) == pawn) ||
            (whosThere(src, soldier.row - 1, soldier.column + 1) == pawn)) {
            return true;
        }
    }
    //king is white
    if ((whosThere(src, soldier.row + 1, soldier.column - 1) == pawn) ||
        (whosThere(src, soldier.row + 1, soldier.column + 1) == pawn)) {
        return true;
    }
    return false;
}


bool knightsThreatSoldier(SPChessGame *src, int color, position soldier) {
    char knight = KNIGHTBLACK;   //soldier is white
    if (color == 0) {           // soldier is black
        knight = KNIGHTWHITE;
    }
    if ((whosThere(src, soldier.row - 2, soldier.column - 1) == knight) ||
        (whosThere(src, soldier.row - 2, soldier.column + 1) == knight)
        || (whosThere(src, soldier.row + 2, soldier.column - 1) == knight) ||
        (whosThere(src, soldier.row + 2, soldier.column + 1) == knight)
        || (whosThere(src, soldier.row + 1, soldier.column - 2) == knight) ||
        (whosThere(src, soldier.row + 1, soldier.column + 2) == knight)
        || (whosThere(src, soldier.row - 1, soldier.column - 2) == knight) ||
        (whosThere(src, soldier.row - 1, soldier.column + 2) == knight)) {
        return true;
    }
    return false;
}






bool kingThreatensSoldier(SPChessGame *src, int color, position soldier) {
    char opKing = KINGBLACK;   //our king is white
    if (color == 0) {           // our king is black
        opKing = KINGWHITE;
    }
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (whosThere(src, soldier.row + i, soldier.column + j) == opKing) {
                return true;
            }
        }
    }
    return false;
}



bool checkLane(SPChessGame *src, int x, int y, position soldier, char queen, char other){
    int row = soldier.row;
    int col = soldier.column;
    char tmp;
    while (row < GAMESIZE && row > -1 && col < GAMESIZE && col > -1) {
        row += y;
        col += x;
        tmp = whosThere(src, row, col);
        if (tmp == queen || tmp == other) { return true; }
        if (tmp != BLANK) { break; }
    }
    return false;
}


bool QRBThreatensSoldier(SPChessGame *src, int color, position soldier) {
    char queen = QUEENBLACK;   //our soldier is white
    char bishop = BISHOPBLACK;
    char rook = ROOKBLACK;
    if (color == 0) {           // our soldier is black
        queen = QUEENWHITE;
        bishop = BISHOPWHITE;
        rook = ROOKWHITE;
    }
    if (checkLane(src, 0, 1, soldier, queen, rook)) { return true; }
    if (checkLane(src, 1, 0, soldier, queen, rook)) { return true; }
    if (checkLane(src, -1, 0, soldier, queen, rook)) { return true; }
    if (checkLane(src, 0, -1, soldier, queen, rook)) { return true; }
    if (checkLane(src, 1, 1, soldier, queen, bishop)) { return true; }
    if (checkLane(src, -1, -1, soldier, queen, bishop)) { return true; }
    if (checkLane(src, -1, 1, soldier, queen, bishop)) { return true; }
    if (checkLane(src, 1, -1, soldier, queen, bishop)) { return true; }
    return false;
}


bool isTheSoldierThreatened(SPChessGame *src, int color , position soldier){
    if (!posOnBoard(soldier)) { return false;}
    if (pawnsThreatSoldier(src, color, soldier) || knightsThreatSoldier(src, color, soldier)
        || kingThreatensSoldier(src, color, soldier) || QRBThreatensSoldier(src, color, soldier)){
        return true;
    }
    return false;
}

bool isTheKingThreatened(SPChessGame *src, int color) {
    position kingPos = getKingPosition(src, color);
    return isTheSoldierThreatened(src, color, kingPos);
}




bool isMoveRiskTheKing(SPChessGame* src, position origin , position dest){
    if (!src){ return false;}
    char tmp = src->gameBoard[dest.row][dest.column];
    if(src->gameBoard[origin.row][origin.column] == KINGBLACK){
        src->blackKing = dest;
    }
    if(src->gameBoard[origin.row][origin.column] == KINGWHITE){
        src->whiteKing = dest;
    }
    src->gameBoard[dest.row][dest.column] = src->gameBoard[origin.row][origin.column];
    src->gameBoard[origin.row][origin.column] = BLANK;
    bool result = isTheKingThreatened(src, src->currentPlayer);
    src->gameBoard[origin.row][origin.column] = src->gameBoard[dest.row][dest.column];
    src->gameBoard[dest.row][dest.column] = tmp;
    if(src->gameBoard[origin.row][origin.column] == KINGBLACK){
        src->blackKing = origin;
    }
    if(src->gameBoard[origin.row][origin.column] == KINGWHITE){
        src->whiteKing = origin;
    }
    return result;
}




bool posOnBoard (position pos){
    if (pos.column > GAMESIZE-1 || pos.column < 0 || pos.row < 0 ||  pos.row > GAMESIZE-1){return false;}
    return true;
}

bool isBlack(char soldier){
    if (soldier > 64 && soldier < 91){ return true;}
    return false;
}

bool isWhite(char soldier){
    if (soldier > 96 && soldier < 123){ return true;}
    return false;
}

bool pawnValidMove(SPChessGame* src, position origin , position dest){
    int direction = src->currentPlayer == 1 ? 1 : -1;
    if (origin.column == dest.column && dest.row == (origin.row + direction) && src->gameBoard[dest.row][dest.column] == BLANK){ return true;} // moving one step forward
    if (origin.column == dest.column && direction == 1 && origin.row == 1 && dest.row == (origin.row + 2*direction)
        && src->gameBoard[dest.row][dest.column] == BLANK && src->gameBoard[origin.row + direction][origin.column] == BLANK){ return true;} // moving two steps forward - white
    if (origin.column == dest.column && direction == -1 && origin.row == 6 && dest.row == (origin.row + 2*direction)
        && src->gameBoard[dest.row][dest.column] == BLANK && src->gameBoard[origin.row  + direction][origin.column] == BLANK){ return true;} // moving two steps forward - black
    if (direction == 1){
        if ((origin.column == dest.column-1 || origin.column == dest.column+1)
            && dest.row == (origin.row + direction) && isBlack(src->gameBoard[dest.row][dest.column])){ return true;} // eating - white
    }
    else{
        if ((origin.column == dest.column-1 || origin.column == dest.column+1)
            && dest.row == (origin.row + direction) && isWhite(src->gameBoard[dest.row][dest.column])){ return true;} // eating - black
    }
    return false;
}


bool knightValidMove(position origin , position dest){
    if (!((abs(origin.row - dest.row) == 2 && abs(origin.column - dest.column) == 1)
        || (abs(origin.row - dest.row) == 1 && abs(origin.column - dest.column) == 2))){
        return false;
    }
    return true;
}

bool kingValidMove(position origin , position dest){
    if (abs(dest.column - origin.column) > 1 || abs(dest.row - origin.row) > 1){
        return false;
    }
    return true;
}


bool rookValidMove(SPChessGame* src, position origin , position dest){
    int low;
    int high;
    if (origin.column == dest.column){
        low = mini(origin.row , dest.row);
        high = maxi(origin.row , dest.row);
        for (int i = low+1; i < high; i++){
            if (src->gameBoard[i][dest.column] != BLANK){return false;}
        }
    }
    else if (origin.row == dest.row){
        low = mini(origin.column , dest.column);
        high = maxi(origin.column , dest.column);
        for (int i = low+1; i < high; i++){
            if (src->gameBoard[dest.row][i] != BLANK){return false;}
        }
    }
    else{
        return false;
    }
    return true;
}

bool bishopValidMove(SPChessGame* src, position origin , position dest) {
    if (abs(dest.column - origin.column) != abs(dest.row - origin.row)) { return false; }
    int dx, dy;
    dx = dest.column > origin.column ? 1 : -1;
    dy = dest.row > origin.row ? 1 : -1;
    int row = origin.row + dy, col = origin.column + dx;
    while (row != dest.row){
        if (src->gameBoard[row][col] != BLANK){ return false;}
        row += dy;
        col += dx;
    }
    return true;
}

bool queenValidMove(SPChessGame* src, position origin , position dest){
    return  (rookValidMove(src, origin, dest) || (bishopValidMove(src, origin, dest)));
}


SP_CHESS_GAME_MESSAGE isValidMove(SPChessGame* src, position origin , position dest){
    if (!src) {
        return SP_CHESS_GAME_INVALID_ARGUMENT;
    }
    if (!posOnBoard(origin) || !posOnBoard(dest)) {
        return SP_CHESS_GAME_INVALID_POSITION_ON_BOARD;
    }
    if ((origin.row == dest.row && origin.column == dest.column)) { return SP_CHESS_GAME_ILLEGAL_MOVE; }

    if (src->currentPlayer == 1 && !isWhite(src->gameBoard[origin.row][origin.column])) {
        return SP_CHESS_GAME_SOLDIER_MISMATCH;
    }
    if (src->currentPlayer == 0 && !isBlack(src->gameBoard[origin.row][origin.column])) {
        return SP_CHESS_GAME_SOLDIER_MISMATCH;
    }
    if ((src->currentPlayer == 1 && isWhite(src->gameBoard[dest.row][dest.column])) ||
            (src->currentPlayer == 0 && isBlack(src->gameBoard[dest.row][dest.column]))){
        return SP_CHESS_GAME_ILLEGAL_MOVE;
    }
    char soldier = (src->gameBoard[origin.row][origin.column]);
    bool flag = true;
    if (soldier == PAWNWHITE || soldier == PAWNBLACK){ flag = pawnValidMove(src, origin, dest);}
    else if (soldier == KNIGHTBLACK || soldier == KNIGHTWHITE) { flag = knightValidMove(origin, dest);}
    else if (soldier == KINGBLACK || soldier == KINGWHITE) { flag = kingValidMove(origin, dest);}
    else if (soldier == ROOKBLACK || soldier == ROOKWHITE) { flag = rookValidMove(src, origin, dest);}
    else if (soldier == BISHOPBLACK || soldier == BISHOPWHITE) { flag = bishopValidMove(src, origin, dest);}
    else if (soldier == QUEENBLACK || soldier == QUEENWHITE) { flag = queenValidMove(src, origin, dest);}
    if (!flag || isMoveRiskTheKing(src, origin, dest)){
        return SP_CHESS_GAME_ILLEGAL_MOVE;
    }
    return SP_CHESS_GAME_SUCCESS;
}

void pawnPromotion (SPChessGame* src, action move, int isMini) {
    if (!src) { return; }
    char piece = BLANK;
    if ((src->gameMode == 1 && src->currentPlayer != src->userColor) || isMini == 1){
        piece = QUEENWHITE;
    }
    else {
        char buffer[SP_MAX_LINE_LENGTH];
        printf("Pawn promotion - please replace the pawn by queen, rook, knight, bishop or pawn:\n");
        while (piece == BLANK) {
            fgets(buffer, SP_MAX_LINE_LENGTH, stdin);
            piece = getPiece(buffer);
        }
    }
    if (move.piece == PAWNBLACK) {
        src->gameBoard[move.current.row][move.current.column] = (char)(toupper(piece));
    }
    if (move.piece == PAWNWHITE) {
        src->gameBoard[move.current.row][move.current.column] = piece;
    }
}



SP_CHESS_GAME_MESSAGE chessGameSetMove(SPChessGame* src, position origin , position dest, int isMini, int isGui) {
    SP_CHESS_GAME_MESSAGE msg = isValidMove(src, origin, dest);
    if (msg != SP_CHESS_GAME_SUCCESS){
        return msg;
    }
    char soldier = (src->gameBoard[origin.row][origin.column]);
    if (soldier == KINGBLACK){
        src->blackKing.row = dest.row;
        src->blackKing.column = dest.column;
        src->blackLeftCastling = src->blackRightCastling = 0;
    }
    else if (soldier == KINGWHITE){
        src->whiteKing.row = dest.row;
        src->whiteKing.column = dest.column;
        src->whiteLeftCastling = src->whiteRightCastling = 0;
    }
    if (origin.row == 0){
    	if (origin.column == 0){
    		src->whiteLeftCastling = 0;
    	}
    	else if (origin.column == 7){
    		src->whiteRightCastling = 0;
    	}
    }
    else if (origin.row == 7){
    	if (origin.column == 0){
    		src->blackLeftCastling = 0;
    	}
    	else if (origin.column == 7){
    		src->blackRightCastling = 0;
    	}
    } 
    char captured = src->gameBoard[dest.row][dest.column];
    src->gameBoard[dest.row][dest.column] = soldier;
    src->gameBoard[origin.row][origin.column] = BLANK;
    action move;
    move.current = dest;
    move.prev = origin;
    move.captured = captured;
    move.piece = soldier;
    move.castling = SP_CHESS_NO_CASTLING;

    if ((move.prev.row == 0 && move.prev.column == 4) | (move.current.row == 0 && move.current.column == 4)) {
        if (src->whiteLeftCastling){ move.isLWCastlingDeactivated = 1; }
        if (src->whiteRightCastling){ move.isRWCastlingDeactivated = 1; }
    }
    else if (src->whiteLeftCastling && ((move.prev.row == 0 && move.prev.column == 0) || (move.current.row == 0 && move.current.column == 0))) { move.isLWCastlingDeactivated = 1; }
    else if (src->whiteRightCastling && ((move.prev.row == 0 && move.prev.column == 7) || (move.current.row == 0 && move.current.column == 7))) { move.isRWCastlingDeactivated = 1; }
    else if ((move.prev.row == 7 && move.prev.column == 4) || (move.current.row == 7 && move.current.column == 4)){
        if (src->blackLeftCastling){ move.isLBCastlingDeactivated = 1; }
        if (src->blackRightCastling){ move.isRBCastlingDeactivated = 1; }
    }
    else if (src->blackLeftCastling && ((move.prev.row == 7 && move.prev.column == 0) || (move.current.row == 7 && move.current.column == 0))) { move.isLBCastlingDeactivated = 1; }
    else if (src->blackRightCastling && ((move.prev.row == 7 && move.prev.column == 7) || (move.current.row == 7 && move.current.column == 7))) { move.isRBCastlingDeactivated = 1; }

    gameSpArrayListAdd(src->lastMoves, move);
    if (isGui == 0 && ((soldier == PAWNBLACK && move.current.row == 0) || (soldier == PAWNWHITE && move.current.row == 7))) {
        pawnPromotion(src, move, isMini);
    }
    src->currentPlayer = 1 - src->currentPlayer;
    return SP_CHESS_GAME_SUCCESS;
}


void regularUndo(SPChessGame* src , action lastMove){
    if (lastMove.piece == KINGBLACK) {
        src->blackKing.row = lastMove.prev.row;
        src->blackKing.column = lastMove.prev.column;
    } else if (lastMove.piece == KINGWHITE) {
        src->whiteKing.row = lastMove.prev.row;
        src->whiteKing.column = lastMove.prev.column;
    }
    src->gameBoard[lastMove.prev.row][lastMove.prev.column] = lastMove.piece;
    src->gameBoard[lastMove.current.row][lastMove.current.column] = lastMove.captured;
}

void castlingUndo(SPChessGame* src , action lastMove){
    switch (lastMove.castling) {
        case SP_CHESS_WHITE_LEFT_CASTLING:
//            src->whiteLeftCastling = 1;
            src->gameBoard[0][0] = ROOKWHITE;
            src->gameBoard[0][4] = KINGWHITE;
            src->gameBoard[0][2] = src->gameBoard[0][3] = BLANK;
            src->whiteKing.row = 0;
            src->whiteKing.column = 4;
            break;
        case SP_CHESS_WHITE_RIGHT_CASTLING:
//            src->whiteRightCastling = 1;
            src->gameBoard[0][7] = ROOKWHITE;
            src->gameBoard[0][4] = KINGWHITE;
            src->gameBoard[0][5] = src->gameBoard[0][6] = BLANK;
            src->whiteKing.row = 0;
            src->whiteKing.column = 4;
            break;
        case SP_CHESS_WHITE_BOTH_CASTLINGS:
//            src->whiteLeftCastling = src->whiteRightCastling = 1;
            src->whiteKing.row = 0;
            src->whiteKing.column = 4;
            src->gameBoard[0][4] = KINGWHITE;
            if (lastMove.prev.row == 0){                // left castling was done
                src->gameBoard[0][0] = ROOKWHITE;
                src->gameBoard[0][2] = src->gameBoard[0][3] = BLANK;
            }
            else {                                      // right castling was done
                src->gameBoard[0][7] = ROOKWHITE;
                src->gameBoard[0][5] = src->gameBoard[0][6] = BLANK;
            }
            break;
        case SP_CHESS_BLACK_LEFT_CASTLING:
//            src->blackLeftCastling = 1;
            src->gameBoard[7][0] = ROOKBLACK;
            src->gameBoard[7][4] = KINGBLACK;
            src->gameBoard[7][2] = src->gameBoard[7][3] = BLANK;
            src->whiteKing.row = 7;
            src->whiteKing.column = 4;
            break;
        case SP_CHESS_BLACK_RIGHT_CASTLING:
//            src->blackRightCastling = 1;
            src->gameBoard[7][7] = ROOKBLACK;
            src->gameBoard[7][4] = KINGBLACK;
            src->gameBoard[7][5] = src->gameBoard[7][6] = BLANK;
            src->whiteKing.row = 7;
            src->whiteKing.column = 4;
            break;
        case SP_CHESS_BLACK_BOTH_CASTLINGS:
//            src->blackLeftCastling = src->blackRightCastling = 1;
            src->whiteKing.row = 7;
            src->whiteKing.column = 4;
            src->gameBoard[7][4] = KINGBLACK;
            if (lastMove.prev.row == 0){                    // left castling was done
                src->gameBoard[7][0] = ROOKBLACK;
                src->gameBoard[7][2] = src->gameBoard[7][3] = BLANK;
            }
            else {                                          // right castling was done
                src->gameBoard[7][7] = ROOKBLACK;
                src->gameBoard[7][5] = src->gameBoard[7][6] = BLANK;
            }
            break;
        default:
            break;
    }
}

int isWhiteLeftCastlingValid(SPChessGame *src){
    if(!src) { return 0; }
    if(src->whiteLeftCastling == 0 || src->gameBoard[0][1] != BLANK || src->gameBoard[0][2] != BLANK || src->gameBoard[0][3] != BLANK ||
       src->gameBoard[0][4] != KINGWHITE  || src->gameBoard[0][0] != ROOKWHITE){
        return 0;
    }
    int res = 1;
    position tmpKingsPos = src->whiteKing;
    src->whiteKing.row = 0;
    src->whiteKing.column = 2;
    if (isTheKingThreatened(src , 1)){
        res = 0;
    }
    src->whiteKing = tmpKingsPos;
    return res;
}


int isWhiteRightCastlingValid(SPChessGame *src){
    if(!src) { return 0; }
    if(src->whiteRightCastling == 0 || src->gameBoard[0][5] != BLANK || src->gameBoard[0][6] != BLANK ||
       src->gameBoard[0][4] != KINGWHITE  || src->gameBoard[0][7] != ROOKWHITE){
        return 0;
    }

    int res = 1;
    position tmpKingsPos = src->whiteKing;
    src->whiteKing.row = 0;
    src->whiteKing.column = 6;
    if (isTheKingThreatened(src , 1)){
        res = 0;
    }
    src->whiteKing = tmpKingsPos;
    return res;
}


int isBlackLeftCastlingValid(SPChessGame *src){
    if(!src) { return 0; }
    if(src->blackLeftCastling == 0 || src->gameBoard[7][1] != BLANK || src->gameBoard[7][2] != BLANK || src->gameBoard[7][3] != BLANK ||
       src->gameBoard[7][4] != KINGBLACK  || src->gameBoard[7][0] != ROOKBLACK){
        return 0;
    }
    int res = 1;
    position tmpKingsPos = src->blackKing;
    src->blackKing.row = 7;
    src->blackKing.column = 2;
    if (isTheKingThreatened(src , 0)){
        res = 0;
    }
    src->blackKing = tmpKingsPos;
    return res;
}


int isBlackRightCastlingValid(SPChessGame *src){
    if(!src) { return 0; }
    if(src->blackRightCastling == 0 || src->gameBoard[7][5] != BLANK || src->gameBoard[7][6] != BLANK ||
       src->gameBoard[7][4] != KINGBLACK  || src->gameBoard[7][7] != ROOKBLACK){
        return 0;
    }
    int res = 1;
    position tmpKingsPos = src->blackKing;
    src->blackKing.row = 7;
    src->blackKing.column = 6;
    if (isTheKingThreatened(src , 0)){
        res = 0;
    }
    src->blackKing = tmpKingsPos;
    return res;
}


void executeWhiteLeftCastling(SPChessGame *src){
    if(!src) { return; }
    src->gameBoard[0][0] = src->gameBoard[0][4] = BLANK;
    src->gameBoard[0][2] = KINGWHITE;
    src->gameBoard[0][3] = ROOKWHITE;
    src->whiteKing.column = 2;
    action move;
    move.prev.row = 0;
    move.prev.column = 0;
    move.current.row = 0;
    move.current.column = 3;
    move.captured = BLANK;
    move.piece = ROOKWHITE;
    if (src->whiteLeftCastling == 1){ move.castling = SP_CHESS_WHITE_BOTH_CASTLINGS; }
    else { move.castling = SP_CHESS_WHITE_LEFT_CASTLING; }
    spArrayListAddFirst(src->lastMoves, move);
    src->whiteLeftCastling = src->whiteRightCastling = 0;
    src->currentPlayer = 1 - src->currentPlayer;
    return;
}


void executeWhiteRightCastling(SPChessGame *src){
    if(!src) { return; }
    src->gameBoard[0][7] = src->gameBoard[0][4] = BLANK;
    src->gameBoard[0][6] = KINGWHITE;
    src->gameBoard[0][5] = ROOKWHITE;
    src->whiteKing.column = 6;
    action move;
    move.prev.row = 0;
    move.prev.column = 7;
    move.current.row = 0;
    move.current.column = 5;
    move.captured = BLANK;
    move.piece = ROOKWHITE;
    if (src->whiteLeftCastling == 1){ move.castling = SP_CHESS_WHITE_BOTH_CASTLINGS; }
    else { move.castling = SP_CHESS_WHITE_RIGHT_CASTLING; }
    spArrayListAddFirst(src->lastMoves, move);
    src->whiteLeftCastling = src->whiteRightCastling = 0;
    src->currentPlayer = 1 - src->currentPlayer;
    return;
}


void executeBlackLeftCastling(SPChessGame *src){
    if(!src) { return; }
    src->gameBoard[7][0] = src->gameBoard[7][4] = BLANK;
    src->gameBoard[7][2] = KINGBLACK;
    src->gameBoard[7][3] = ROOKBLACK;
    src->blackKing.column = 2;
    action move;
    move.prev.row = 7;
    move.prev.column = 0;
    move.current.row = 7;
    move.current.column = 3;
    move.captured = BLANK;
    move.piece = ROOKBLACK;
    if (src->blackRightCastling == 1){ move.castling = SP_CHESS_BLACK_BOTH_CASTLINGS; }
    else { move.castling = SP_CHESS_BLACK_LEFT_CASTLING; }
    spArrayListAddFirst(src->lastMoves, move);
    src->blackLeftCastling = src->blackRightCastling = 0;
    src->currentPlayer = 1 - src->currentPlayer;
    return;
}


void executeBlackRightCastling(SPChessGame *src){
    if(!src) { return; }
    src->gameBoard[7][7] = src->gameBoard[7][4] = BLANK;
    src->gameBoard[7][6] = KINGBLACK;
    src->gameBoard[7][5] = ROOKBLACK;
    src->blackKing.column = 6;
    action move;
    move.prev.row = 7;
    move.prev.column = 7;
    move.current.row = 7;
    move.current.column = 5;
    move.captured = BLANK;
    move.piece = ROOKBLACK;
    if (src->blackLeftCastling == 1){ move.castling = SP_CHESS_BLACK_BOTH_CASTLINGS; }
    else { move.castling = SP_CHESS_BLACK_RIGHT_CASTLING; }
    spArrayListAddFirst(src->lastMoves, move);
    src->blackLeftCastling = src->blackRightCastling = 0;
    src->currentPlayer = 1 - src->currentPlayer;
    return;
}


int executeCastling(SPChessGame *src, SPCommand command){
    if (!src) { return 0; }
    if (!posOnBoard(command.source)) {
        printf("Invalid position on the board\n");
        return 0;
    }
    else if ((src->currentPlayer == 1 && !isWhite(src->gameBoard[command.source.row][command.source.column])) ||
             (src->currentPlayer == 0 && !isBlack(src->gameBoard[command.source.row][command.source.column]))) {
        printf("The specified position does not contain your piece\n");
        return 0;
    }
    if (src->gameBoard[command.source.row][command.source.column] != ROOKWHITE &&
        src->gameBoard[command.source.row][command.source.column]!= ROOKBLACK){
        printf("Wrong position for a rook\n");
        return 0;
    }
    if (command.source.row == 0 && command.source.column == 0){
        if (isWhiteLeftCastlingValid(src)){
            executeWhiteLeftCastling(src);
            return 1;
        }
        else {
            printf("Illegal castling move\n");
            return 0;
        }
    }
    else if (command.source.row == 0 && command.source.column == 7){
        if (isWhiteRightCastlingValid(src)){
            executeWhiteRightCastling(src);
            return 1;
        }
        else {
            printf("Illegal castling move\n");
            return 0;
        }
    }
    else if (command.source.row == 7 && command.source.column == 0){
        if (isBlackLeftCastlingValid(src)){
            executeBlackLeftCastling(src);
            return 1;
        }
        else {
            printf("Illegal castling move\n");
            return 0;
        }
    }
    else if (command.source.row == 7 && command.source.column == 7){
        if (isBlackRightCastlingValid(src)){
            executeBlackRightCastling(src);
            return 1;
        }
        else {
            printf("Illegal castling move\n");
            return 0;
        }
    }
    else{
        printf("Wrong position for a rook\n");
        return 0;
    }
}

int executeCastlingMiniMax(SPChessGame *src, position origin, position dst){
    SPCommand cmd;
    cmd.source = origin;
    cmd.destination = dst;
    return executeCastling(src, cmd);
}



SP_CHESS_GAME_MESSAGE chessGameUndoPrevMove(SPChessGame* src){
    if (!src){
        return SP_CHESS_GAME_INVALID_ARGUMENT;
    }
    if ((spArrayListIsEmpty(src->lastMoves))){
        return SP_CHESS_GAME_NO_HISTORY;
    }
    action lastMove = *(spArrayListGetFirst(src->lastMoves));
    spArrayListRemoveFirst(src->lastMoves);
    if (lastMove.castling == SP_CHESS_NO_CASTLING) {
        regularUndo(src, lastMove);
    }
    else {
        castlingUndo(src, lastMove);
    }
    if (lastMove.isLWCastlingDeactivated == 1) { src->whiteLeftCastling = 1; }
    if (lastMove.isRWCastlingDeactivated == 1) { src->whiteRightCastling = 1; }
    if (lastMove.isLBCastlingDeactivated == 1) { src->blackLeftCastling = 1; }
    if (lastMove.isRBCastlingDeactivated == 1) { src->blackRightCastling = 1; }
    src->currentPlayer = 1 - src->currentPlayer;
    return SP_CHESS_GAME_SUCCESS;
}




SP_CHESS_GAME_MESSAGE chessGamePrintBoard(SPChessGame *src) {
    if (!src) {
        return SP_CHESS_GAME_INVALID_ARGUMENT;
    }
    for (int i = GAMESIZE; i > 0; i--) {
        printf("%d| ", i);
        for (int j = 0; j < GAMESIZE; j++) {
            printf("%c ", src->gameBoard[i - 1][j]);
        }
        printf("|\n");
    }
    printf("  -----------------\n");
    printf("  ");
    for (int i = 0; i < GAMESIZE; i++) {
        printf(" %c", (i + 65));
    }
    printf("\n");
    return SP_CHESS_GAME_SUCCESS;
}


SPArrayList* getMovesForSoldier(SPChessGame* src, int row, int col){
    position soldierPos;
    soldierPos.column = col;
    soldierPos.row = row;
    if (!src || !posOnBoard(soldierPos) || src->gameBoard[row][col] == BLANK){ return NULL;}
    SPArrayList *possibleMoves = spArrayListCreate(GAMESIZE*GAMESIZE);
    if (possibleMoves == NULL){ return NULL;}
    position tmpDest;
    for (int i = 0; i < GAMESIZE; i++){
        for (int j = 0; j < GAMESIZE; j++){
            tmpDest.row = i;
            tmpDest.column = j;
            if (isValidMove(src, soldierPos, tmpDest) == SP_CHESS_GAME_SUCCESS){
                spArrayListAddLast(possibleMoves,generateAction(soldierPos, tmpDest, whosThere(src, i, j), src->gameBoard[row][col], SP_CHESS_NO_CASTLING, 0, 0, 0, 0));
            }
        }
    }
    if (isWhiteLeftCastlingValid(src) && src->gameBoard[0][0] == ROOKWHITE && src->gameBoard[0][4] == KINGWHITE){
        soldierPos.row = 0;
        soldierPos.column = 0;
        tmpDest.row = 0;
        tmpDest.column = 4;
        if (row == 0 && col == 0){
            spArrayListAddLast(possibleMoves,generateAction(soldierPos, tmpDest, BLANK, ROOKWHITE, SP_CHESS_WHITE_LEFT_CASTLING, 1, src->whiteRightCastling, 0, 0));
        } else if (row == 0 && col == 4) {
            spArrayListAddLast(possibleMoves, generateAction(tmpDest, soldierPos, BLANK, KINGWHITE, SP_CHESS_WHITE_LEFT_CASTLING, 1, src->whiteRightCastling, 0, 0));
        }
    }
    else if (isWhiteRightCastlingValid(src) && src->gameBoard[0][7] == ROOKWHITE && src->gameBoard[0][4] == KINGWHITE){
        soldierPos.row = 0;
        soldierPos.column = 7;
        tmpDest.row = 0;
        tmpDest.column = 4;
        if (row == 0 && col == 7){
            spArrayListAddLast(possibleMoves,generateAction(soldierPos, tmpDest, BLANK, ROOKWHITE, SP_CHESS_WHITE_RIGHT_CASTLING, 1, src->whiteLeftCastling, 0, 0));
        } else if (row == 0 && col == 4) {
            spArrayListAddLast(possibleMoves, generateAction(tmpDest, soldierPos, BLANK, KINGWHITE, SP_CHESS_WHITE_RIGHT_CASTLING, 1, src->whiteLeftCastling, 0, 0));
        }
    }
    else if (isBlackLeftCastlingValid(src) && src->gameBoard[7][0] == ROOKBLACK && src->gameBoard[7][4] == KINGBLACK){
        soldierPos.row = 7;
        soldierPos.column = 0;
        tmpDest.row = 7;
        tmpDest.column = 4;
        if (row == 7 && col == 0){
            spArrayListAddLast(possibleMoves,generateAction(soldierPos, tmpDest, BLANK, ROOKBLACK, SP_CHESS_BLACK_LEFT_CASTLING, 0, 0, 1, src->blackRightCastling));
        } else if (row == 7 && col == 4) {
            spArrayListAddLast(possibleMoves, generateAction(tmpDest, soldierPos, BLANK, KINGBLACK, SP_CHESS_BLACK_LEFT_CASTLING, 0, 0, 1, src->blackRightCastling));
        }
    }
    else if (isBlackRightCastlingValid(src) && src->gameBoard[7][7] == ROOKWHITE && src->gameBoard[7][4] == KINGWHITE){
        soldierPos.row = 7;
        soldierPos.column = 7;
        tmpDest.row = 7;
        tmpDest.column = 4;
        if (row == 7 && col == 7){
            spArrayListAddLast(possibleMoves,generateAction(soldierPos, tmpDest, BLANK, ROOKBLACK, SP_CHESS_BLACK_RIGHT_CASTLING, 0, 0, src->blackLeftCastling, 1));
        } else if (row == 7 && col == 4) {
            spArrayListAddLast(possibleMoves, generateAction(tmpDest, soldierPos, BLANK, KINGBLACK, SP_CHESS_BLACK_RIGHT_CASTLING,  0, 0, src->blackLeftCastling, 1));
        }
    }
    return possibleMoves;
}


void printCheckMessage(SPChessGame* src, int current){
    char* player;
    if (src->gameMode == 1 && current == src->userColor){
        printf("Check!\n");
    }
    else{
        player = current == 0 ? "black" : "white";
        printf("Check: %s King is threatened!\n", player);
    }
}


SP_CHESS_GAME_STATE chessCheckWinner(SPChessGame* src, int isMini, int isGui){
    bool flag = true;
    if (!src){ return SP_CHESS_GAME_INVALID_GAME;}
    char tmp;
    int num;
    SPArrayList *possibleMoves;
    if (src->currentPlayer == 1) {
        for (int i = 0; i < GAMESIZE; i++){
            for (int j = 0; j < GAMESIZE; j++){
                tmp = whosThere(src, i, j);
                if (isWhite(tmp)){
                    possibleMoves = getMovesForSoldier(src, i, j);
                    num = possibleMoves->actualSize;
                    spArrayListDestroy(&possibleMoves);
                    if (num > 0){
                        flag = false;
                        goto next1;
                    }

                }
            }
        }
        next1:
        if (isTheKingThreatened(src, src->currentPlayer)){       // is the white king threatened?
            if (flag){ return SP_CHESS_GAME_BLACK_WINNER; }      // no possible moves at all for the white && check
            else{                                                // just check
                if (isMini == 0){
                    if (isGui == 0){ printCheckMessage(src, src->currentPlayer); }
                }
                return SP_CHESS_GAME_NO_WINNER;
            }
        }
        else if (flag){ return SP_CHESS_GAME_TIE; }             // No moves but no check
        else return SP_CHESS_GAME_NO_WINNER;                    // there are moves, no check
    }
    else {
        for (int i = 0; i < GAMESIZE; i++){
            for (int j = 0; j < GAMESIZE; j++){
                tmp = whosThere(src, i, j);
                if (isBlack(tmp)) {
                    possibleMoves = getMovesForSoldier(src, i, j);
                    num = possibleMoves->actualSize;
                    spArrayListDestroy(&possibleMoves);
                    if (num > 0) {
                        flag = false;
                        goto next2;
                    }
                }
            }
        }
        next2:
        if (isTheKingThreatened(src, src->currentPlayer)){       // is the black king threatened?
            if (flag){ return SP_CHESS_GAME_WHITE_WINNER; }      // no possible moves at all for the black && check
            else {                                               // just check
                if (isMini == 0){
                    if (isGui == 0){ printCheckMessage(src, src->currentPlayer); }
                }
                return SP_CHESS_GAME_NO_WINNER;
            }
        }
        else if (flag){ return SP_CHESS_GAME_TIE; }             // No moves but no check
        else return SP_CHESS_GAME_NO_WINNER;                    // there are moves, no check
    }
}
