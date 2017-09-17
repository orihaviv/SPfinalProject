#ifndef SPFINAL_CHESSPARSER_H
#define SPFINAL_CHESSPARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

//specify the maximum line length
#define SP_MAX_LINE_LENGTH 1024
//converting char to int
#define rowToInt(a) (a - 49)
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

/**
 * Checks if a specified string represents a valid integer. It is recommended
 * to use this function prior to calling the standard library function atoi.
 *
 * @return
 * true if the string represents a valid integer, and false otherwise.
 */
bool spParserIsInt(const char* str);


/**
 * returns the relevant piece's char of the input string
 * @param src - the source string
 *
 * @return relevant char
 */
char getPiece(char* source);

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
