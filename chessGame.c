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
            printf("Specify game setting or type 'start' to begin a game with the current setting:\\n");
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
    position king;
    int flag = 0;
    char kingChar = KINGBLACK;
    if (color == 1) { kingChar = KINGWHITE; }
    for (int i = 0; i < GAMESIZE; i++) {
        for (int j = 0; j < GAMESIZE; j++) {
            if (src->gameBoard[i][j] == kingChar) {
                king.row = i;
                king.column = j;
                flag = 1;
                break;
            }
        }
        if (flag) { break; }
    }
    return king;
}





bool pawnsThreatKing(SPChessGame *src, int color, position kingPos) {
    char pawn = PAWNBLACK;
    if (color == 0) {  // king is black
        pawn = PAWNWHITE;
        if ((whosThere(src, kingPos.row - 1, kingPos.column - 1) == pawn) ||
            (whosThere(src, kingPos.row - 1, kingPos.column + 1) == pawn)) {
            return true;
        }
    }
    //king is white
    if ((whosThere(src, kingPos.row + 1, kingPos.column - 1) == pawn) ||
        (whosThere(src, kingPos.row + 1, kingPos.column + 1) == pawn)) {
        return true;
    }
    return false;
}






bool knightsThreatKing(SPChessGame *src, int color, position kingPos) {
    char knight = KNIGHTBLACK;   //king is white
    if (color == 0) {           // king is black
        knight = KNIGHTWHITE;
    }
    if ((whosThere(src, kingPos.row - 2, kingPos.column - 1) == knight) ||
        (whosThere(src, kingPos.row - 2, kingPos.column + 1) == knight)
        || (whosThere(src, kingPos.row + 2, kingPos.column - 1) == knight) ||
        (whosThere(src, kingPos.row + 2, kingPos.column + 1) == knight)
        || (whosThere(src, kingPos.row + 1, kingPos.column - 2) == knight) ||
        (whosThere(src, kingPos.row + 1, kingPos.column + 2) == knight)
        || (whosThere(src, kingPos.row - 1, kingPos.column - 2) == knight) ||
        (whosThere(src, kingPos.row - 1, kingPos.column + 2) == knight)) {
        return true;
    }
    return false;
}






bool kingThreatensKing(SPChessGame *src, int color, position kingPos) {
    char opKing = KINGBLACK;   //our king is white
    if (color == 0) {           // our king is black
        opKing = KINGWHITE;
    }
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (whosThere(src, kingPos.row + i, kingPos.column + j) == opKing) {
                return true;
            }
        }
    }
    return false;
}






bool checkLane(SPChessGame *src, int x, int y, position kingPos, char queen, char other){
    int row = kingPos.row;
    int col = kingPos.column;
    char soldier;
    while (row < GAMESIZE && row > 0 && col < GAMESIZE && col > 0) {
        row += y;
        col += x;
        soldier = whosThere(src, row, col);
        if (soldier == queen || soldier == other) { return true; }
        if (soldier != BLANK) { break; }
    }
    return false;
}





bool QRBThreatensKing(SPChessGame *src, int color, position kingPos) {
    char queen = QUEENBLACK;   //our king is white
    char bishop = BISHOPBLACK;
    char rook = ROOKBLACK;
    if (color == 0) {           // our king is black
        queen = QUEENWHITE;
        bishop = BISHOPWHITE;
        rook = ROOKWHITE;
    }
    if (checkLane(src, 0, 1, kingPos, queen, rook)) { return true; }
    if (checkLane(src, 1, 0, kingPos, queen, rook)) { return true; }
    if (checkLane(src, -1, 0, kingPos, queen, rook)) { return true; }
    if (checkLane(src, 0, -1, kingPos, queen, rook)) { return true; }
    if (checkLane(src, 1, 1, kingPos, queen, bishop)) { return true; }
    if (checkLane(src, -1, -1, kingPos, queen, bishop)) { return true; }
    if (checkLane(src, -1, 1, kingPos, queen, bishop)) { return true; }
    if (checkLane(src, 1, -1, kingPos, queen, bishop)) { return true; }
    return false;
}




bool isTheKingThreatened(SPChessGame *src, int color) {
    position king = getKingPosition(src, color);
    if (pawnsThreatKing(src, color, king) || knightsThreatKing(src, color, king)
        || kingThreatensKing(src, color, king) || QRBThreatensKing(src, color, king)){
        return true;
    }
    return false;
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
    int direction;
    src->currentPlayer == 1 ? direction = 1 : direction = -1;
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
    dest.column > origin.column ? dx = 1 : dx = -1;
    dest.row > origin.row ? dy = 1 : dy = -1;
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
    if (src->currentPlayer == 1 && (isWhite(src->gameBoard[dest.row][dest.column]) || isBlack(src->gameBoard[origin.row][origin.column]))) { return false;}
    if (src->currentPlayer == 0 && (isBlack(src->gameBoard[dest.row][dest.column]) || isWhite(src->gameBoard[origin.row][origin.column]))) { return false;}
    if (src->gameBoard[origin.row][origin.column] == BLANK) { return false; }
    char soldier = (src->gameBoard[origin.row][origin.column]);
    bool flag = true;
    if (soldier == PAWNWHITE || soldier == PAWNBLACK){ flag = pawnValidMove(src, origin, dest);}
    else if (soldier == KNIGHTBLACK || soldier == KNIGHTWHITE) { flag = knightValidMove(src, origin, dest);}
    else if (soldier == KINGBLACK || soldier == KINGWHITE) { flag = kingValidMove(src, origin, dest);}
    else if (soldier == ROOKBLACK || soldier == ROOKWHITE) { flag = rookValidMove(src, origin, dest);}
    else if (soldier == BISHOPBLACK || soldier == BISHOPWHITE) { flag = bishopValidMove(src, origin, dest);}
    else if (soldier == QUEENBLACK || soldier == QUEENWHITE) { flag = queenValidMove(src, origin, dest);}
    if (flag && isMoveSafeForKing(src, origin, dest)){
        return true;
    }
    return false;
}





SP_CHESS_GAME_MESSAGE chessGameSetMove(SPChessGame* src, position origin , position dest){
        if ((!src) || !posOnBoard(origin) || !posOnBoard(dest)){
            return SP_CHESS_GAME_INVALID_ARGUMENT;
        }
        if (!isValidMove(src,origin,dest)) {
            return SP_CHESS_GAME_INVALID_MOVE;
        }
        int currPlayer = src->currentPlayer;
        src->gameBoard[dest.row][dest.column] = src->gameBoard[origin.row][origin.column];
        src->gameBoard[origin.row][origin.column] = BLANK;
        action move;
        move.current = dest;
        move.prev = origin;
        spArrayListAddFirst(src->lastMoves , move);
        src->currentPlayer = 1 - src->currentPlayer;
        return SP_CHESS_GAME_SUCCESS;
    }

//    bool spFiarGameIsValidMove(SPFiarGame* src, int col){
//        if ((!src) || (col < 0) || (col > 6) || (src->tops[col] == SP_FIAR_GAME_N_ROWS)) {
//            return false;
//        }
//        return true;
//    }
//
//    void spFiarGameDeleteMove(SPFiarGame* src){
//        int col;
//        col = spArrayListGetLast(src->lastMoves);
//        if(spFiarGameGetCurrentPlayer(src) == SP_FIAR_GAME_PLAYER_1_SYMBOL){
//            printf("Remove disc: remove computer's disc at column %d\n", col+1);
//            src->currentPlayer = SP_FIAR_GAME_PLAYER_2_SYMBOL;
//        }
//        else {
//            printf("Remove disc: remove users's disc at column %d\n", col+1);
//            src->currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
//        }
//        src->gameBoard[src->tops[col]-1][col] = SP_FIAR_GAME_EMPTY_ENTRY;
//        spArrayListRemoveLast(src->lastMoves);
//        src->tops[col]--;
//        return;
//    }


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
}





int chessGameGetCurrentPlayer(SPChessGame *src) {
    return src->currentPlayer;
}





//void changeToSetting(SPChessGame* src){
//    src->state = 0;
//    printf("Specify game setting or type 'start' to begin a game with the current setting:\\n");
//}


