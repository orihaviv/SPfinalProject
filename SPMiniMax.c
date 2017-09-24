//
// Created by ׳�׳•׳¨׳™ ׳—׳‘׳™׳‘ on 10/06/2017.
//
#include "SPMiniMax.h"


action* spMinimaxSuggestMove(SPChessGame* currentGame, int depth){
    if (currentGame == NULL || depth <= 0 || depth > 4){ //TODO change >4 to >5 if needed
        return NULL;
    }
    SPChessGame* gameCopy = (chessGameCopy(currentGame));
    if (gameCopy == NULL){ return NULL; }
    action bestAction;
    int bestScore, score;
    SPArrayList* possibleActions;
    char currentSoldier;


    action move;
    if (gameCopy->currentPlayer == 1) {         // white's turn
        bestScore = INT_MIN;
        for (int i = 0; i < GAMESIZE; i++) {
            for (int j = 0; j < GAMESIZE; j++) {
                currentSoldier = gameCopy->gameBoard[i][j];
                if (isWhite(currentSoldier)) {
                    possibleActions = getMovesForSoldier(gameCopy, i, j);
                    for (int index = 0; index < possibleActions->actualSize; index++) {
                        move = *(spArrayListGetAt(possibleActions, index));
                        chessGameSetMove(gameCopy, move.prev, move.current, 1);
                        score = nodeScore(gameCopy, depth - 1, 1 - gameCopy->currentPlayer, INT_MIN, INT_MAX);
                        if (bestScore < score) {
                            bestAction = move;
                            bestScore = score;
                        }
                        chessGameUndoPrevMove(gameCopy);
                    }
                }
            }
        }
    }
    else {                                        //  black's turn
        bestScore = INT_MAX;
        for (int i = 0; i < GAMESIZE; i++) {
            for (int j = 0; j < GAMESIZE; j++) {
                currentSoldier = gameCopy->gameBoard[i][j];
                if (isBlack(currentSoldier)) {
                    possibleActions = getMovesForSoldier(gameCopy, i, j);
                    for (int index = 0; index < possibleActions->actualSize; index++) {
                        move = *(spArrayListGetAt(possibleActions, index));
                        chessGameSetMove(gameCopy, move.prev, move.current, 1);
                        score = nodeScore(gameCopy, depth - 1, 1 - gameCopy->currentPlayer, INT_MIN, INT_MAX);
                        if (bestScore > score) {
                            bestAction = move;
                            bestScore = score;
                        }
                        chessGameUndoPrevMove(gameCopy);
                    }
                }
            }
        }
    }
    spArrayListDestroy(&possibleActions);
    chessGameDestroy(&gameCopy);
    action* bestActionPointer;
    bestActionPointer = &bestAction;
    return bestActionPointer;

}
