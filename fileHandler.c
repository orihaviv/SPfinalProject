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

    startLabel(GENERAL, 1, gameFile);
    startAndEndLabel("whiteLeftCastling", NULL, game->whiteLeftCastling, 2, gameFile);
    startAndEndLabel("whiteRightCastling", NULL, game->whiteRightCastling, 2, gameFile);
    startAndEndLabel("blackLeftCastling", NULL, game->blackLeftCastling, 2, gameFile);
    startAndEndLabel("blackRightCastling", NULL, game->blackRightCastling, 2, gameFile);
    startAndEndLabel("whiteKingRow", NULL, game->whiteKing.row, 2, gameFile);
    startAndEndLabel("whiteKingCol", NULL, game->whiteKing.column, 2, gameFile);
    startAndEndLabel("blackKingRow", NULL, game->blackKing.row, 2, gameFile);
    startAndEndLabel("blackKingCol", NULL, game->blackKing.column, 2, gameFile);
    endLabel(GENERAL, 1, gameFile);

    endLabel(GAME, 0, gameFile);

    if (fclose(gameFile) != 0) {     // fclose has failed
        return 0;
    }

    return 1;
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
            outputGame->currentPlayer = (!strcmp(labelInfo, "BLACK")) ? 0 : 1;
        } else if (strstr(line, MODE) != NULL) {             // Fill gameMode
            getLabelInfo(labelInfo, line);
            tmp = labelInfo[0];
            if (spParserIsInt(labelInfo)) { outputGame->gameMode = tmp - '0'; }
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
                outputGame->userColor = (!strcmp(labelInfo, "WHITE")) ? 1 : 0;
            }
        } else if (strstr(line, BOARD) != NULL && (strchr(line, '/') == NULL)) { // Fill board
            for (int j = GAMESIZE - 1; j >= 0; j--) {
                if (fgets(line, sizeof(line), gameFile)) {
                    for (int i = 0; i < GAMESIZE; i++) {
                        getLabelInfo(labelInfo, line);
                        outputGame->gameBoard[j][i] = labelInfo[i];
                    }
                }
            }
        } else if (strstr(line, "whiteLeftCastling") != NULL) {           // Fill whiteLeftCastling
            getLabelInfo(labelInfo, line);
            tmp = labelInfo[0];
            if (spParserIsInt(labelInfo)) { outputGame->whiteLeftCastling = tmp - '0'; }
        } else if (strstr(line, "whiteRightCastling") != NULL) {           // Fill whiteRightCastling
            getLabelInfo(labelInfo, line);
            tmp = labelInfo[0];
            if (spParserIsInt(labelInfo)) { outputGame->whiteRightCastling = tmp - '0'; }
        } else if (strstr(line, "blackLeftCastling") != NULL) {           // Fill blackLeftCastling
            getLabelInfo(labelInfo, line);
            tmp = labelInfo[0];
            if (spParserIsInt(labelInfo)) { outputGame->blackLeftCastling = tmp - '0'; }
        } else if (strstr(line, "blackRightCastling") != NULL) {           // Fill blackRightCastling
            getLabelInfo(labelInfo, line);
            tmp = labelInfo[0];
            if (spParserIsInt(labelInfo)) { outputGame->blackRightCastling = tmp - '0'; }
        } else if (strstr(line, "whiteKingRow") != NULL) {
            getLabelInfo(labelInfo, line);
            tmp = labelInfo[0];
            if (spParserIsInt(labelInfo)) { outputGame->whiteKing.row = tmp - '0'; }
        } else if (strstr(line, "whiteKingCol") != NULL) {
            getLabelInfo(labelInfo, line);
            tmp = labelInfo[0];
            if (spParserIsInt(labelInfo)) { outputGame->whiteKing.column = tmp - '0'; }
        } else if (strstr(line, "blackKingRow") != NULL) {
            getLabelInfo(labelInfo, line);
            tmp = labelInfo[0];
            if (spParserIsInt(labelInfo)) { outputGame->blackKing.row = tmp - '0'; }
        } else if (strstr(line, "blackKingCol") != NULL) {
            getLabelInfo(labelInfo, line);
            tmp = labelInfo[0];
            if (spParserIsInt(labelInfo)) { outputGame->blackKing.column = tmp - '0'; }
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




/********************* GUI *********************/





bool savedGameExists(){

    if (access("GUI/saved/savedGames.xml", F_OK) != -1){
        return true;
    }
    return false;
}


bool createSavedGames(char* first, char* second, char* third, char* forth, char* fifth){
    int num = 5;
    if (!fifth || strlen(fifth) == 0){
        fifth = "";
        num--;
        if (!forth || strlen(forth) == 0){
            forth = "";
            num--;
            if(!third || strlen(third) == 0){
                third = "";
                num--;
                if (!second || strlen(second) == 0){
                    second = "";
                    num--;
                    if (!first || strlen(first) == 0){
                        first = "";
                        num--;
                    }
                }
            }
        }
    }
    FILE *gameFile;
    gameFile = fopen("GUI/saved/savedGames.xml", "w");
    if (gameFile == NULL) {         // fopen has failed
        return false;
    }
    fprintf(gameFile, XML_HEADLINE);
    startLabel(ALL_GAMES, 0, gameFile);

    startAndEndLabel(NUM_OF_SAVED, NULL, num, 1, gameFile);
    startLabel(SAVED_LIST, 1, gameFile);
    startAndEndLabel(SLOT_ONE, first, -1, 1, gameFile);
    startAndEndLabel(SLOT_TWO, second, -1, 1, gameFile);
    startAndEndLabel(SLOT_THREE, third, -1, 1, gameFile);
    startAndEndLabel(SLOT_FOUR, forth, -1, 1, gameFile);
    startAndEndLabel(SLOT_FIVE, fifth, -1, 1, gameFile);
    endLabel(SAVED_LIST, 1, gameFile);

    endLabel(ALL_GAMES, 0, gameFile);

    if (fclose(gameFile) != 0) {     // fclose has failed
        return false;
    }

    return true;
}


int extractNumOfSavedGames(){
    char tmp;
    char labelInfo[SP_MAX_LINE_LENGTH];
    char line[SP_MAX_LINE_LENGTH];

    FILE *gameFile = fopen("GUI/saved/savedGames.xml", "r");
    if (!gameFile) {                                          // File Opening error
        return -1;
    }
    while (fgets(line, sizeof(line), gameFile) != NULL) {
        if (strstr(line, NUM_OF_SAVED) != NULL) {
            getLabelInfo(labelInfo, line);
            tmp = labelInfo[0];
            if (spParserIsInt(labelInfo)) { return (tmp - '0'); }
            else {return -1;}
        }
    }

    if (fclose(gameFile) != 0) {     // fclose has failed
        return -1;
    }
    return -1;
}


char* extractPathOfSlot(int slotNum){
    if (extractNumOfSavedGames() < slotNum || slotNum < 1 ){ return NULL; }
    char* path = (char *) malloc(SP_MAX_LINE_LENGTH);
    char line[SP_MAX_LINE_LENGTH];
    char* requiredSlot;

    FILE *gameFile = fopen("GUI/saved/savedGames.xml", "r");
    if (!gameFile) {                                          // File Opening error
        return NULL;
    }
    switch(slotNum){
        case 1:
            requiredSlot = SLOT_ONE;
            break;
        case 2:
            requiredSlot = SLOT_TWO;
            break;
        case 3:
            requiredSlot = SLOT_THREE;
            break;
        case 4:
            requiredSlot = SLOT_FOUR;
            break;
        case 5:
            requiredSlot = SLOT_FIVE;
            break;
        default:
            return NULL;
    }
    while (fgets(line, sizeof(line), gameFile) != NULL) {
        if (strstr(line, requiredSlot) != NULL) {
            getLabelInfo(path, line);
            if (strlen(path) <= 0){ return NULL;}
            else { return path; }
        }
    }
}


bool guiLoadChessGame(SPChessGame **game, int slot) {
    if (*game == NULL || slot < 1 || slot > 5) {return false; }
    char* path = extractPathOfSlot(slot);
    return loadChessGame(game, path);
}

int guiSaveGame(SPChessGame *game){
    bool success;
    int gameSaved;
    int numOfGames;
    if (!savedGameExists()){
        gameSaved = saveGame("GUI/saved/game1", game);
        success = createSavedGames("GUI/saved/game1", NULL, NULL, NULL, NULL);
        if (success && gameSaved) { return 1; }
        return 0;
    }

    numOfGames = extractNumOfSavedGames();
    char* one = NULL;
    char* two = extractPathOfSlot(1);
    char* three = extractPathOfSlot(2);
    char* four = extractPathOfSlot(3);
    char* five = extractPathOfSlot(4);

    switch(numOfGames){
        case 1:
            one = "GUI/saved/game2";
            break;
        case 2:
            one = "GUI/saved/game3";
            break;
        case 3:
            one = "GUI/saved/game4";
            break;
        case 4:
            one = "GUI/saved/game5";
            break;
        case 5:
            one = extractPathOfSlot(5);
            break;
        default:
            return 0;

    }
    gameSaved = saveGame(one, game);
    success = createSavedGames(one, two, three, four, five);
    if (success && gameSaved) { return 1; }
    return 0;
}




