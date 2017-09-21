//
// Created by אורי חביב on 12/09/2017.
//


#include "fileHandler.h"


void startLabel(char *label, int tabs, FILE *gameFile) {
    // Add tabs
    int i;
    for (i = 0; i < tabs; i++)
        fprintf(gameFile, "%c", '\t');
    fprintf(gameFile, "<%s>\n", label);
}


void endLabel(char *label, int tabs, FILE *gameFile) {
    // Add tabs
    int i;
    for (i = 0; i < tabs; i++)
        fprintf(gameFile, "%c", '\t');
    // End label
    fprintf(gameFile, "</%s>\n", label);
}


void startAndEndLabel(char *label, char *str, int num, int tabs, FILE *gameFile) {

    // Add tabs
    for (int i = 0; i < tabs; i++)
        fprintf(gameFile, "%c", '\t');

    // Data is an integer
    if (str == NULL && num != -1)
        fprintf(gameFile, "<%s>%d</%s>\n", label, num, label);

        // Data is a string
    else if (str != NULL && num == -1)
        fprintf(gameFile, "<%s>%s</%s>\n", label, str, label);

        // No data to write
    else
        fprintf(gameFile, "<%s></%s>\n", label, label);
}


void writeBoardData(FILE *gameFile, SPChessGame *game) {

    char stringLine[GAMESIZE + 1];
    for (int j = GAMESIZE - 1; j >= 0; j--) {
        for (int i = 0; i < GAMESIZE; i++)
            stringLine[i] = game->gameBoard[j][i];
        stringLine[GAMESIZE] = '\0';
        fprintf(gameFile, "\t\t<%s%d>%s</%s%d>\n", ROW, j + 1, stringLine, ROW, j + 1);
    }
    return;
}

//int addToSaved(char* filePath){
//    FILE *gameFile;
//    gameFile = fopen("saved", "w");
//}




int saveGame(char *filePath, SPChessGame *game) {
    FILE *gameFile;
    gameFile = fopen(filePath, "w");
    if (gameFile == NULL) {         // fopen has failed
        return 0;
    }
    fprintf(gameFile, XML_HEADLINE);
    startLabel(GAME, 0, gameFile);
    char *player = (game->currentPlayer == 1) ? "WHITE" : "BLACK";
    startAndEndLabel(CURRENT_TURN, player, -1, 1, gameFile);
    startAndEndLabel(MODE, NULL, game->gameMode, 1, gameFile);
    if (game->gameMode == 1) {
        startAndEndLabel(LEVEL, NULL, game->difficulty, 1, gameFile);
        char *user = (game->userColor == 1) ? "WHITE" : "BLACK";
        startAndEndLabel(COLOR, user, -1, 1, gameFile);
    } else {
        startAndEndLabel(LEVEL, NULL, -1, 1, gameFile);
        startAndEndLabel(COLOR, NULL, -1, 1, gameFile);
    }
    startLabel(BOARD, 1, gameFile);
    writeBoardData(gameFile, game);
    endLabel(BOARD, 1, gameFile);
    endLabel(GAME, 0, gameFile);

    if (fclose(gameFile) != 0) {     // fclose has failed
        return 0;
    }

    return  1;
}


void getLabelInfo(char *info, char *label) {
    int i = 0;
    char *start = strchr(label, '>');
    start++;
    while (start[i] != '<') {
        info[i] = start[i];
        i++;
    }
    info[i] = '\0';
    return;
}


bool loadChessGame(SPChessGame **game, char *filePath) {
    SPChessGame *outputGame = chessGameCreate();
    char labelInfo[9];
    char line[SP_MAX_LINE_LENGTH];
    char tmp;
    bool success = false;
    FILE *gameFile = fopen(filePath, "r");
    if (!gameFile) {                                          // File Opening error
        chessGameDestroy(&outputGame);
        return false;
    }
    while (fgets(line, sizeof(line), gameFile) != NULL && !success) {
        if (strstr(line, CURRENT_TURN) != NULL) {            // Fill currentPlayer
            getLabelInfo(labelInfo, line);
            outputGame->currentPlayer = (!strcasecmp(labelInfo, "BLACK")) ? 0 : 1;
        } else if (strstr(line, MODE) != NULL) {             // Fill gameMode
            getLabelInfo(labelInfo, line);
            tmp = labelInfo[0];
            if (spParserIsInt(labelInfo)) {
                outputGame->gameMode = tmp - '0';
            }
        } else if (strstr(line, LEVEL) != NULL) {            // Fill difficulty
            if (outputGame->gameMode == 1) {
                getLabelInfo(labelInfo, line);
                tmp = labelInfo[0];
                if (spParserIsInt(labelInfo)) {
                    outputGame->difficulty = tmp - '0';
                }
            }
        } else if (strstr(line, COLOR) != NULL) {           // Fill userColor
            if (outputGame->gameMode == 1) {
                getLabelInfo(labelInfo, line);
                outputGame->userColor = (!strcasecmp(labelInfo, "WHITE")) ? 1 : 0;
            }
        } else if (strstr(line, BOARD) != NULL && (strchr(line, '/') == NULL)) {
            for (int j = GAMESIZE - 1; j >= 0; j--) {
                if (fgets(line, sizeof(line), gameFile)) {
                    for (int i = 0; i < GAMESIZE; i++) {
                        getLabelInfo(labelInfo, line);
                        outputGame->gameBoard[j][i] = labelInfo[i];
                    }
                }
            }
        } else if ((strstr(line, GAME) != NULL) && (strchr(line, '/') != NULL)) { success = true; }
    }
    if (success && fclose(gameFile) == 0) {              // no File closing error
        chessGameDestroy(game);
        *game = outputGame;
        return true;
    }
    chessGameDestroy(&outputGame);
    return false;
}




