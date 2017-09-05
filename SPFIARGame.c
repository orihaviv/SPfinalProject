//
// Created by אורי חביב on 31/05/2017.
//


#include "SPChessGame.h"


SPFiarGame* spFiarGameCreate(int historySize) {
    if (historySize > 0) {
        SPFiarGame *fiarGame = (SPFiarGame *) malloc(sizeof(SPFiarGame));
        if (fiarGame != NULL) {
            fiarGame->undoHistory = 0;
            fiarGame->currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
            fiarGame->lastMoves = spArrayListCreate(historySize);
            if (fiarGame->lastMoves != NULL) {
                for (int i = 0; i < SP_FIAR_GAME_N_ROWS; i++) {
                    for (int j = 0; j < SP_FIAR_GAME_N_COLUMNS; j++) {
                        fiarGame->gameBoard[i][j] = SP_FIAR_GAME_EMPTY_ENTRY;
                    }
                }
                for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++){
                    (fiarGame->tops)[i] = 0;
                }
                return fiarGame;
            }
            spFiarGameDestroy(fiarGame);
        }
        else{
            printf("Error: malloc has failed");
        }
    }
    return NULL;
}


SPFiarGame* spFiarGameCopy(SPFiarGame* src){
    if (src != NULL) {
        SPFiarGame *fiarGame = (SPFiarGame *) malloc(sizeof(SPFiarGame));
        if (fiarGame != NULL) {
            fiarGame->undoHistory = src->undoHistory;
//            fiarGame->lastMoves = spArrayListCreate(src->lastMoves->maxSize);
            fiarGame->lastMoves = spArrayListCopy(src->lastMoves);
            if (fiarGame->lastMoves != NULL) {
                fiarGame->currentPlayer = src->currentPlayer;
                for (int i = 0; i < SP_FIAR_GAME_N_ROWS; i++) {
                    for (int j = 0; j < SP_FIAR_GAME_N_COLUMNS; j++) {
                        fiarGame->gameBoard[i][j] = src->gameBoard[i][j];
                    }
                }
                for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++){
                    (fiarGame->tops)[i] = (src->tops)[i];
                }
                return fiarGame;
            }
            spFiarGameDestroy(fiarGame);
        }
        else{
            printf("Error: malloc has failed");
        }
    }
    return NULL;
}

void spFiarGameDestroy(SPFiarGame* src){
    if (src == NULL){
        return;
    }
    spArrayListDestroy(src->lastMoves);
    free(src);
    return;
}


SP_FIAR_GAME_MESSAGE spFiarGameSetMove(SPFiarGame* src, int col){
    if ((!src) || (col < 0) || (col > 6)){
        return SP_FIAR_GAME_INVALID_ARGUMENT;
    }
    if (src->tops[col] == 6){
        return  SP_FIAR_GAME_INVALID_MOVE;
    }
    src->gameBoard[src->tops[col]][col] = spFiarGameGetCurrentPlayer(src);
    src->tops[col]++;
    gameSpArrayListAdd(src->lastMoves, col);
    switchPlayer(src);
    return SP_FIAR_GAME_SUCCESS;
}

bool spFiarGameIsValidMove(SPFiarGame* src, int col){
    if ((!src) || (col < 0) || (col > 6) || (src->tops[col] == SP_FIAR_GAME_N_ROWS)) {
        return false;
    }
    return true;
}

void spFiarGameDeleteMove(SPFiarGame* src){
    int col;
    col = spArrayListGetLast(src->lastMoves);
    if(spFiarGameGetCurrentPlayer(src) == SP_FIAR_GAME_PLAYER_1_SYMBOL){
        printf("Remove disc: remove computer's disc at column %d\n", col+1);
        src->currentPlayer = SP_FIAR_GAME_PLAYER_2_SYMBOL;
    }
    else {
        printf("Remove disc: remove users's disc at column %d\n", col+1);
        src->currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
    }
    src->gameBoard[src->tops[col]-1][col] = SP_FIAR_GAME_EMPTY_ENTRY;
    spArrayListRemoveLast(src->lastMoves);
    src->tops[col]--;
    return;
}

SP_FIAR_GAME_MESSAGE spFiarGameUndoPrevMove(SPFiarGame* src){
    if (!src){
        return SP_FIAR_GAME_INVALID_ARGUMENT;
    }
    if ((spArrayListIsEmpty(src->lastMoves))){
        return SP_FIAR_GAME_NO_HISTORY;
    }
    spFiarGameDeleteMove(src);
    return SP_FIAR_GAME_SUCCESS;

}

char spFiarGameGetCurrentPlayer(SPFiarGame* src){
    return src->currentPlayer;
}


SP_CHESS_GAME_MESSAGE spFiarGamePrintBoard(SPChessGame* src){
    if(!src){
        return SP_FIAR_GAME_INVALID_ARGUMENT;
    }
    for(int i=GAMESIZE;i>0;i--){
        printf("%d| ",i);
        for(int j=0;j<GAMESIZE; j++){
            printf("%c ",src->gameBoard[i-1][j]);
        }
        printf("|\n");
    }
    printf("  -----------------\n");
    printf("  ");
    for(int i=0;i<GAMESIZE; i++){
        printf(" %c",(i+65));
    }
    printf("\n");
}

char spFiarCheckWinner(SPFiarGame* src) {
    if (src == NULL){
        return '\0';
    }
    for (int i = 0; i < SP_FIAR_GAME_N_ROWS; i++) {
        for (int j = 0; j < SP_FIAR_GAME_N_COLUMNS - 3; j++) {
            if (src->gameBoard[i][j] == SP_FIAR_GAME_EMPTY_ENTRY){ continue;}
            for (int k = 1; k < SP_FIAR_GAME_SPAN; k++) {
                if (src->gameBoard[i][j + k] != src->gameBoard[i][j]) { break; }
                else if (k == SP_FIAR_GAME_SPAN - 1) { return src->gameBoard[i][j]; }
            }
        }
    }
    for (int i = 0; i < SP_FIAR_GAME_N_ROWS - 3; i++) {
        for (int j = 0; j < SP_FIAR_GAME_N_COLUMNS; j++) {
            if (src->gameBoard[i][j] == SP_FIAR_GAME_EMPTY_ENTRY){ continue;}
            for (int k = 1; k < SP_FIAR_GAME_SPAN; k++) {
                if (src->gameBoard[i + k][j] != src->gameBoard[i][j]) { break; }
                else if (k == SP_FIAR_GAME_SPAN - 1) { return src->gameBoard[i][j]; }
            }
        }
    }
    for (int i = 0; i < SP_FIAR_GAME_N_ROWS - 3; i++) {
        for (int j = 0; j < SP_FIAR_GAME_N_COLUMNS - 3; j++) {
            if (src->gameBoard[i][j] == SP_FIAR_GAME_EMPTY_ENTRY){ continue;}
            for (int k = 1; k < SP_FIAR_GAME_SPAN; k++) {
                if (src->gameBoard[i + k][j + k] != src->gameBoard[i][j]) { break; }
                else if (k == SP_FIAR_GAME_SPAN - 1) { return src->gameBoard[i][j]; }
            }
        }
    }
    for (int i = 0; i < SP_FIAR_GAME_N_ROWS - 3; i++) {
        for (int j = 3; j < SP_FIAR_GAME_N_COLUMNS; j++) {
            if (src->gameBoard[i][j] == SP_FIAR_GAME_EMPTY_ENTRY){ continue;}
            for (int k = 1; k < SP_FIAR_GAME_SPAN; k++) {
                if (src->gameBoard[i + k][j - k] != src->gameBoard[i][j]) { break; }
                else if (k == SP_FIAR_GAME_SPAN - 1) { return src->gameBoard[i][j]; }
            }
        }
    }
    for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++){
        if (src->tops[i] < SP_FIAR_GAME_N_ROWS){
            return '\0';
        }
    }
    return SP_FIAR_GAME_TIE_SYMBOL;
}


void switchPlayer(SPFiarGame* src){
    if (src != NULL) {
        if (spFiarGameGetCurrentPlayer(src) == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
            src->currentPlayer = SP_FIAR_GAME_PLAYER_2_SYMBOL;
        } else {
            src->currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
        }
    }
}
