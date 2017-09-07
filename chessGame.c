//
// Created by אורי חביב on 05/09/2017.
//

#include "chessGame.h"


SPChessGame* chessGameCreate() {
    SPChessGame *game = (SPChessGame *) malloc(sizeof(SPChessGame));
    if (game != NULL) {
        game->lastMoves = spArrayListCreate(HISTORYSIZE);
        if (game->lastMoves != NULL) {
            game->userColor = 1;
            game->currentPlayer = 1;
            game->difficulty = 2;
            game->state = 0;
            game->gameMode = 1;
            for (int i = 1; i < GAMESIZE-1; i++) {
                for (int j = 0; j < GAMESIZE; j++) {
                    if(i==1){
                        game->gameBoard[i][j] = PAWNWHITE;
                    }
                    else if (i == GAMESIZE-2){
                        game->gameBoard[i][j] = PAWNBLACK;
                    }
                    else{game->gameBoard[i][j] = BLANK;}
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




SPChessGame* spFiarGameCopy(SPChessGame* src){
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
        }
        else{
            printf("Error: copy malloc has failed");
        }
    }
    return NULL;
}


void chessGameDestroy(SPChessGame* src){
    if (src == NULL){
        return;
    }
    spArrayListDestroy(src->lastMoves);
    free(src);
    return;
}


SP_CHESS_GAME_MESSAGE spChessGamePrintBoard(SPChessGame* src){
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

int spChessGameGetCurrentPlayer(SPChessGame* src){
    return src->currentPlayer;
}

//void changeToSetting(SPChessGame* src){
//    src->state = 0;
//    printf("Specify game setting or type 'start' to begin a game with the current setting:\\n");
//}


