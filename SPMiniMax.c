//
// Created by ׳�׳•׳¨׳™ ׳—׳‘׳™׳‘ on 10/06/2017.
//
#include "SPMiniMax.h"

int spMinimaxSuggestMove(SPChessGame* currentGame, unsigned int maxDepth){
    if (currentGame == NULL || maxDepth <= 0){
        return -1;
    }
    SPChessGame* gameCopy = (spChessGameCopy(currentGame));
    position bestPos;
    int score, bestScore, first;
    if (gameCopy == NULL){return -1;}
    if (currentGame->currentPlayer == 1){ // white's turn
        bestScore = INT_MIN;
        for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++){
            if (isValidMove(gameCopy, i)) {
                first = spArrayListGetFirst(gameCopy->lastMoves);
                chessGameSetMove(gameCopy, i);
                score = (nodeScore(gameCopy, maxDepth - 1, 1));
                if (score > bestScore) {
                    bestScore = score;
                    bestCol = i;
                }
                gameCopy->gameBoard[gameCopy->tops[i]-1][i] = SP_FIAR_GAME_EMPTY_ENTRY;
                gameCopy->currentPlayer = 1 - gameCopy->currentPlayer;
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
            if (isValidMove(gameCopy, i)) {
                first = spArrayListGetFirst(gameCopy->lastMoves);
                chessGameSetMove(gameCopy, i);
                score = (nodeScore(gameCopy, maxDepth - 1, 0));
                if (score < bestScore) {
                    bestScore = score;
                    bestCol = i;
                }
                gameCopy->gameBoard[gameCopy->tops[i]-1][i] = SP_FIAR_GAME_EMPTY_ENTRY;
                gameCopy->currentPlayer = 1 - gameCopy->currentPlayer;
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
