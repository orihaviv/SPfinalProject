//
// Created by אורי חביב on 10/06/2017.
//
#include "SPMiniMax.h"

int spMinimaxSuggestMove(SPFiarGame* currentGame, unsigned int maxDepth){
    if (currentGame == NULL || maxDepth <= 0){
        return -1;
    }
    SPFiarGame* gameCopy = (spFiarGameCopy(currentGame));
    int score, bestScore, bestCol = 9, first;
    if (gameCopy == NULL){return -1;}
    if (currentGame->currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL){ // user's turn
        bestScore = INT_MIN;
        for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++){
            if (spFiarGameIsValidMove(gameCopy, i)) {
                first = spArrayListGetFirst(gameCopy->lastMoves);
                spFiarGameSetMove(gameCopy, i);
                score = (nodeScore(gameCopy, maxDepth - 1, 1));
                if (score > bestScore) {
                    bestScore = score;
                    bestCol = i;
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
    }
    else{ // computer's turn
        bestScore = INT_MAX;
        for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++){
            if (spFiarGameIsValidMove(gameCopy, i)) {
                first = spArrayListGetFirst(gameCopy->lastMoves);
                spFiarGameSetMove(gameCopy, i);
                score = (nodeScore(gameCopy, maxDepth - 1, 0));
                if (score < bestScore) {
                    bestScore = score;
                    bestCol = i;
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
    }
    spFiarGameDestroy(gameCopy);
    return bestCol;
}