//
// Created by אורי חביב on 05/09/2017.
//

#ifndef SPFINAL_CHESSGAME_H
#define SPFINAL_CHESSGAME_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include "SPArrayList.h"
#include "chessParser.h"



//Definitions
#define GAMESIZE 8
#define HISTORYSIZE 6
#define BLANK '_'
#define PAWNWHITE 'm'
#define PAWNBLACK 'M'
#define BISHOPBLACK 'B'
#define BISHOPWHITE 'b'
#define ROOKWHITE 'r'
#define ROOKBLACK 'R'
#define KNIGHTWHITE 'n'
#define KNIGHTBLACK 'N'
#define QUEENWHITE 'q'
#define QUEENBLACK 'Q'
#define KINGWHITE 'k'
#define KINGBLACK 'K'



/**
 * chessGame Summary:
 *
 * A container that represents a chess game, a two players
 *
 * Create           - Creates a new game board
 * GameCopy             - Copies a game board
 * GameDestroy          - Frees all memory resources associated with a game
 * GameSetMove          - Sets a move on a game board
 * GameIsValidMove      - Checks if a move is valid
 * GameUndoPrevMove     - Undoes previous move made by the last player
 * GamePrintBoard       - Prints the current board
 * GameGetCurrentPlayer - Returns the current player
 * Player				  - Switches the turn of current player
 *
 */


typedef struct sp_chess_game{
    char gameBoard[GAMESIZE][GAMESIZE];
    int gameMode; // 1 = 1 player, 2 = 2 players
    int currentPlayer;
    int difficulty;
    SPArrayList* lastMoves;
    int userColor; // 0 = black, 1 = white
    int state; // settings = 0, game = 1
} SPChessGame;



/**
 * Type used for returning error codes from game functions
 */
typedef enum sp_fiar_game_message_t {
    SP_FIAR_GAME_INVALID_MOVE,
    SP_FIAR_GAME_INVALID_ARGUMENT,
    SP_FIAR_GAME_NO_HISTORY,
    SP_FIAR_GAME_SUCCESS,
} SP_CHESS_GAME_MESSAGE;

/**
 * Creates a new game with a specified history size. The history size is a
 * parameter which specifies the number of previous moves to store. If the number
 * of moves played so far exceeds this parameter, then first moves stored will
 * be discarded in order for new moves to be stored.
 *
 * @historySize - The total number of moves to undo,
 *                a player can undo at most historySizeMoves turns.
 * @return
 * NULL if either a memory allocation failure occurs or historySize <= 0.
 * Otherwise, a new game instant is returned.
 */
SPChessGame* spFiarGameCreate();




/**
 *	Creates a copy of a given game.
 *	The new copy has the same status as the src game.
 *
 *	@param src - the source game which will be copied
 *	@return
 *	NULL if either src is NULL or a memory allocation failure occurred.
 *	Otherwise, an new copy of the source game is returned.
 *
 */
SPChessGame* spChessGameCopy(SPChessGame* src);

/**
 * Frees all memory allocation associated with a given game. If src==NULL
 * the function does nothing.
 *
 * @param src - the source game
 */
void chessGameDestroy(SPChessGame* src);



///**
// * Sets the next move in a given game by specifying column index. The
// * columns are 0-based and in the range [0,SP_FIAR_GAME_N_COLUMNS -1].
// *
// * @param src - The target game
// * @param col - The target column, the columns are 0-based
// * @return
// * SP_FIAR_GAME_INVALID_ARGUMENT - if src is NULL or col is out-of-range
// * SP_FIAR_GAME_INVALID_MOVE - if the given column is full.
// * SP_FIAR_GAME_SUCCESS - otherwise
// */
//SP_FIAR_GAME_MESSAGE spFiarGameSetMove(SPFiarGame* src, int col);



///**
// * Checks if a disk can be put in the specified column.
// *
// * @param src - The source game
// * @param col - The specified column
// * @return
// * true  - if the a disc can be put in the target column
// * false - otherwise.
// */
//bool spFiarGameIsValidMove(SPFiarGame* src, int col);




///**
// * Removes a disc that was put in the previous move and changes the current
// * player's turn. If the user invoked this command more than historySize times
// * in a row then an error occurs.
// *
// * @param src - The source game
// * @return
// * SP_FIAR_GAME_INVALID_ARGUMENT - if src == NULL
// * SP_FIAR_GAME_NO_HISTORY       - if the user invoked this function more then
// *                                 historySize in a row.
// * SP_FIAR_GAME_SUCCESS          - on success. The last disc that was put on the
// *                                 board is removed and the current player is changed
// */
//SP_FIAR_GAME_MESSAGE spFiarGameUndoPrevMove(SPFiarGame* src);





/**
 * On success, the function prints the board game. If an error occurs, then the
 * function does nothing. The characters 'X' and 'O' are used to represent
 * the discs of player 1 and player 2, respectively.
 *
 * @param src - the target game
 * @return
 * SP_FIAR_GAME_INVALID_ARGUMENT - if src==NULL
 * SP_FIAR_GAME_SUCCESS - otherwise
 *
 */
SP_CHESS_GAME_MESSAGE spChessGamePrintBoard(SPChessGame* src);



/**
 * Returns the current player of the specified game.
 * @param src - the source game
 * @return
 * 1 - if it's the turn of the white player
 * 0 - if it's the turn of the black player
 */
int spChessGameGetCurrentPlayer(SPChessGame* src);





///**
//* Checks if there's a winner in the specified game status. The function returns either
//* SP_FIAR_GAME_PLAYER_1_SYMBOL or SP_FIAR_GAME_PLAYER_2_SYMBOL in case there's a winner, where
//* the value returned is the symbol of the winner. If the game is over and there's a tie
//* then the value SP_FIAR_GAME_TIE_SYMBOL is returned. in any other case the null characters
//* is returned.
//* @param src - the source game
//* @return
//* SP_FIAR_GAME_PLAYER_1_SYMBOL - if player 1 won
//* SP_FIAR_GAME_PLAYER_2_SYMBOL - if player 2 won
//* SP_FIAR_GAME_TIE_SYMBOL - If the game is over and there's a tie
//* null character - otherwise
//*/
//char spFiarCheckWinner(SPFiarGame* src);
//
//
///**
//* Switching the turns of the players in the specified game.
//* @param src - the source game
//*/
//void switchPlayer(SPFiarGame* src);




///**
//* Switching the game's state to setting the specified game.
//* @param src - the source game
//*/
//void changeToSetting(SPChessGame* src);

#endif //SPFINAL_CHESSGAME_H
