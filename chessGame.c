//
// Created by אורי חביב on 05/09/2017.
//

#include "chessGame.h"


SPChessGame* spFiarGameCreate() {
    SPChessGame *game = (SPChessGame *) malloc(sizeof(SPChessGame));
    if (game != NULL) {
        game->lastMoves = spArrayListCreate(HISTORYSIZE);
        if (game->lastMoves != NULL) {
            game->userColor = 1;
            game->currentPlayer = 1;
            game->difficulty = 2;
            game->state = 0;
            game->gameMode = 1;
            for (int i = 0; i < GAMESIZE; i++) {
                for (int j = 0; j < GAMESIZE; j++) {
                    if(i==1){
                        game->gameBoard[i][j] = PAWNWHITE;
                    }
                    else if (i == 6){
                        game->gameBoard[i][j] = PAWNBLACK;
                    }
                    else{game->gameBoard[i][j] = BLANK;}
                }
            }
            game->gameBoard[0][0] = BISHOPWHITE;
            game->gameBoard[0][1] = BISHOPWHITE;
            game->gameBoard[0][2] = BISHOPWHITE;
            game->gameBoard[0][3] = BISHOPWHITE;
            game->gameBoard[0][4] = BISHOPWHITE;
            game->gameBoard[0][5] = BISHOPWHITE;
            game->gameBoard[0][7] = BISHOPWHITE;
            game->gameBoard[7][0] = BISHOPWHITE;
            game->gameBoard[7][1] = BISHOPWHITE;
            game->gameBoard[7][2] = BISHOPWHITE;
            game->gameBoard[7][3] = BISHOPWHITE;
            game->gameBoard[7][4] = BISHOPWHITE;
            game->gameBoard[7][5] = BISHOPWHITE;
            game->gameBoard[7][6] = BISHOPWHITE;
            game->gameBoard[7][7] = BISHOPWHITE;
            return game;
        }
//            spFiarGameDestroy(fiarGame);
    } else {
        printf("Error: game create malloc has failed");
    }
    return NULL;
}