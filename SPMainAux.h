#ifndef SPMAINAUX_H_
#define SPMAINAUX_H_


#include "SPMiniMax.h"



/**
 * Initializing the specified FIAR game level settings of the user.
 *
 *
 * @param src - The target game to load into
 * @param src - The path to the required game
 * @return

 */
void loadGame (SPChessGame* src, char* path);



/**
 * Printing the game's settings
 *
 * @param game - the current game
 */

void printSettings(SPChessGame* game);



/**
 * Managing the settings mode.
 *
 * Does'nt affect the game if the command is illegal for the settings mode or undefined.
 *
 * @param src - The current game
 *
 * @return
 * 0 - if the command is to quit the game at this point.
 * 1 - if the command is to start the game.
 */


int settings(SPChessGame *game);


/**
 * Managing the game mode.
 *
 * Does'nt affect the game if the command is illegal for the game mode or undefined.
 *
 * @param src - The current game
 *
 * @return
 * 0 - if the command is to quit the game at this point.
 * 1 - if the game continues.
 */

int gameState (SPChessGame *game);



/**
 * Executing the next computer move.
 *
 * @param src - The target game
 *
 */

void executeComputerMove(SPChessGame* src);

/**
 * Executing the next user move.
 *
 * @param src - The target game
 *
 * @return
 * 1 - if src is continued.
 * 0 - if the user quit the game in this turn.
 */

int executePlayerMove (SPChessGame* src);


///**
// * Executing the command given on the specified SPFiarGame.
// * Does'nt affect the game if the command is illegal or undefined.
// *
// * @param src - The target game
// * @param src - The command that will be executed.
// *
// * @return
// * -1 - if src is NULL.
// * 0 - if the command is to quit the game at this point.
// * 1 - if the command is to restart the game at this point.s
// * 3 - if the command is to suggest move.
// * 2 - otherwize.
// */
//int execution (SPFiarGame* src, SPCommand command);


///**
// * Special execution of the command given on the specified SPFiarGame,
// * adjusted to a "game over" situation.
// * Does'nt affect the game if the command is illegal or undefined.
// *
// * @param src - The target game
// * @param src - The command that will be executed.
// *
// * @return
// * -1 - if src is NULL.
// * 0 - if the command is to quit the game at this point.
// * 1 - if the command is to restart the game at this point or undoing tyhe last move.
// * 2 - otherwize - invalid or illegal command.
// */
//int executionEnd (SPFiarGame* src, SPCommand command);




///**
// * Printing the "game over" announcement.
// *
// * @param winner - the char represents the winner.
// * @return
// */
//void printWinner(char winner);

#endif
