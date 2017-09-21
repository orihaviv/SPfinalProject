#ifndef SPMINIMAX_H_
#define SPMINIMAX_H_


#include "SPMiniMaxNode.h"


/**
 * Given a game state, this function evaluates the best move according to
 * the current player. The function initiates a MiniMax algorithm up to a
 * specified length given by difficulty. The current game state doesn't change
 * by this function including the history of previous moves.
 *
 * @param currentGame - The current game state
 * @param depth - The maximum depth of the miniMax algorithm
 * @return
 * NULL if either currentGame is NULL or maxDepth <= 0.
 * On success the function returns an optimized action.
 * which is the best move for the current player.
 */
action* spMinimaxSuggestMove(SPChessGame* currentGame, int depth);

#endif
