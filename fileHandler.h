//
// Created by אורי חביב on 12/09/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include "chessGame.h"


#define XML_HEADLINE "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
#define GAME "game"
#define CURRENT_TURN "current_turn"
#define MODE "game_mode"
#define LEVEL "difficulty"
#define COLOR "user_color"
#define BOARD "board"
#define ROW "row_"



#ifndef FINALPROJECT_FILEHANDLER_H
#define FINALPROJECT_FILEHANDLER_H




/**
 * Start new label with given number of tabs in XML file.
 *
 * @param label - the label's name
 * @param tabs - num of tabs before the label
 * @param gameFile - a pointer the the file
 */

void startLabel(char *label, int tabs, FILE* gameFile);


/**
 * End label with given number of tabs in XML file.
 *
 * @param label - the label's name
 * @param tabs - num of tabs before the label
 * @param gameFile - a pointer the the file
 */

void endLabel(char *label, int tabs, FILE* gameFile);


/**
 * Start a new label and end it, with given number of tabs in XML file.
 *
 * @param label - the label's name
 * @param str - the data in the label
 * @param tabs - num of tabs before the label
 * @param gameFile - a pointer the the file
 */

void startAndEndLabel(char *label, char *str, int num, int tabs, FILE* gameFile);


/**
 * Writing a board into the XML file
 *
 * @param gameFile - a pointer the the file
 * @param game - the current game
 */


void writeBoardData(FILE* gameFile, SPChessGame* game);



/**
 * Saving a game into the XML file
 *
 * @param filePath - a path to a file
 * @param game - the current game
 *
 * @return
 * 0 - Game can not be saved
 * 1 - Game has been saved
 *
 */

int saveGame(char *filePath, SPChessGame* game);



/**
 * Extracting label's info from a label
 *
 * @param info - a pointer to the string the info will be written into
 * @param label - a pointer to the label
 *
 */

void getLabelInfo(char* info, char* label);



/**
 * loading a game from the XML file
 *
 * @param filePath - a path to a file
 * @param game - the current game
 *
 * @return
 * true - if the game was loaded
 * false - otherwise

 */

bool loadChessGame(SPChessGame **game, char *filePath);




#endif //FINALPROJECT_FILEHANDLER_H
