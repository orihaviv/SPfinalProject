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

SPCommand setMoveCmd(char* source, char* dest){
    SPCommand command;
    command.cmd = INVALID;
    char row[SP_MAX_LINE_LENGTH];
    if (source && dest){
    	while(source[i] != ',') { i++; }
    	strncpy(row, source+1, i-2);
        command.source.column = colToInt(source[i+1]);
        command.source.row = rowToInt(atoi(row));
        
    	while(dest[j] != ',') { j++; }
    	strncpy(row, dest+1, j-2);
        command.destination.column = colToInt(dest[j+1]);
        command.destination.row = rowToInt(atoi(row));
        command.cmd = MOVE;
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

bool isValidFormat(char* token){
	if(token == NULL || token[0] != '<' || !token[1].isdigit()){
		return false;
	}
	int i = 2;
	while (token[i] >= '0' && token[i] <= '9'){
		i++;
	}
	if(token[i++] != ','){
		return false;
	}
	if(token[i] >= 'A' && token[i] <= 'Z'){
		return false;
	}
	i++;
	if(token[i] != '>' || token[i+1] != '\0'){
		return false;
	}
	return true;
}


SPCommand spParserParseLine(const char* str) {
    char *strCopy = (char *) malloc(SP_MAX_LINE_LENGTH);
    SPCommand command;
    command.cmd = INVALID;
    if (strCopy != NULL) {
        strcpy(strCopy, str);
        char *firstToken = strtok(strCopy, " \t\r\n");
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
            	if (isValidFormat(nextToken) && isValidFormat(forthFormat)){
            		return setMoveCmd (nextToken, forthToken);
            	}
            }
        } else if (!strcmp(firstToken, "get_moves")){
            return getMoveCmd(nextToken);
        } else if (!strcmp(firstToken, "load")) {
            strcpy(command.path, nextToken);
            command.cmd = LOAD;
        } else if (!strcmp(firstToken, "save")){
            strcpy(command.path, nextToken);
            command.cmd = SAVE;
        } else if (nextToken != NULL) {
            printf("Invalid command\n");
        } else if (!strcmp(firstToken, "default")) {
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
        else{
            printf("Invalid command\n");
        }
        free(strCopy);
    }
    return command;
}
