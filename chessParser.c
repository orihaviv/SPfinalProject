//
// Created by אורי חביב on 31/05/2017.
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

SPCommand setGameMode (char* mode) {
    SPCommand command;
    command.cmd = GAME_MODE;
    if (!strcmp(mode, "1")) {
        command.args = 1;
//        printf("Game mode is set to 1 players\n"); TODO
    } else if (!strcmp(nextToken, "2")) {
        command.args = 2;
//        printf("Game mode is set to 2 players\n"); TODO
    } else {
        command.cmd = INVALID;
        printf("Wrong game mode\n");
    }
    return command;
}



SPCommand setDifficulty(char* diff) {
    SPCommand command;
    command.cmd = INVALID;
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

SPCommand setColor(char* color){
    SPCommand command;

    if (!strcmp(color, "0")) {
        command.arg = 0;
    } else if (!strcmp(nextToken, "1")) {
        command.arg = 1;
    } else {
        command.cmd = INVALID;
        printf("Invalid color\n");
    }
    return command;
}


SPCommand spParserParseLine(const char* str) {
    char *strCopy = (char *) malloc(SP_MAX_LINE_LENGTH);
    SPCommand command;
    if (strCopy != NULL) {
        strcpy(strCopy, str);
        char *firstToken = strtok(strCopy, " \t\r\n");
        if (!strcmp(firstToken, "game_mode")) {
            char *nextToken = strtok(NULL, " \t\r\n");
            return setGameMode(nextToken);
        } else if (!strcmp(firstToken, "difficulty")) {
            char *nextToken = strtok(NULL, " \t\r\n");
            return setDifficulty(nextToken);
        } else if (!strcmp(firstToken, "user_color")) {
            char *nextToken = strtok(NULL, " \t\r\n");
            return setColor(nextToken);
        } else if (!strcmp(firstToken, "load")) {
            command.path = strtok(NULL, " \t\r\n");
            command.cmd = LOAD;
        } else if (!strcmp(firstToken, "default")) {
            command.cmd = DEFAULT_GAME;
        } else if (!strcmp(firstToken, "print_setting")) {
            command.cmd = PRINT_SETTING;
        } else if (!strcmp(firstToken, "quit")) {
            command.cmd = QUIT;
        } else if (!strcmp(firstToken, "quit")) {
            command.cmd = QUIT;
        } else if ((!strcmp(firstToken, "quit")){

        }
        free(strCopy);
        return command;
    }
}






            if (!strcmp(firstToken, "add_disc")) {
            command.cmd = SP_ADD_DISC;
            char *nextToken = strtok(NULL, " \t\r\n");
            if (spParserIsInt(nextToken)) {
                command.validArg = true;
                command.arg = atoi(nextToken);
            } else {
                printf("Error: invalid command\n");
                command.cmd = SP_INVALID_LINE;
            }
        } else {
            if (!strcmp(firstToken, "quit")) {
                command.cmd = SP_QUIT;
            } else if (!strcmp(firstToken, "restart")) {
                command.cmd = SP_RESTART;
            } else if (!strcmp(firstToken, "undo_move")) {
                command.cmd = SP_UNDO_MOVE;
            } else if (!strcmp(firstToken, "suggest_move")) {
                command.cmd = SP_SUGGEST_MOVE;
            } else {
                flag = 1;
                printf("Error: invalid command\n");
                command.cmd = SP_INVALID_LINE;
            }
        }
        if (strtok(NULL, " \t\r\n") != NULL && flag == 0) {
            printf("Error: invalid command\n");
            command.cmd = SP_INVALID_LINE;
        }
        free(strCopy);
    }
    else{
        printf("Error: malloc has failed");
        command.cmd = SP_QUIT;
    }
    return command;
}