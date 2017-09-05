#ifndef SPMINIMAXNODE_H_

#define SPMINIMAXNODE_H_
#include "SPFIARGame.h"

/**
 * Given a game state,depth, and the current player this function evaluates the score
 * of the game stats according to the current player.
 * The function initiates a MiniMax algorithm up to a specified length given by the depth. given.
 * The current game state doesn't change by this function including the history of previous moves.
 *
 * @param currentGame - The current game state
 * @param depth - The depth of the miniMax algorithm
 * @param player - The current player the miniMax algorithm is calculated for
 *                 0 - user, 1 - computer
 * @return
 * -1 if either currentGame is NULL or depth < 0 or invalid number represents the player.
 * On success the function returns a number represents the board's score if there's no winner.
 * INT_MAX if the user is the winner in this game state.
 * INT_MIN if the computer is the winner in this game state.
 */
int nodeScore(SPFiarGame* src, int depth, int player);



/**
 * Given a game state, this function evaluates the score of the board according
 * to the scoring function.
 *The current game state doesn't change
 * by this function including the history of previous moves.
 *
 * @param currentGame - The current game state
 * @return
 * -1 if the currentGame is NULL.
 * On success the function returns a number represents the board's score if there's no winner.
 * INT_MAX if the user is the winner in this game state.
 * INT_MIN if the computer is the winner in this game state.
 */
int scoreOfLeafNode(SPFiarGame* currentGame);

#endif
