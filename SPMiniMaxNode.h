#ifndef SPMINIMAXNODE_H_

#define SPMINIMAXNODE_H_
#include "chessGame.h"

//Definitions
#define BLANKSCORE 0
#define PAWNWHITESCORE 1
#define PAWNBLACKSCORE -1
#define BISHOPWHITESCORE 3
#define BISHOPBLACKSCORE -3
#define KNIGHTWHITESCORE 3
#define KNIGHTBLACKSCORE -3
#define ROOKWHITESCORE 5
#define ROOKBLACKSCORE -5
#define QUEENWHITESCORE 9
#define QUEENBLACKSCORE -9
#define KINGWHITESCORE 100
#define KINGBLACKSCORE -100

/**
 * Given a representative char of a soldier,
 * returns the score of the specific soldier.
 *
 * @param soldier - a representative char of a soldier
 * @return - the relevant score of the specific soldier
 */
int soldierScore(char soldier);

/**
 * Given a game state, this function evaluates the score of the board according
 * to the scoring function.
 *The current game state doesn't change
 * by this function, including the history of previous moves.
 *
 * @param currentGame - The current game state
 * @return
 * -1 if the currentGame is NULL. //TODO!!!
 * On success the function returns a number represents the board's score if there's no winner.
 * INT_MAX if the white player is the winner in this game state.
 * INT_MIN if the black player is the winner in this game state.
 */
int scoreOfLeafNode(SPChessGame* currentGame);


/**
 * Given a game state,depth, and the current player this function evaluates the score
 * of the game stats according to the current player.
 * The function initiates a MiniMax algorithm up to a specified length given by the depth. given.
 * The current game state doesn't change by this function including the history of previous moves.
 *
 * @param currentGame - The current game state
 * @param depth - The depth of the miniMax algorithm
 * @param player - The current player the miniMax algorithm is calculated for
 *          0 - black, 1 - white
 * @param alpha - The "alpha" parameter for the minimax
 * @param beta - The "beta" parameter for the minimax
 * @param isGui - indicates if is in GUI mode
 * @return
 * -999 if either currentGame is NULL or depth < 0 or invalid number represents the player.
 * On success the function returns a number represents the board's score if there's no winner.
 * INT_MAX if the user is the winner in this game state.
 * INT_MIN if the cSPFiarGameomputer is the winner in this game state.
 * 0 if the game is a tie.
 */
int nodeScore(SPChessGame *src, int depth, int player, int alpha, int beta, int isGui);


#endif
