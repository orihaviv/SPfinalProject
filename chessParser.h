//
// Created by Omer Koren & Ori Haviv 2017
//


#ifndef SPFINAL_CHESSPARSER_H
#define SPFINAL_CHESSPARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

//specify the maximum line length
#define SP_MAX_LINE_LENGTH 1024
//converting char to int
#define colToInt(a) (a - 65)


//a type used to represent a command
typedef enum {
    GAME_MODE,
    DIFFICULTY,
	USER_COLOR,
	LOAD,
	DEFAULT_GAME,
	PRINT_SETTING,
	MOVE,
	CASTLE,
	GET_MOVES,
	START,
	SAVE,
	UNDO,
	RESET,
	INVALID,
	IGNORE,
	QUIT,
} SP_COMMAND;

typedef struct position_on_board {
	int row;
	int column;
} position;



//a new type that is used to encapsulate a parsed line
typedef struct command_t {
	SP_COMMAND cmd;
	position source;
	position destination;
	int arg;
	char* path;
} SPCommand;

typedef enum sp_chess_castling_state_t {
    SP_CHESS_NO_CASTLING,
    SP_CHESS_BLACK_LEFT_CASTLING,
    SP_CHESS_BLACK_RIGHT_CASTLING,
    SP_CHESS_WHITE_LEFT_CASTLING,
    SP_CHESS_WHITE_RIGHT_CASTLING,
} SP_CHESS_CASTLING_STATE;

/**
 * Checks if a specified string represents a valid integer. It is recommended
 * to use this function prior to calling the standard library function atoi.
 *
 * @return
 * true if the string represents a valid integer, and false otherwise.
 */
bool spParserIsInt(const char* str);


/**
 * Sets a game mode command
 *
 * @param mode - wanted game mode
 *
 * @return the entire command
 */
SPCommand setGameModeCmd (char* mode);


/**
 * Sets a difficulty command
 *
 * @param diff - wanted difficulty
 *
 * @return the entire command
 */
SPCommand setDifficultyCmd(char* diff);


/**
 * Sets a color command
 *
 * @param color - wanted color for the user
 *
 * @return the entire command
 */
SPCommand setColorCmd(char* color);


/**
 * Sets a castle command
 *
 * @param origin - the position of te wanted rook
 *
 * @return the entire command
 */
SPCommand setCastleCmd(char* origin);


/**
 * Sets a move command
 *
 * @param source - the origin position of the wanted piece
 * @param dest - the destination position of the wanted piece
 *
 * @return the entire command
 */
SPCommand setMoveCmd(char* source, char* dest);


/**
 * Sets a get move command
 *
 * @param source - the position of the wanted piece
 *
 * @return the entire command
 */
SPCommand getMoveCmd(char* source);


/**
 * returns the relevant piece's char of the input string
 *
 * @param src - the source string
 *
 * @return relevant char
 */
char getPiece(char* source);


/**
 * Checks whether the command has a valid format
 *
 * @param token - the relevant token of the command
 *
 * @return
 * true - if the format is valid
 * false - otherwise
 */
bool isValidFormat(char* token);


/**
 * Parses a specified line. If the line is a command which has an integer
 * argument then the argument is parsed and is saved in the field arg and the
 * field validArg is set to true. In any other case then 'validArg' is set to
 * false and the value 'arg' is undefined
 *
 * @return
 * A parsed line such that:
 *   cmd - contains the command type, if the line is invalid then this field is
 *         set to INVALID_LINE
 *   validArg - is set to true if the command is add_disc and the integer argument
 *              is valid
 *   arg      - the integer argument in case validArg is set to true
 */
SPCommand spParserParseLine(const char* str);

#endif
