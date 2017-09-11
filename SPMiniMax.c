//
// Created by ׳�׳•׳¨׳™ ׳—׳‘׳™׳‘ on 10/06/2017.
//
#include "SPMiniMax.h"


action* spMinimaxSuggestMove(SPChessGame* currentGame, int depth){
    if (currentGame == NULL || depth <= 0 || depth > 4){ //TODO change >4 to >5 if needed
        return NULL;
    }
    SPChessGame* gameCopy = (spChessGameCopy(currentGame));
    action bestAction;
    int bestScore, score;
    SPArrayList* possibleActions;
    char currentSoldier;



    if (gameCopy->currentPlayer == 1) {         // white's turn
        bestScore == INT_MIN;
        for (int i = 0; i < GAMESIZE; i++) {
            for (int j = 0; j < GAMESIZE; j++) {
                currentSoldier = gameCopy->gameBoard[i][j];
                if (isWhite(currentSoldier)) {
                    possibleActions = getMovesForSoldier(gameCopy, i, j);
                    for (action move : possibleActions) {
                        chessGameSetMove(gameCopy, move.prev, move.current);
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
        bestScore == INT_MAX;
        for (int i = 0; i < GAMESIZE; i++) {
            for (int j = 0; j < GAMESIZE; j++) {
                currentSoldier = gameCopy->gameBoard[i][j];
                if (isBlack(currentSoldier)) {
                    possibleActions = getMovesForSoldier(gameCopy, i, j);
                    for (action move : possibleActions) {
                        chessGameSetMove(gameCopy, move.prev, move.current);
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
    spArrayListDestroy(possibleActions);
    chessGameDestroy(gameCopy);
    return &(bestAction);

}




int nodeScore(SPChessGame *src, int depth, int player, int alpha, int beta) {


    if (player == 1) {         // white's turn
        bestScore == INT_MIN;
        for (int i = 0; i < GAMESIZE; i++) {
            for (int j = 0; j < GAMESIZE; j++) {
                currentSoldier = gameCopy->gameBoard[i][j];
                if (isWhite(currentSoldier)) {
                    possibleActions = getMovesForSoldier(gameCopy, i, j);
                    for (action move : possibleActions) {
                        chessGameSetMove(gameCopy, move.prev, move.current);
                        bestScore = maxi(bestScore, nodeScore(gameCopy, depth - 1, 1 - player, alpha, beta));
                        chessGameUndoPrevMove(gameCopy);
                        alpha = maxi(bestScore, alpha);
                        if (beta <= alpha) { break; }
                    }
                }
            }
        }
    }
    else {                  //  black's turn
        bestScore == INT_MAX;
        for (int i = 0; i < GAMESIZE; i++) {
            for (int j = 0; j < GAMESIZE; j++) {
                currentSoldier = gameCopy->gameBoard[i][j];
                if (isBlack(currentSoldier)) {
                    possibleActions = getMovesForSoldier(gameCopy, i, j);
                    for (action move : possibleActions) {
                        chessGameSetMove(gameCopy, move.prev, move.current);
                        bestScore = mini(bestScore, nodeScore(gameCopy, depth - 1, 1 - player, alpha, beta));
                        chessGameUndoPrevMove(gameCopy);
                        beta = mini(bestScore, beta);
                        if (beta <= alpha) { break; }
                    }
                }
            }
        }
    }
    spArrayListDestroy(possibleActions);
    chessGameDestroy(gameCopy);
    return bestScore;
}
