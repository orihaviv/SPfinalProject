//
// Created by ׳³ן¿½׳³ג€¢׳³ֲ¨׳³ג„¢ ׳³ג€”׳³ג€˜׳³ג„¢׳³ג€˜ on 10/06/2017.
//
#include "SPMiniMaxNode.h"
#include "chessGame.h"

int soldierScore(char soldier) {
    switch (soldier) {
        case BLANK:
            return BLANKSCORE;
        case PAWNWHITE:
            return PAWNWHITESCORE;
        case PAWNBLACK:
            return PAWNWBLACKSCORE;
        case BISHOPWHITE:
            return BISHOPWHITESCORE;
        case BISHOPBLACK:
            return BISOPBLACKSCORE;
        case ROOKWHITE:
            return ROOKWHITESCORE;
        case ROOKBLACK:
            return ROOKBLACKSCORE;
        case KNIGHTWHITE:
            return KNIGHTWHITESCORE;
        case KNIGHTBLACK:
            return KNIGHTBLACKSCORE;
        case QUEENWHITE:
            return QUEENWHITESCORE;
        case QUEENBLACK:
            return QUEENBLACKSCORE;
        case KINGWHITE:
            return KINGWHITESCORE;
        case KINGBLACK:
            return KINGBLACKSCORE;
    }
}

int scoreOfLeafNode(SPChessGame *currentGame) {
    int score = chessCheckWinner(currentGame);
    if (score == 1) {         // white player won
        return INT_MAX;
    } else if (score == 0) {    // black player won
        return INT_MIN;
    } else if (score == 2) { return 999; } // tie
    score = 0;
    for (int i = 0; i < GAMESIZE; i++) {
        for (int j = 0; j < GAMESIZE; j++) {
            score += soldierScore(currentGame->gameBoard[i][j]);
        }
    }
    return score;
}


int nodeScore(SPChessGame *src, int depth, int player, int alpha, int beta) {
    if ((src == NULL) || (depth < 0) || (depth > 4) || (player < 0) || (player > 1)) {  //TODO change >4 to >5 if needed
        return -999;
    }

    SPChessGame *gameCopy = (chessGameCopy(src));
    int bestScore;
    SPArrayList* possibleActions;
    char currentSoldier;
    int scoreOfCurrent = scoreOfLeafNode(gameCopy);

    if ((depth == 0) || (scoreOfCurrent == INT_MAX) || (scoreOfCurrent ==  INT_MIN)) {
        chessGameDestroy(&gameCopy);
        return scoreOfCurrent;
    } else if (scoreOfCurrent == 999){
        chessGameDestroy(&gameCopy);
        return 0;
    }

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
    spArrayListDestroy(&possibleActions);
    chessGameDestroy(&gameCopy);
    return bestScore;
}
