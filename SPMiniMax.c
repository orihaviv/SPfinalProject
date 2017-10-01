//
// Created by ׳�׳•׳¨׳™ ׳—׳‘׳™׳‘ on 10/06/2017.
//
#include "SPMiniMax.h"


action* spMinimaxSuggestMove(SPChessGame* currentGame, int depth, int isGui){
    if (currentGame == NULL || depth <= 0 || depth > 4){ //TODO change >4 to >5 if needed
        return NULL;
    }
    SPChessGame* gameCopy = (chessGameCopy(currentGame));
    if (gameCopy == NULL){ return NULL; }
    int bestScore, score;
    SPArrayList* possibleActions;
    char currentSoldier;

    action move;
    action bestAction;
    if (gameCopy->currentPlayer == 1) {         // white's turn
        bestScore = INT_MIN;
        for (int i = 0; i < GAMESIZE; i++) {
            for (int j = 0; j < GAMESIZE; j++) {
                currentSoldier = gameCopy->gameBoard[i][j];
                if (isWhite(currentSoldier)) {
                    possibleActions = getMovesForSoldier(gameCopy, i, j);
                    for (int index = 0; index < possibleActions->actualSize; index++) {
                        move = *(spArrayListGetAt(possibleActions, index));
                        if (move.castling == SP_CHESS_NO_CASTLING){ chessGameSetMove(gameCopy, move.prev, move.current, 1, 0); }
                        else { executeCastlingMiniMax(gameCopy, move.prev, move.current, isGui); }
                        score = nodeScore(gameCopy, depth - 1, gameCopy->currentPlayer, INT_MIN, INT_MAX, isGui);
                        if (bestScore < score) {
                            bestAction = move;
                            bestScore = score;
                        }
                        chessGameUndoPrevMove(gameCopy);
                    }
                    spArrayListDestroy(&possibleActions);
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
                        if (move.castling == SP_CHESS_NO_CASTLING){ chessGameSetMove(gameCopy, move.prev, move.current, 1, 0); }
                        else { executeCastlingMiniMax(gameCopy, move.prev, move.current, isGui); }
                        score = nodeScore(gameCopy, depth - 1, gameCopy->currentPlayer, INT_MIN, INT_MAX, isGui);
                        if (bestScore > score) {
                            bestAction = move;
                            bestScore = score;
                        }
                        chessGameUndoPrevMove(gameCopy);
                    }
                    spArrayListDestroy(&possibleActions);
                }
            }
        }
    }
    chessGameDestroy(&gameCopy);
    return actionCopy(&bestAction);
}
