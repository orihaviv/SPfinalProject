//
// Created by ׳³ן¿½׳³ג€¢׳³ֲ¨׳³ג„¢ ׳³ג€”׳³ג€˜׳³ג„¢׳³ג€˜ on 10/06/2017.
//
#include "SPMiniMaxNode.h"
#include "chessGame.h"

int soldierScore(char soldier){
	switch(soldier){
		case BLANK: return BLANKSCORE;
		case PAWNWHITE: return PAWNWHITESCORE;
		case PAWNBLACK: return PAWNWBLACKSCORE;
		case BISHOPWHITE: return BISHOPWHITESCORE;
		case BISHOPBLACK: return BISOPBLACKSCORE;
		case ROOKWHITE: return ROOKWHITESCORE;
		case ROOKBLACK: return ROOKBLACKSCORE;
		case KNIGHTWHITE: return KNIGHTWHITESCORE;
		case KNIGHTBLACK: return KNIGHTBLACKSCORE;
		case QUEENWHITE: return QUEENWHITESCORE;
		case QUEENBLACK: return QUEENBLACKSCORE;
		case KINGWHITE: return KINGWHITESCORE;
		case KINGBLACK: return KINGBLACKSCORE;
	}
}

int scoreOfLeafNode(SPChessGame* currentGame){
	int score = chessCheckWinner(currentGame);
	if (score == 1){
		return INT_MAX;
	}
	else if (score == 0){
		return INT_MIN;
	}
	score = 0;
	for(int i=0 ; i < GAMESIZE ; i++){
		for(int j=0 ; j < GAMESIZE ; j++){
			score += soldierScore(currentGame.gameBoard[i][j]);
		}
	}
	return score;
}


int nodeScore(SPFiarGame* src, int depth, int player){
    if ((src == NULL) || (depth < 0) || (depth > 4) || (player < 0) || (player >1)){  //TODO change >4 to >5 if needed
        return -1;
    }
    SPChessGame* gameCopy = (chessGameCopy(src));
    int score;
    int bestScore = player == 1 ? INT_MIN : INT_MAX;
    int first;
    int scoreOfCurrent = scoreOfLeafNode(gameCopy);
//    if ((depth != 0) && (scoreOfCurrent < INT_MAX) && (scoreOfCurrent > INT_MIN)){
//        for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++){
//            if (spFiarGameIsValidMove(gameCopy, i)) {
//                first = spArrayListGetFirst(gameCopy->lastMoves);
//                spFiarGameSetMove(gameCopy, i);
//                score = (nodeScore(gameCopy, depth - 1, 1 - player));
//                if (player == 1) {
//                    if (bestScore > score) {
//                        bestScore = score;
//                    }
//                }
//                else{
//                    if (score > bestScore) {
//                        bestScore = score;
//                    }
//                }
//                gameCopy->gameBoard[gameCopy->tops[i]-1][i] = SP_FIAR_GAME_EMPTY_ENTRY;
//                switchPlayer(gameCopy);
//                spArrayListRemoveLast(gameCopy->lastMoves);
//                if(gameCopy->lastMoves->actualSize == gameCopy->lastMoves->maxSize-1){
//                    spArrayListAddFirst(gameCopy->lastMoves, first);
//                }
//                gameCopy->tops[i]--;
//            }
//        }
//        spFiarGameDestroy(gameCopy);
//        return bestScore;
//    }
//    else {
//        spFiarGameDestroy(gameCopy);
//        return scoreOfCurrent;
//    }
}
