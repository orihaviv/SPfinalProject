//
// Created by אורי חביב on 05/09/2017.
//

#include <ctype.h>
#include "chessGame.h"




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
            game->whiteKing.column = 4;
            game->whiteKing.row = 0;
            game->blackKing.column = 4;
            game->blackKing.row = 7;
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
            printf("Specify game setting or type 'start' to begin a game with the current setting:\n");
            return game;
        }
        chessGameDestroy(game);
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
                for (int i = 0; i < GAMESIZE; i++) {
                    for (int j = 0; j < GAMESIZE; j++) {
                        game->gameBoard[i][j] = src->gameBoard[i][j];
                    }
                }
                return game;
            }
            chessGameDestroy(game);
        } else {
            printf("Error: copy malloc has failed");
        }
    }
    return NULL;
}






void chessGameDestroy(SPChessGame *src) {
    if (src == NULL) {
        return;
    }
    spArrayListDestroy(src->lastMoves);
    free(src);
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




bool pawnsThreatSoldier(SPChessGame *src, int color, position soldier) {
    char pawn = PAWNBLACK;
    if (color == 0) {  // king is black
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
    char knight = KNIGHTBLACK;   //king is white
    if (color == 0) {           // king is black
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
    while (row < GAMESIZE && row > 0 && col < GAMESIZE && col > 0) {
        row += y;
        col += x;
        tmp = whosThere(src, row, col);
        if (tmp == queen || tmp == other) { return true; }
        if (tmp != BLANK) { break; }
    }
    return false;
}





bool QRBThreatensSoldier(SPChessGame *src, int color, position soldier) {
    char queen = QUEENBLACK;   //our king is white
    char bishop = BISHOPBLACK;
    char rook = ROOKBLACK;
    if (color == 0) {           // our king is black
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




bool isMoveSafeForKing(SPChessGame* src, position origin , position dest){
    char tmp = src->gameBoard[dest.row][dest.column];
    src->gameBoard[dest.row][dest.column] = src->gameBoard[origin.row][origin.column];
    src->gameBoard[origin.row][origin.column] = BLANK;
    bool result = isTheKingThreatened(src, src->currentPlayer);
    src->gameBoard[origin.row][origin.column] = src->gameBoard[dest.row][dest.column];
    src->gameBoard[dest.row][dest.column] = tmp;
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
    if (origin.column == dest.column && dest.row == (origin.row + direction) && src->gameBoard[dest.row][dest.column] == BLANK){ return true;}
    if (origin.column == dest.column && direction == 1 && origin.row == 1 && dest.row == (origin.row + 2*direction)
        && src->gameBoard[dest.row][dest.column] == BLANK){ return true;}
    if (origin.column == dest.column && direction == -1 && origin.row == 6 && dest.row == (origin.row + 2*direction)
        && src->gameBoard[dest.row][dest.column] == BLANK){ return true;}
    if (direction == 1){
        if ((origin.column == dest.column-1 || origin.column == dest.column+1)
            && dest.row == (origin.row + direction) && isBlack(src->gameBoard[dest.row][dest.column])){ return true;}
    }
    else{
        if ((origin.column == dest.column-1 || origin.column == dest.column+1)
            && dest.row == (origin.row + direction) && isWhite(src->gameBoard[dest.row][dest.column])){ return true;}
    }
    return false;
}


bool knightValidMove(SPChessGame* src, position origin , position dest){
    if (!((abs(origin.row - dest.row) == 2 && abs(origin.column - dest.column) == 1)
        || (abs(origin.row - dest.row) == 1 && abs(origin.column - dest.column) == 2))){
        return false;
    }
    return true;
}

bool kingValidMove(SPChessGame* src, position origin , position dest){
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


bool isValidMove(SPChessGame* src, position origin , position dest){
    if ((!src) || !posOnBoard(origin) || !posOnBoard(dest) || (origin.row == dest.row && origin.column == dest.column)) { return false; }
    if (src->currentPlayer == 1 && (isWhite(src->gameBoard[dest.row][dest.column]) || !isWhite(src->gameBoard[origin.row][origin.column]))) { return false;}
    if (src->currentPlayer == 0 && (isBlack(src->gameBoard[dest.row][dest.column]) || !isBlack(src->gameBoard[origin.row][origin.column]))) { return false;}
    char soldier = (src->gameBoard[origin.row][origin.column]);
    bool flag = true;
    if (soldier == PAWNWHITE || soldier == PAWNBLACK){ flag = pawnValidMove(src, origin, dest);}
    else if (soldier == KNIGHTBLACK || soldier == KNIGHTWHITE) { flag = knightValidMove(src, origin, dest);}
    else if (soldier == KINGBLACK || soldier == KINGWHITE) { flag = kingValidMove(src, origin, dest);}
    else if (soldier == ROOKBLACK || soldier == ROOKWHITE) { flag = rookValidMove(src, origin, dest);}
    else if (soldier == BISHOPBLACK || soldier == BISHOPWHITE) { flag = bishopValidMove(src, origin, dest);}
    else if (soldier == QUEENBLACK || soldier == QUEENWHITE) { flag = queenValidMove(src, origin, dest);}
    if (flag && !isMoveSafeForKing(src, origin, dest)){
        return true;
    }
    return false;
}





SP_CHESS_GAME_MESSAGE chessGameSetMove(SPChessGame* src, position origin , position dest) {
    if ((!src) || !posOnBoard(origin) || !posOnBoard(dest)) {
        return SP_CHESS_GAME_INVALID_ARGUMENT;
    }
    if (!isValidMove(src, origin, dest)) {
        return SP_CHESS_GAME_INVALID_MOVE;
    }
    char soldier = (src->gameBoard[origin.row][origin.column]);
    int currPlayer = src->currentPlayer;
    if (soldier == KINGBLACK){
        src->blackKing.row = dest.row;
        src->blackKing.column = dest.column;
    }
    else if (soldier == KINGWHITE){
        src->whiteKing.row = dest.row;
        src->whiteKing.column = dest.column;
    }
    char captured = src->gameBoard[dest.row][dest.column];
    src->gameBoard[dest.row][dest.column] = soldier;
    src->gameBoard[origin.row][origin.column] = BLANK;
    action move;
    move.current = dest;
    move.prev = origin;
    move.captured = captured;
    spArrayListAddFirst(src->lastMoves, move);
    src->currentPlayer = 1 - src->currentPlayer;
    return SP_CHESS_GAME_SUCCESS;
}



SP_CHESS_GAME_MESSAGE chessGameUndoPrevMove(SPChessGame* src){
    if (!src){
        return SP_CHESS_GAME_INVALID_ARGUMENT;
    }
    if ((spArrayListIsEmpty(src->lastMoves))){
        return SP_CHESS_GAME_NO_HISTORY;
    }
    action lastMove = spArrayListGetFirst(src->lastMoves);
    spArrayListRemoveFirst(src->lastMoves);
    if ((src->gameBoard[lastMove.current.row][lastMove.current.column]) == KINGBLACK){
        src->blackKing.row = lastMove.prev.row;
        src->blackKing.column = lastMove.prev.column;
    }
    else if ((src->gameBoard[lastMove.current.row][lastMove.current.column]) == KINGWHITE){
        src->whiteKing.row = lastMove.prev.row;
        src->whiteKing.column = lastMove.prev.column;
    }
    src->gameBoard[lastMove.prev.row][lastMove.prev.column] = src->gameBoard[lastMove.current.row][lastMove.current.column];
    src->gameBoard[lastMove.current.row][lastMove.current.column] = lastMove.captured;
    char* player = src->currentPlayer == 1 ? "black" : "white";
    printf("Undo move for player %s : <%d,%c> ->  <%d,%c>\n", player,
           toRowNum(lastMove.current.row), toColChar(lastMove.current.column),toRowNum(lastMove.prev.row), toColChar(lastMove.prev.column));
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
    printf("\n\n");
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
            if (isValidMove(src, soldierPos, tmpDest)){
                spArrayListAddLast(possibleMoves, generateAction(soldierPos, tmpDest, whosThere(src, i, j)));
            }
        }
    }
    return possibleMoves;
}





int chessCheckWinner(SPChessGame* src){
    if (!src){ return NULL;}
    char tmp;
    SPArrayList *possibleMoves;
    int cur = src->currentPlayer;
    if (src->currentPlayer == 1) {
        for (int i = 0; i < GAMESIZE; i++){
            for (int j = 0; j < GAMESIZE; j++){
                tmp = whosThere(src, i, j);
                if (isWhite(tmp)){
                    possibleMoves = getMovesForSoldier(src, i, j);
                    if (possibleMoves->actualSize > 0){ return -1; }
                }
            }
        }
        // no possible moves at all for the white
        if (isTheKingThreatened(src, src->currentPlayer)){ return 0;}  // is the white king threatened?
        else return 2;
    }
    else {
        for (int i = 0; i < GAMESIZE; i++){
            for (int j = 0; j < GAMESIZE; j++){
                tmp = whosThere(src, i, j);
                if (isBlack(tmp)){
                    possibleMoves = getMovesForSoldier(src, i, j);
                    if (possibleMoves->actualSize > 0){ return -1; }
                }
            }
        }
        // no possible moves at all for the black
        if (isTheKingThreatened(src, src->currentPlayer)){ return 1;}  // is the black king threatened?
        else return 2;
    }
}






