#ifndef SPMAINAUX_H_
#define SPMAINAUX_H_

//put auxiliary functions and constants used by the main function here.
#include "SPMiniMax.h"



/**
 * Initializing the specified FIAR game level settings of the user.
 *
 *
 * @param src - The target game
 * @return
 * 0 - if the user quits the game at this point.
 * 2 - if the game's level is set legally.
 */
int initialize(SPFiarGame *fiarGame);



/**
 * Executing the command given on the specified SPFiarGame.
 * Does'nt affect the game if the command is illegal or undefined.
 *
 * @param src - The target game
 * @param src - The command that will be executed.
 *
 * @return
 * -1 - if src is NULL.
 * 0 - if the command is to quit the game at this point.
 * 1 - if the command is to restart the game at this point.s
 * 3 - if the command is to suggest move.
 * 2 - otherwize.
 */
int execution (SPFiarGame* src, SPCommand command);


/**
 * Special execution of the command given on the specified SPFiarGame,
 * adjusted to a "game over" situation.
 * Does'nt affect the game if the command is illegal or undefined.
 *
 * @param src - The target game
 * @param src - The command that will be executed.
 *
 * @return
 * -1 - if src is NULL.
 * 0 - if the command is to quit the game at this point.
 * 1 - if the command is to restart the game at this point or undoing tyhe last move.
 * 2 - otherwize - invalid or illegal command.
 */
int executionEnd (SPFiarGame* src, SPCommand command);




/**
 * Printing the "game over" announcement.
 *
 * @param winner - the char represents the winner.
 * @return
 */
void printWinner(char winner);

#endif
