//
// Created by Omer Koren & Ori Haviv 2017
//

#ifndef SPFINAL_CHESSGAME_H
#define SPFINAL_CHESSGAME_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include "SPArrayList.h"



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

#define toColChar(a) a+65
#define toRowNum(a) a+1
#define maxi(a, b) (a > b ? a : b)
#define mini(a, b) (a < b ? a : b)


/**
 * chessGame Summary:
 *
 * A container that represents a chess game, a two players
 *
 * Create           - Creates a new game board
 * GameCopy             - Copies a game board
 * GameDestroy          - Frees all memory resources associated with a game //// TODO
 * GameSetMove          - Sets a move on a game board
 * GameIsValidMove      - Checks if a move is valid
 * GameUndoPrevMove     - Undoes previous move made by the last player
 * GamePrintBoard       - Prints the current board
 * GameGetCurrentPlayer - Returns the current player
 * Player				  - Switches the turn of current player
 *
 */


typedef struct sp_chess_game {
    char gameBoard[GAMESIZE][GAMESIZE];
    int gameMode; // 1 = 1 player, 2 = 2 players
    int currentPlayer;
    int difficulty;
    SPArrayList *lastMoves;
    int userColor; // 0 = black, 1 = white
    int state; // settings = 0, game = 1
    position whiteKing;
    position blackKing;
    int whiteLeftCastling;
    int whiteRightCastling;
    int blackLeftCastling;
    int blackRightCastling;
} SPChessGame;


/**
 * Type used for returning error codes from game functions
 */
typedef enum sp_chess_game_message_t {
    SP_CHESS_GAME_ILLEGAL_MOVE,
    SP_CHESS_GAME_SOLDIER_MISMATCH,
    SP_CHESS_GAME_INVALID_POSITION_ON_BOARD,
    SP_CHESS_GAME_INVALID_ARGUMENT,
    SP_CHESS_GAME_NO_HISTORY,
    SP_CHESS_GAME_SUCCESS,
} SP_CHESS_GAME_MESSAGE;


/**
 * Type used for returning game's state
 */
typedef enum sp_chess_game_state_t {
    SP_CHESS_GAME_TIE,
    SP_CHESS_GAME_WHITE_WINNER,
    SP_CHESS_GAME_BLACK_WINNER,
    SP_CHESS_GAME_NO_WINNER,
    SP_CHESS_GAME_INVALID_GAME,
} SP_CHESS_GAME_STATE;



/**
 *	Initializes the game board
 *
 *	@param game - the source game which will be copied
 */
void initializeBoard(SPChessGame* game);

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
SPChessGame *chessGameCreate();


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
SPChessGame *chessGameCopy(SPChessGame *src);

/**
 * Frees all memory allocation associated with a given game. If src==NULL
 * the function does nothing.
 *
 * @param src - the source game
 */
void chessGameDestroy(SPChessGame **src);


/**
 * Returns the soldier in the given position on board
 * @param src - the source game
 * @paran pos - the position
 *
 * @return the char of the soldier on the board
 * \0 if illegal position
 */
char whosThere(SPChessGame *src, int row, int col);


/**
 * returns the relevant king's position
 * @param src - the source game
 * @param color - which king do we check
 *
 * @return king's position
 */
position getKingPosition(SPChessGame *src, int color);


/**
 * returns the color of a specific piece
 *
 * @param soldier - the specific piece
 *
 * @return the relevant color
 */
int getColor(char soldier);


/**
 * Checks if the soldier is under threat(Check) by a rival's pawn
 * @param src - the source game
 * @param color - which king do we check
 *
 * @return true if the soldier is threatened by a pawn
 * false otherwise
 */

bool pawnsThreatSoldier(SPChessGame *src, int color, position soldier);

/**
 * Checks if the soldier is under threat(Check) by a rival's knight
 * @param src - the source game
 * @param color - which king do we check
 *
 * @return true if the soldier is threatened by a knight
 * false otherwise
 */

bool knightsThreatSoldier(SPChessGame *src, int color, position soldier);

/**
 * Checks if the soldier is under threat(Check) by a rival's king
 * @param src - the source game
 * @param color - which king do we check
 *
 * @return true if the soldier is threatened by a king
 * false otherwise
 */

bool kingThreatensSoldier(SPChessGame *src, int color, position soldier);



/**
 * Checks if there is a threat, in the determined lane, by a rival's Queen, Rook or Bishop
 * @param src - the source game
 * @param x - steps in x axis
 * @param y - steps in y axis
 * @param soldier - soldier's position
 * @param queen - rival's queen
 * @param other - rival's bishop or rook, depends on the lane
 *
 * @return true if the soldier is threatened by a Queen, Rook or Bishop in the specified lane
 * false otherwise
 */


bool checkLane(SPChessGame *src, int x, int y, position soldier, char queen, char other);


/**
 * Checks if the soldier is under threat(Check) by a rival's Queen, Rook or Bishop
 * @param src - the source game
 * @param color - which soldier do we check
 *
 * @return true if the soldier is threatened by a Queen, Rook or Bishop
 * false otherwise
 */

bool QRBThreatensSoldier(SPChessGame *src, int color, position soldier);


/**
 * Checks if the king is under threat(Check)
 * @param src - the source game
 * @param color - which king do we check
 *
 * @return true if the king is threatened
 * false otherwise
 */

bool isTheKingThreatened(SPChessGame *src, int color);


/**
 * Checks if the soldier is under threat(Check)
 * @param src - the source game
 * @param color - which soldier do we check
 *
 * @return true if the king is threatened
 * false otherwise
 */

bool isTheSoldierThreatened(SPChessGame *src, int color, position soldier);




/**
 * Simulate the next move and checks if the king is under threat(Check)
 * @param src - the source game
 * @param origin - the origin of the soldier
 * @param dest - the destination of the soldier
 *
 * @return true if the king is threatened in case the move is done
 * false otherwise
 */

bool isMoveRiskTheKing(SPChessGame *src, position origin, position dest);


/**
* Checks if the position is on board
* @param pos - the position we want to check
* @return true if it is on the board
* false otherwise
*/

bool posOnBoard(position pos);



/**
* Checks if the soldier is black
* @param soldier - the char of the soldier
* @return true if it is black
* false otherwise
*/
bool isBlack(char soldier);




/**
* Checks if the soldier is black
* @param soldier - the char of the soldier
* @return true if it is black
* false otherwise
*/

bool isWhite(char soldier);


/**
* Checks if a pawn can be moved from origin to destination.
*
* @param src - The source game
* @param origin - The origin position of the soldier
* @param dest - The destination position of the soldier
* @return
* true  - if the move is possible
* false - otherwise.
*/

bool pawnValidMove(SPChessGame *src, position origin, position dest);


/**
* Checks if a knight can be moved from origin to destination.
*
* @param origin - The origin position of the soldier
* @param dest - The destination position of the soldier
* @return
* true  - if the move is possible
* false - otherwise.
*/


bool knightValidMove(position origin, position dest);



/**
* Checks if a king can be moved from origin to destination.
*
* @param origin - The origin position of the soldier
* @param dest - The destination position of the soldier
* @return
* true  - if the move is possible
* false - otherwise.
*/



bool kingValidMove(position origin, position dest);


/**
* Checks if a rook can be moved from origin to destination.
*
* @param src - The source game
* @param origin - The origin position of the soldier
* @param dest - The destination position of the soldier
* @return
* true  - if the move is possible
* false - otherwise.
*/

bool rookValidMove(SPChessGame *src, position origin, position dest);


/**
* Checks if a bishop can be moved from origin to destination.
*
* @param src - The source game
* @param origin - The origin position of the soldier
* @param dest - The destination position of the soldier
* @return
* true  - if the move is possible
* false - otherwise.
*/


bool bishopValidMove(SPChessGame *src, position origin, position dest);

/**
* Checks if a queen can be moved from origin to destination.
*
* @param src - The source game
* @param origin - The origin position of the soldier
* @param dest - The destination position of the soldier
* @return
* true  - if the move is possible
* false - otherwise.
*/


bool queenValidMove(SPChessGame *src, position origin, position dest);


/**
* Checks if a soldier can be moved from origin to destination.
*
* @param src - The source game
* @param origin - The origin position of the soldier
* @param dest - The destination position of the soldier
* @return
*   SP_CHESS_GAME_ILLEGAL_MOVE - illegal move with the wanted soldier
*   SP_CHESS_GAME_SOLDIER_MISMATCH - the origin is not position of a current player's soldier
*   SP_CHESS_GAME_INVALID_POSITION_ON_BOARD - one of the positions is not on the board
*   SP_CHESS_GAME_INVALID_ARGUMENT - if src is NULL
*   SP_CHESS_GAME_SUCCESS - The move is valid
*
*/
SP_CHESS_GAME_MESSAGE isValidMove(SPChessGame *src, position origin, position dest);



/**
 * Promoting a pawn.
 *
 * @param src - The current game
 * @param move - the action leaded to the promotion
 * @param isMini - indicates if the move is part of the miniMax prediction
 */


void pawnPromotion (SPChessGame* src, action move, int isMini);


/**
 * Sets the next move in a given game by specifying origin position and destination position.
 *
 * @param src - The current game
 * @param origin - the origin position of the soldier
 * @param dest - the destination position of the soldier
 * @param isMini - indicates if the move is part of the miniMax prediction
 * @param isGui - indicates if the move is in a gui mode game
 * @return
 *   SP_CHESS_GAME_ILLEGAL_MOVE - illegal move with the wanted soldier
 *   SP_CHESS_GAME_SOLDIER_MISMATCH - the origin is not position of a current player's soldier
 *   SP_CHESS_GAME_INVALID_POSITION_ON_BOARD - one of the positions is not on the board
 *   SP_CHESS_GAME_INVALID_ARGUMENT - if src is NULL
 *   SP_CHESS_GAME_SUCCESS - on success
 */

SP_CHESS_GAME_MESSAGE chessGameSetMove(SPChessGame* src, position origin , position dest, int isMini, int isGui);

/**
* Undo a regular move
*
* @param src - The source game
* @param lastMove - The last action done
*/
void regularUndo(SPChessGame* src , action lastMove);


/**
* Undo a castling move
*
* @param src - The source game
* @param lastMove - The last action done
*/
void castlingUndo(SPChessGame* src , action lastMove);


/**
 * Indicates whether white left castling is valid.
 *
 * @param src - The target game
 *
 * @return
 * 1 - if castling is valid
 * 0 - otherwise
 */
int isWhiteLeftCastlingValid(SPChessGame *src);


/**
 * Indicates whether white right castling is valid.
 *
 * @param src - The target game
 *
 * @return
 * 1 - if castling is valid
 * 0 - otherwise
 */
int isWhiteRightCastlingValid(SPChessGame *src);

/**
 * Indicates whether black left castling is valid.
 *
 * @param src - The target game
 *
 * @return
 * 1 - if castling is valid
 * 0 - otherwise
 */
int isBlackLeftCastlingValid(SPChessGame *src);


/**
 * Indicates whether black right castling is valid.
 *
 * @param src - The target game
 *
 * @return
 * 1 - if castling is valid
 * 0 - otherwise
 */
int isBlackRightCastlingValid(SPChessGame *src);



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
 * @param isMini - indicates if the execution is in minimax
 * @param isGui - indicates if is in GUI mode
 *
 * @return
 * 1 - if castling succeeded
 * 0 - if castling didn't succeed
 */

int executeCastling(SPChessGame *src, SPCommand command, int isMini, int isGui);


/**
 * Executing castling move for the computer
 *
 * @param src - The target game
 * @param origin - The origin position of the move to execute
 * @param dst - The destination position of the move to execute
 * @param isGui - indicates if is in GUI mode
 *
 * @return
 * 1 - if castling succeeded
 * 0 - if castling didn't succeed
 */
int executeCastlingMiniMax(SPChessGame *src, position origin, position dst, int isGui);


/**
 * Undo the last move happened in the game
 *
 * @param src - The source game
 * @return
 * SP_CHESS_GAME_INVALID_ARGUMENT - if src == NULL
 * SP_CHESS_GAME_NO_HISTORY       - if the user invoked this function more then
 *                                 historySize in a row.
 * SP_CHESS_GAME_SUCCESS          - on success.
 */
SP_CHESS_GAME_MESSAGE chessGameUndoPrevMove(SPChessGame *src);


/**
 * On success, the function prints the board game. If an error occurs, then the
 * function does nothing.
 *
 * @param src - the target game
 * @return
 * SP_CHESS_GAME_INVALID_ARGUMENT - if src is NULL
 * SP_CHESS_GAME_SUCCESS - otherwise
 *
 */
SP_CHESS_GAME_MESSAGE chessGamePrintBoard(SPChessGame *src);


/**
 * On success, the function returns an arrayList of actions.
 * each action is a valid action for the soldier in the given coordinates on board
 *
 * @param src - the game
 * @param row - the soldier's row
 * @param col - the soldier's column
 * @return
 * NULL - if src==NULL
 * actions arrayList - otherwise
 *
 */
SPArrayList *getMovesForSoldier(SPChessGame *src, int row, int col);


/**
* Checks if there's a winner in the specified game status. The function the correct message
* @param src - the source game
* @param isMini - indicates if part of the miniMax proccess
* @param isGui - indicates if in GUI mode
* @return
* SP_CHESS_GAME_STATE message tells what is the winning state
*/
SP_CHESS_GAME_STATE chessCheckWinner(SPChessGame *src, int isMini, int isGui);


#endif//SPFINAL_CHESSGAME_H
