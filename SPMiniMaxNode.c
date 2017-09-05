//
// Created by אורי חביב on 10/06/2017.
//
#include "SPMiniMaxNode.h"

int scoreOfLeafNode(SPFiarGame* currentGame){
    if (currentGame == NULL){
        return -1;
    }
    int vector[9] = {0};
    int num;
    for (int i = 0; i < SP_FIAR_GAME_N_ROWS; i++){
        for (int j = 0; j < SP_FIAR_GAME_N_COLUMNS-3; j++){
            num = 0;
            for (int k = 0; k < SP_FIAR_GAME_SPAN; k++){
                if (currentGame->gameBoard[i][j+k] == SP_FIAR_GAME_PLAYER_1_SYMBOL){ num++; }
                else if (currentGame->gameBoard[i][j+k] == SP_FIAR_GAME_PLAYER_2_SYMBOL){ num--; }
            }
            vector[num+4]++;
        }
    }
    for (int i = 0; i < SP_FIAR_GAME_N_ROWS-3; i++){
        for (int j = 0; j < SP_FIAR_GAME_N_COLUMNS; j++){
            num = 0;
            for (int k = 0; k < SP_FIAR_GAME_SPAN; k++){
                if (currentGame->gameBoard[i+k][j] == SP_FIAR_GAME_PLAYER_1_SYMBOL){ num++; }
                else if (currentGame->gameBoard[i+k][j] == SP_FIAR_GAME_PLAYER_2_SYMBOL){ num--; }
            }
            vector[num+4]++;
        }
    }
    for (int i = 0; i < SP_FIAR_GAME_N_ROWS-3; i++){
        for (int j = 0; j < SP_FIAR_GAME_N_COLUMNS-3; j++){
            num = 0;
            for (int k = 0; k < SP_FIAR_GAME_SPAN; k++){
                if (currentGame->gameBoard[i+k][j+k] == SP_FIAR_GAME_PLAYER_1_SYMBOL){ num++; }
                else if (currentGame->gameBoard[i+k][j+k] == SP_FIAR_GAME_PLAYER_2_SYMBOL){ num--; }
            }
            vector[num+4]++;
        }
    }
    for (int i = 0; i < SP_FIAR_GAME_N_ROWS-3; i++){
        for (int j = 3; j < SP_FIAR_GAME_N_COLUMNS; j++){
            num = 0;
            for (int k = 0; k < SP_FIAR_GAME_SPAN; k++){
                if (currentGame->gameBoard[i+k][j-k] == SP_FIAR_GAME_PLAYER_1_SYMBOL){ num++; }
                else if (currentGame->gameBoard[i+k][j-k] == SP_FIAR_GAME_PLAYER_2_SYMBOL){ num--; }
            }
            vector[num+4]++;
        }
    }
    if (vector[0]>0){ return INT_MIN;}
    else if (vector[8]){ return INT_MAX;}
    return (vector[1]*(-5) + vector[2]*(-2) + vector[3]*(-1) + vector[5] + vector[6]*2 + vector[7]*5);
}


int nodeScore(SPFiarGame* src, int depth, int player){
    if ((src == NULL) || (depth < 0) || (player < 0) || (player >1)){
        return -1;
    }
    SPFiarGame* gameCopy = (spFiarGameCopy(src));
    int score;
    int bestScore;
    if(player == 1){ // computer's turn
        bestScore = INT_MAX;
    }
    else{ // user's turn
        bestScore = INT_MIN;
    }
    int first;
    int scoreOfCurrent = scoreOfLeafNode(gameCopy);
    if ((depth != 0) && (scoreOfCurrent < INT_MAX) && (scoreOfCurrent > INT_MIN)){
        for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++){
            if (spFiarGameIsValidMove(gameCopy, i)) {
                first = spArrayListGetFirst(gameCopy->lastMoves);
                spFiarGameSetMove(gameCopy, i);
                score = (nodeScore(gameCopy, depth - 1, 1 - player));
                if (player == 1) {
                    if (bestScore > score) {
                        bestScore = score;
                    }
                }
                else{
                    if (score > bestScore) {
                        bestScore = score;
                    }
                }
                gameCopy->gameBoard[gameCopy->tops[i]-1][i] = SP_FIAR_GAME_EMPTY_ENTRY;
                switchPlayer(gameCopy);
                spArrayListRemoveLast(gameCopy->lastMoves);
                if(gameCopy->lastMoves->actualSize == gameCopy->lastMoves->maxSize-1){
                    spArrayListAddFirst(gameCopy->lastMoves, first);
                }
                gameCopy->tops[i]--;
            }
        }
        spFiarGameDestroy(gameCopy);
        return bestScore;
    }
    else {
        spFiarGameDestroy(gameCopy);
        return scoreOfCurrent;
    }
}
