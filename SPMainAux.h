#ifndef SPMAINAUX_H_
#define SPMAINAUX_H_


#include "SPMiniMax.h"
#include "fileHandler.h"



/**
 * Loading into src the game described in the file the path leads to
 *
 *
 * @param src - A pointer to the target game to load into
 * @param src - The path to the required game
 * @return

 */
void loadGame (SPChessGame** src, char* path);



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
 * @param gamePointer - A pointer to the current game
 *
 * @return
 * 0 - if the command is to quit the game at this point.
 * 1 - if the command is to start the game.
 */


int settings(SPChessGame **gamePointer);




/**
 * Translating the char representing the soldier to its name.
 *
 * @param soldier - the soldier's representing char
 *
 * @return the name of the soldier's piece
 *
 */

char* translateToSoldiersName(char soldier);


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
 * @param command - The command to execute
 *
 * @return
 * 1 - if src is continued.
 * 0 - if the user quit the game in this turn.
 */

int executePlayerMove (SPChessGame* src, SPCommand command);


/**
 * Executing white left castling move.
 *
 * @param src - The target game
 */
void executeWhiteLeftCastling(SPChessGame *src);


/**
 * Executing white right castling move.
 *
 * @param src - The target game
 */
void executeWhiteRightCastling(SPChessGame *src);


/**
 * Executing black left castling move.
 *
 * @param src - The target game
 */
void executeBlackLeftCastling(SPChessGame *src);


/**
 * Executing black right castling move.
 *
 * @param src - The target game
 */
void executeBlackRightCastling(SPChessGame *src);


/**
 * Executing castling move.
 *
 * @param src - The target game
 * @param command - The command to execute
 *
 * @return
 * 1 - if castling succeeded
 * 0 - if castling didn't succeed
 */

int executeCastling(SPChessGame *src, SPCommand command);


/**
 * Printing suggested valid moves for the user.
 *
 * @param game - The target game
 * @param command - The "get moves" command to execute
 *
 *
 */

void executeGetMoves(SPChessGame *game, SPCommand command);




/**
 * Executing an "Undo" command if legal.
 *
 * @param game - The target game
 *
 */

void executeUndo(SPChessGame *game);


/**
 * Saving the game.
 *
 * @param game - The target game
 * @param command - The "save" command to execute
 *
 */

void executeSave(SPChessGame* game, SPCommand command);


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

SPCommand gameState (SPChessGame *game);



/**
 * Printing the winner
 *
 * @param msg - The game winner message
 *
 */


void printWinnerMessage(SP_CHESS_GAME_STATE msg, SPChessGame *game);



#endif
