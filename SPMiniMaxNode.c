//
// Created by Omer Koren & Ori Haviv 2017
//

#include "SPMiniMaxNode.h"


int soldierScore(char soldier) {
    switch (soldier) {
        case BLANK:
            return BLANKSCORE;
        case PAWNWHITE:
            return PAWNWHITESCORE;
        case PAWNBLACK:
            return PAWNBLACKSCORE;
        case BISHOPWHITE:
            return BISHOPWHITESCORE;
        case BISHOPBLACK:
            return BISHOPBLACKSCORE;
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
        default:
            return 0;
    }
}

int scoreOfLeafNode(SPChessGame *currentGame) {
    SP_CHESS_GAME_STATE msg = chessCheckWinner(currentGame, 1, 0);
    if (msg == SP_CHESS_GAME_WHITE_WINNER) {         // white player won
        return INT_MAX;
    } else if (msg == SP_CHESS_GAME_BLACK_WINNER) {    // black player won
        return INT_MIN;
    } else if (msg == SP_CHESS_GAME_TIE) { return 999; } // tie
    int score = 0;
    for (int i = 0; i < GAMESIZE; i++) {
        for (int j = 0; j < GAMESIZE; j++) {
            score += soldierScore(currentGame->gameBoard[i][j]);
        }
    }
    return score;
}

int scoreOfLeafNodeExpert(SPChessGame *currentGame) {
    int score = scoreOfLeafNode(currentGame);
    char currentPiece;
    if (score == INT_MIN || score == INT_MAX){ return score; }
    score *= 5;
    position pos;
    for (int i = 0; i < GAMESIZE; i++) {
        for (int j = 0; j < GAMESIZE; j++) {
            pos.row = i;
            pos.column = j;
            currentPiece = currentGame->gameBoard[i][j];
            if (currentGame->currentPlayer == 1 - getColor(currentPiece)) {
                if (isTheSoldierThreatened(currentGame, 1 - currentGame->currentPlayer, pos)) {
                    if (currentPiece != KINGWHITE && currentPiece != KINGBLACK) {
                        score -= soldierScore(currentPiece);
                    } else if (currentPiece == KINGWHITE) {
                        score -= 20;
                    } else {                // Current piece == KINGBLACK
                        score += 20;
                    }
                }
            }
        }
    }
    return score;
}


int nodeScore(SPChessGame *src, int depth, int player, int alpha, int beta, int isGui, int isExpert) {
    if ((src == NULL) || (depth < 0) || (depth > 4) || (player < 0) || (player > 1)) {
        return -999;
    }
    SPChessGame* gameCopy = (chessGameCopy(src));
    int bestScore;
    SPArrayList* possibleActions;
    char currentSoldier;
    int scoreOfCurrent = 0;
    if (isExpert == 1) { scoreOfCurrent = scoreOfLeafNodeExpert(gameCopy); }
    else { scoreOfCurrent = scoreOfLeafNode(gameCopy); }

    if ((depth == 0) || (scoreOfCurrent == INT_MAX) || (scoreOfCurrent ==  INT_MIN)) {
        return scoreOfCurrent;
    } else if (scoreOfCurrent == 999){
        return 0;
    }

    action move;
    if (player == 1) {         // white's turn
        bestScore = INT_MIN;
        for (int i = 0; i < GAMESIZE; i++) {
            for (int j = 0; j < GAMESIZE; j++) {
                currentSoldier = gameCopy->gameBoard[i][j];
                if (isWhite(currentSoldier)) {
                    possibleActions = getMovesForSoldier(gameCopy, i, j);
                    for (int index = 0; index < possibleActions->actualSize; index++) {
                        move = *(spArrayListGetAt(possibleActions, index));
                        if (move.castling == SP_CHESS_NO_CASTLING) {
                            chessGameSetMove(gameCopy, move.prev, move.current, 1, 0);
                            bestScore = maxi(bestScore, nodeScore(gameCopy, depth - 1, 1 - player, alpha, beta, isGui, isExpert));
                            chessGameUndoPrevMove(gameCopy);
                            alpha = maxi(bestScore, alpha);
                            if (beta <= alpha) { break; }
                        }
                    }
                    spArrayListDestroy(&possibleActions);
                }
            }
        }
    }
    else {                  //  black's turn
        bestScore = INT_MAX;
        for (int i = 0; i < GAMESIZE; i++) {
            for (int j = 0; j < GAMESIZE; j++) {
                currentSoldier = gameCopy->gameBoard[i][j];
                if (isBlack(currentSoldier)) {
                    possibleActions = getMovesForSoldier(gameCopy, i, j);
                    for (int index = 0; index < possibleActions->actualSize; index++) {
                        move = *(spArrayListGetAt(possibleActions, index));
                        if (move.castling == SP_CHESS_NO_CASTLING) {
                            chessGameSetMove(gameCopy, move.prev, move.current, 1, 0);
                            bestScore = mini(bestScore, nodeScore(gameCopy, depth - 1, 1 - player, alpha, beta, isGui, isExpert));
                            chessGameUndoPrevMove(gameCopy);
                            beta = mini(bestScore, beta);
                            if (beta <= alpha) { break; }
                        }
                    }
                    spArrayListDestroy(&possibleActions);
                }
            }
        }
    }
    chessGameDestroy(&gameCopy);
    return bestScore;
}
