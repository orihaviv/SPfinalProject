//
// Created by אורי חביב on 10/06/2017.
//
#include "SPMainAux.h"

int initialize(SPFiarGame *fiarGame){
    char buffer[SP_MAX_LINE_LENGTH];
    int levelInput;
    while (true){
        printf("Please enter the difficulty level between [1-7]:\n");
        fgets(buffer,SP_MAX_LINE_LENGTH,stdin);
        if (spParserIsInt(buffer)) {
            levelInput = atoi(buffer);
            if ((levelInput >= 1) || (levelInput <= 7)) {
                fiarGame->level = levelInput;
                spFiarGamePrintBoard(fiarGame);
                break;
            }
        }
        if (!strcmp(buffer,"quit\n")){
            spFiarGameDestroy(fiarGame);
            return 0;
        }
        printf("Error: invalid level (should be between 1 to 7)\n");
    }
    return 2;
}

int execution (SPFiarGame* src, SPCommand command){
    if (src == NULL){
        return -1;
    }
    int move;
    SP_FIAR_GAME_MESSAGE message;
    switch (command.cmd){

        case SP_QUIT:
            spFiarGameDestroy(src);
            return 0;

        case SP_RESTART:
            spFiarGameDestroy(src);
            return 1;

        case SP_SUGGEST_MOVE:
            move = spMinimaxSuggestMove(src, src->level);
            printf("Suggested move: drop a disc to column %d\n", (move+1));
            return 3;

        case SP_UNDO_MOVE:
            if (src->undoHistory != (src->lastMoves->maxSize)){
                message = spFiarGameUndoPrevMove(src);
                if (message != SP_FIAR_GAME_NO_HISTORY){
                    spFiarGameUndoPrevMove(src);
                    spFiarGamePrintBoard(src);
                    src->undoHistory+=2;
                    return 2;
                }
            }
            printf("Error: cannot undo previous move!\n");
            return 2;

        case SP_ADD_DISC:
            message = spFiarGameSetMove(src, command.arg-1);
            if (message == SP_FIAR_GAME_INVALID_ARGUMENT){
                printf("Error: column number must be in range 1-7\n");
            }
            else if (message == SP_FIAR_GAME_INVALID_MOVE){
                printf("Error: column %d is full\n", command.arg);
            }
            else if (message == SP_FIAR_GAME_SUCCESS){
                if (spFiarCheckWinner(src) == '\0') {
                    move = spMinimaxSuggestMove(src, src->level);
                    message = spFiarGameSetMove(src, move);
                    printf("Computer move: add disc to column %d\n", (move + 1));
                }
                src->undoHistory = 0;
                spFiarGamePrintBoard(src);
            }
        default:
            return 2;
    }
}


int executionEnd (SPFiarGame* src, SPCommand command) {
    if (src == NULL) {
        return -1;
    }
    switch (command.cmd) {
        case SP_QUIT:
            spFiarGameDestroy(src);
            return 0;
        case SP_RESTART:
            spFiarGameDestroy(src);
            return 1;
        case SP_UNDO_MOVE:
            spFiarGameUndoPrevMove(src);
            spFiarGameUndoPrevMove(src);
            spFiarGamePrintBoard(src);
            src->undoHistory+=2;
            return 1;
        default:
            printf("Error: the game is over\n");
            return  2;
    }
}

void printWinner(char winner){
    if (winner == SP_FIAR_GAME_PLAYER_2_SYMBOL){
        printf("Game over: computer wins\nPlease enter 'quit' to exit or 'restart' to  start a new game!\n");
    }
    else if (winner == SP_FIAR_GAME_PLAYER_1_SYMBOL){
        printf("Game over: you win\nPlease enter 'quit' to exit or 'restart' to  start a new game!\n");
    }
    else if (winner == SP_FIAR_GAME_TIE_SYMBOL){
        printf("Game over: it's a tie\nPlease enter 'quit' to exit or 'restart' to  start a new game!\n");
    }
}
