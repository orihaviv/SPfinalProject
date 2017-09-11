//
// Created by אורי חביב on 10/06/2017.
//
#include "SPMainAux.h"
#include "chessParser.h"



void loadGame (SPChessGame* src, char* path){
    chessGameDestroy(src);
    //TODO
    if (src->state == 0){ // if the loaded game is on settings mode
        settings(src);
    }
    return;
}

void printSettings(SPChessGame* game){
//TODO
};




int settings(SPChessGame *game) {
    game->state = 0;
    char buffer[SP_MAX_LINE_LENGTH];
    SPCommand command;
    printf("Specify game setting or type 'start' to begin a game with the current setting:\n");
    while (true) {
        fgets(buffer, SP_MAX_LINE_LENGTH, stdin);
        if(!buffer){ continue;}
        command = spParserParseLine(buffer);
        switch (command.cmd) {
            case GAME_MODE:
                game->gameMode = command.arg;
                if (command.arg == 1) { printf("Game mode is set to 1 player\n"); }
                else if (command.arg == 2) { printf("Game mode is set to 2 players\n"); }
                break;
            case DIFFICULTY:
                if (game->gameMode == 2){
                    printf("Invalid command\n");
                    break;
                }
                else {
                    game->difficulty = command.arg;
                    printf("Game difficulty is set to %d\n", command.arg); // TODO print something?
                    break;
                }
            case USER_COLOR:
                if (game->gameMode == 2){
                    printf("Invalid command\n");
                    break;
                }
                else {
                    game->userColor = command.arg;
                    char *player = command.arg == 1 ? "black" : "white";
                    printf("User color is set to %s\n", player);   // TODO print something?
                    break;
                }
            case LOAD:
                loadGame(game, command.path);
                break;
            case DEFAULT_GAME:
                game->gameMode = 1;
                game->difficulty = 2;
                game->userColor = 1;
                break;
            case PRINT_SETTING:
                printSettings(game);
                break;
            case QUIT:
                printf("Exiting...\n");
                chessGameDestroy(game);
                return 0;
            case START:
                game->state = 1;
                return 1;
        }
    }
}



char* translateToSoldiersName(char soldier){
    char* name = (char*) malloc(10);
    switch (soldier){
        case 'm':
        case 'M':
            name = "pawn";
            break;
        case 'b':
        case 'B':
            name = "bishop";
            break;
        case 'r':
        case 'R':
            name = "rook";
            break;
        case 'n':
        case 'N':
            name = "knight";
            break;
        case 'k':
        case 'K':
            name = "king";
            break;
        case 'q':
        case 'Q':
            name = "queen";
            break;
    }
    return name;
}


//int gameState (SPChessGame *game){
//    char buffer[SP_MAX_LINE_LENGTH];
//    SPCommand command;
//    command.cmd = INVALID;
//    SP_CHESS_GAME_MESSAGE message;
//    while (command.cmd == INVALID) {
//        fgets(buffer, SP_MAX_LINE_LENGTH, stdin);
//        if (!buffer) { continue; }
//        flag = false;
//        command = spParserParseLine(buffer);
//        switch (command.cmd) {
//}s







void executeComputerMove(SPChessGame* src){
    action nextMove = *(spMinimaxSuggestMove(game, game->difficulty));
    char soldier  = src->gameBoard[nextMove.prev.row][nextMove.prev.column];
    while(chessGameSetMove(game, nextMove.prev, nextMove.current) != SP_CHESS_GAME_SUCCESS){ continue;}
    char* name = translateToSoldiersName(soldier);
    printf("Computer: move %s at <%d,%c> to <%d,%c>\n", name, toRowNum(nextMove.prev.row),
           toColChar(nextMove.prev.column), toRowNum(nextMove.current.row), toColChar(nextMove.current.column));
    free(name);
}


int executePlayerMove (SPChessGame* src){
    int status;
    chessGamePrintBoard(src);
    char* color = src->currentPlayer == 1 ? "white" : "black";
    printf("%s player - enter your move\n", color);
    status = gameState(src);
}













int execution(SPFiarGame *src, SPCommand command) {
    if (src == NULL) {
        return -1;
    }
    int move;
    SP_FIAR_GAME_MESSAGE message;
    switch (command.cmd) {

        case SP_QUIT:
            spFiarGameDestroy(src);
            return 0;

        case SP_RESTART:
            spFiarGameDestroy(src);
            return 1;

        case SP_SUGGEST_MOVE:
            move = spMinimaxSuggestMove(src, src->level);
            printf("Suggested move: drop a disc to column %d\n", (move + 1));
            return 3;

        case SP_UNDO_MOVE:
            if (src->undoHistory != (src->lastMoves->maxSize)) {
                message = spFiarGameUndoPrevMove(src);
                if (message != SP_FIAR_GAME_NO_HISTORY) {
                    spFiarGameUndoPrevMove(src);
                    spFiarGamePrintBoard(src);
                    src->undoHistory += 2;
                    return 2;
                }
            }
            printf("Error: cannot undo previous move!\n");
            return 2;

        case SP_ADD_DISC:
            message = spFiarGameSetMove(src, command.arg - 1);
            if (message == SP_FIAR_GAME_INVALID_ARGUMENT) {
                printf("Error: column number must be in range 1-7\n");
            } else if (message == SP_FIAR_GAME_INVALID_MOVE) {
                printf("Error: column %d is full\n", command.arg);
            } else if (message == SP_FIAR_GAME_SUCCESS) {
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


int executionEnd(SPFiarGame *src, SPCommand command) {
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
            src->undoHistory += 2;
            return 1;
        default:
            printf("Error: the game is over\n");
            return 2;
    }
}

void printWinner(char winner) {
    if (winner == SP_FIAR_GAME_PLAYER_2_SYMBOL) {
        printf("Game over: computer wins\nPlease enter 'quit' to exit or 'restart' to  start a new game!\n");
    } else if (winner == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
        printf("Game over: you win\nPlease enter 'quit' to exit or 'restart' to  start a new game!\n");
    } else if (winner == SP_FIAR_GAME_TIE_SYMBOL) {
        printf("Game over: it's a tie\nPlease enter 'quit' to exit or 'restart' to  start a new game!\n");
    }
}
