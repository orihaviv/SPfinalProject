//
// Created by ׳�׳•׳¨׳™ ׳—׳‘׳™׳‘ on 31/05/2017.
//

#include "chessParser.h"

bool spParserIsInt(const char* str){
    if ((!str) || ((str[0] != '-') && ((str[0] > '9') || (str[0] < '0')))){
        return false;
    }
    for (int i = 1; str[i] != '\0'; i++){
        if (str[i] == '\n'){ continue;}
        if (str[i] > '9' || str[i] < '0'){
            return false;
        }
    }
    return true;
}

SPCommand setGameModeCmd (char* mode) {
    SPCommand command;
    command.cmd = GAME_MODE;
    if (!strcmp(mode, "1")) {
        command.arg = 1;
    } else if (!strcmp(mode, "2")) {
        command.arg = 2;
    } else if (mode == NULL){
        command.arg = 1;
    } else {
        command.cmd = INVALID;
        printf("Wrong game mode\n");
    }
    return command;
}



SPCommand setDifficultyCmd(char* diff) {
    SPCommand command;
    command.cmd = INVALID;
    if(diff == NULL){
        command.cmd = DIFFICULTY;
        command.arg = 2;
    }
    int level;
    if (spParserIsInt(diff)){
        level = atoi(diff);
        if (level > 0 && level < 5){
            command.cmd = DIFFICULTY;
            command.arg = level;
        }
        else if (level == 5){
            printf("Expert level not supported, please choose a value between 1 to 4:\n");
        }
        else{
            printf("Wrong difficulty level. The value should be between 1 to 5\n");
        }
    }
    return command;
}


SPCommand setColorCmd(char* color){
    SPCommand command;
    command.cmd = USER_COLOR;
    if (color == NULL){
        command.arg = 1;
    } else if (!strcmp(color, "0")) {
        command.arg = 0;
    } else if (!strcmp(color, "1")) {
        command.arg = 1;
    } else {
        command.cmd = INVALID;
        printf("Invalid color\n");
    }
    return command;
}

SPCommand setCastleCmd(char* origin){
    SPCommand command;
    command.cmd = CASTLE;
    if (origin == NULL){
        command.cmd = INVALID;
//     } else if (!strcmp(color, "0")) {
//         command.arg = 0;
//     } else if (!strcmp(color, "1")) {
//         command.arg = 1;
//     } else {
//         command.cmd = INVALID;
//         printf("Invalid color\n");
//     }
//     return command;
}

SPCommand setMoveCmd(char* source, char* dest){
    SPCommand command;
    command.cmd = INVALID;
    if (source && dest &&  source[0] == '<' && source[2] == ',' && source[4] == '>' && dest[0] == '<' && dest[2] == ',' && dest[4] == '>'){
        if (source[1] > '0' && source[1] < '9' && dest[1] > '0' && dest[1] < '9'
            && source[3] >= 'A' && source[3] <= 'H' && dest[3] >= 'A' && dest[3] <= 'H'){
            command.source.column = colToInt(source[3]);
            command.source.row = rowToInt(source[1]);
            command.destination.column = colToInt(dest[3]);
            command.destination.row = rowToInt(dest[1]);
            command.cmd = MOVE;
        }
    }
    return command;
}

SPCommand getMoveCmd(char* source){
    SPCommand command;
    command.cmd = INVALID;
    if (!source){ return command;}
    if (source[0] == '<' && source[2] == ',' && source[4] == '>' && source[1] > '0' && source[1] < '9' && source[3] >= 'A' && source[3] <= 'H'){
        command.cmd = GET_MOVES;
        command.source.column = colToInt(source[3]);
        command.source.row = rowToInt(source[3]);
    }
    return command;
}

char getPiece(char* source){
    if (!source){ return '_'; }
	char *strCopy = (char *) malloc(SP_MAX_LINE_LENGTH);
	strcpy(strCopy, source);
    char *firstToken = strtok(strCopy, " \t\r\n");
    char *nextToken = strtok(NULL, " \t\r\n");
    if (nextToken != NULL){
    	printf("Invalid Type\n");
    	return '_';
    }
    if(!strcmp(firstToken, "queen")){
    	return 'q';
    }
    if(!strcmp(firstToken, "rook")){
    	return 'r';
    }
    if(!strcmp(firstToken, "knight")){
    	return 'n';
    }
    if(!strcmp(firstToken, "bishop")){
    	return 'b';
    }
    if(!strcmp(firstToken, "pawn")){
        return 'p';
    }
    printf("Invalid Type\n");
    return '_';
}


SPCommand spParserParseLine(const char* str) {
    SPCommand command;
    command.cmd = INVALID;
    if (!str){
        return command;
    }
    char *strCopy = (char *) malloc(SP_MAX_LINE_LENGTH);
    if (strCopy != NULL) {
        strcpy(strCopy, str);
        char *firstToken = strtok(strCopy, " \t\r\n");
        if (firstToken == NULL){ return command; }
        char *nextToken = strtok(NULL, " \t\r\n");
        if (!strcmp(firstToken, "game_mode")) {
            return setGameModeCmd(nextToken);
        } else if (!strcmp(firstToken, "difficulty")) {
            return setDifficultyCmd(nextToken);
        } else if (!strcmp(firstToken, "user_color")) {
            return setColorCmd(nextToken);
        } else if (!strcmp(firstToken, "move")){
            char *thirdToken = strtok(NULL, " \t\r\n");
            char *forthToken = strtok(NULL, " \t\r\n");
            if (!strcmp(thirdToken, "to")){
                return setMoveCmd (nextToken, forthToken);
            }
        } else if (!strcmp(firstToken, "castle")){
            return setCastleCmd(nextToken);
        } else if (!strcmp(firstToken, "get_moves")){
            return getMoveCmd(nextToken);
        } else if (!strcmp(firstToken, "load")) {
            strcpy(command.path, nextToken);
            command.cmd = LOAD;
        } else if (!strcmp(firstToken, "save")){
            strcpy(command.path, nextToken);
            command.cmd = SAVE;
        } else if (nextToken != NULL) {}
        else if (!strcmp(firstToken, "default")) {
            command.cmd = DEFAULT_GAME;
        } else if (!strcmp(firstToken, "print_setting")) {
            command.cmd = PRINT_SETTING;
        } else if (!strcmp(firstToken, "quit")) {
            command.cmd = QUIT;
        } else if (!strcmp(firstToken, "start")) {
            command.cmd = START;
        } else if (!strcmp(firstToken, "undo")){
            command.cmd = UNDO;
        } else if (!strcmp(firstToken, "reset")) {
            command.cmd = RESET;
        }
        free(strCopy);
    }
    return command;
}
