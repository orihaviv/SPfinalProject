//
// Created by אורי חביב on 10/06/2017.
//
#include "SPMainAux.h"



void loadGame(SPChessGame **src, char *path) {
    bool isLoaded;
    isLoaded = loadChessGame(src, path);
    if (!isLoaded) {
        printf("Error: File does not exist or cannot be opened\n");
        return;
    }
}


void printSettings(SPChessGame *game) {
    printf("SETTINGS:\nGAME MODE: %d\n", game->gameMode);
    if (game->gameMode == 1) {
        char *color = game->userColor == 1 ? "WHITE" : "BLACK";
        printf("DIFFICULTY_LVL: %d\nUSER_CLR: %s\n", game->difficulty, color);
    }
}


int settings(SPChessGame **gamePointer) {
    SPChessGame *game = *gamePointer;
    if (!game) { return 0; }
    game->state = 0;
    char buffer[SP_MAX_LINE_LENGTH];
    SPCommand command;
    printf("Specify game setting or type 'start' to begin a game with the current setting:\n");
    while (true) {
        fgets(buffer, SP_MAX_LINE_LENGTH, stdin);
        if (!(*buffer)) { continue; }
        command = spParserParseLine(buffer);
        switch (command.cmd) {
            case GAME_MODE:
                game->gameMode = command.arg;
                if (command.arg == 1) { printf("Game mode is set to 1 player\n"); }
                else if (command.arg == 2) { printf("Game mode is set to 2 players\n"); }
                break;
            case DIFFICULTY:
                if (game->gameMode == 2) {
                    printf("Invalid command\n");
                } else {
                    game->difficulty = command.arg;
                    printf("Game difficulty is set to %d\n", command.arg); // TODO print something?
                }
                break;
            case USER_COLOR:
                if (game->gameMode == 2) {
                    printf("Invalid command\n");
                } else {
                    game->userColor = command.arg;
                    char *player = command.arg == 0 ? "black" : "white";
                    printf("User color is set to %s\n", player);   // TODO print something?
                }
                break;
            case LOAD:
                loadGame(gamePointer, command.path);
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
                chessGameDestroy(&game);
                return 0;
            case START:
                game->state = 1;
                return 1;
            case IGNORE:
                break;
            default:
                printf("Invalid command\n");
                break;
        }
    }
}


char* translateToSoldiersName(char soldier) {
    char *name;
    switch (soldier) {
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
        default:
            return NULL;
    }
    return name;
}


void executeComputerMove(SPChessGame *src) {
    action nextMove = *(spMinimaxSuggestMove(src, src->difficulty, 0));
    char soldier = nextMove.piece;
    while (chessGameSetMove(src, nextMove.prev, nextMove.current, 0, 0) != SP_CHESS_GAME_SUCCESS) { continue; }
    char *name = translateToSoldiersName(soldier);
    if (name == NULL){
        printf("problem in translateToSoldierName");
        return;
    }
    if (nextMove.castling == SP_CHESS_NO_CASTLING) {
        printf("Computer: move %s at <%d,%c> to <%d,%c>\n", name, toRowNum(nextMove.prev.row),
               toColChar(nextMove.prev.column), toRowNum(nextMove.current.row), toColChar(nextMove.current.column));
    }
    else {
        if (nextMove.piece == ROOKWHITE || nextMove.piece == ROOKBLACK){
            printf("Computer: castle King at <%d,%c> and Rook at <%d,%c>\n" , toRowNum(nextMove.current.row),
                   toColChar(nextMove.current.column), toRowNum(nextMove.prev.row), toColChar(nextMove.prev.column));
        }
        else{
            printf("Computer: castle King at <%d,%c> and Rook at <%d,%c>\n" , toRowNum(nextMove.prev.row),
                   toColChar(nextMove.prev.column), toRowNum(nextMove.current.row), toColChar(nextMove.current.column));
        }
    }
}


int executePlayerMove(SPChessGame *src, SPCommand command) {
    SP_CHESS_GAME_MESSAGE msg = chessGameSetMove(src, command.source, command.destination, 0, 0);
    if (msg == SP_CHESS_GAME_INVALID_POSITION_ON_BOARD) {
        printf("Invalid position on the board\n");
    } else if (msg == SP_CHESS_GAME_SOLDIER_MISMATCH) {
        printf("The specified position does not contain your piece\n");
    } else if (msg == SP_CHESS_GAME_ILLEGAL_MOVE) {
        printf("Illegal move\n");
    }
    else{
        return 1;
    }
    return 0;
}



void executeGetMoves(SPChessGame *game, SPCommand command) {
    SPArrayList *possibleActions;
    action move;
    if (game->gameMode == 2 || game->difficulty > 2) {
        printf("Get move command is not supported\n");
    } else if (!posOnBoard(command.source)) {
        printf("Invalid position on the board\n");
    } else if (game->currentPlayer == 1 && !isWhite(game->gameBoard[command.source.row][command.source.column])) {
        printf("The specified position does not contain white player piece\n");
    } else if (game->currentPlayer == 0 && !isBlack(game->gameBoard[command.source.row][command.source.column])) {
        printf("The specified position does not contain black player piece\n");
    } else {
        possibleActions = getMovesForSoldier(game, command.source.row, command.source.column);
        qsort((void*)possibleActions, possibleActions->actualSize, sizeof(action), actionCompare);
        for (int index = 0; index < possibleActions->actualSize; index++) {
            move = *(spArrayListGetAt(possibleActions, index));
            if (move.castling == SP_CHESS_NO_CASTLING){
                printf("<%d,%c>", toRowNum(move.current.row), toColChar(move.current.column));
            }
            else{
                printf("castle <%d,%c>", toRowNum(move.prev.row), toColChar(move.prev.column));
            }
            if (game->difficulty <= 2) {
                if (isTheSoldierThreatened(game, game->currentPlayer, move.current)) { printf("*"); }
                if (move.captured != BLANK) { printf("^"); }
                printf("\n");
            }
        }
        spArrayListDestroy(&possibleActions);
    }
    return;
}

void executeUndo(SPChessGame *game) {
    if (game->gameMode == 2) {
        printf("Undo command not available in two players mode\n");
        return;
    }
    action* lastMovePointer;
    action lastMove;
    lastMovePointer = spArrayListGetFirst(game->lastMoves);
    if (lastMovePointer == NULL){
        printf("Empty history, move cannot be undone\n");
        return;
    }
    lastMove = *lastMovePointer;
    SP_CHESS_GAME_MESSAGE msg = chessGameUndoPrevMove(game);
    if (msg == SP_CHESS_GAME_NO_HISTORY) {
        printf("Empty history, move cannot be undone\n");
        return;
    }
    char *player;
    if (msg == SP_CHESS_GAME_SUCCESS) {
        player = game->currentPlayer == 1 ? "white" : "black";
        printf("Undo move for player %s : <%d,%c> ->  <%d,%c>\n", player, toRowNum(lastMove.current.row),
               toColChar(lastMove.current.column), toRowNum(lastMove.prev.row), toColChar(lastMove.prev.column));
        lastMove = *(spArrayListGetFirst(game->lastMoves));
        SP_CHESS_GAME_MESSAGE msg = chessGameUndoPrevMove(game);
        if (msg == SP_CHESS_GAME_SUCCESS) {
            player = game->currentPlayer == 1 ? "white" : "black";
            printf("Undo move for player %s : <%d,%c> ->  <%d,%c>\n", player, toRowNum(lastMove.current.row),
                   toColChar(lastMove.current.column), toRowNum(lastMove.prev.row), toColChar(lastMove.prev.column));
        }
    }
}


void executeSave(SPChessGame* game, SPCommand command){
    int saved = saveGame(command.path, game);
    if (saved == 0){
        printf("File cannot be created or modified\n");
    }
}


SPCommand gameState(SPChessGame *game) {
    char buffer[SP_MAX_LINE_LENGTH];
    SPCommand command;
    command.cmd = INVALID;
    while (command.cmd == INVALID) {
        fgets(buffer, SP_MAX_LINE_LENGTH, stdin);
        if (!(*buffer)) { continue; }
        command = spParserParseLine(buffer);
        switch (command.cmd) {
            case MOVE:
                if (executePlayerMove(game, command) == 0){
                    command.cmd = IGNORE;
                }
                break;
            case GET_MOVES:
                executeGetMoves(game, command);
                break;
            case SAVE:
                executeSave(game, command);
                break;
            case UNDO:
                executeUndo(game);
                break;
            case RESET:
                printf("Restarting...\n");
                chessGameDestroy(&game);
                break;
            case QUIT:
                printf("Exiting...\n");
                chessGameDestroy(&game);
                break;
            case CASTLE:
                if (executeCastling(game, command, 0, 0) == 0){
                    command.cmd = INVALID;
                }
                break;
            default:
                printf("Invalid command\n");
                break;
        }
    }
    return command;
}


void printWinnerMessage(SP_CHESS_GAME_STATE msg, SPChessGame *game){
    switch(msg){
        case SP_CHESS_GAME_TIE:
            if (game->gameMode == 2 || game->currentPlayer != game->userColor) {
                printf("The game is tied\n\n");
            }
            else {
                printf("The game ends in a tie\n");
            }
            break;
        case SP_CHESS_GAME_WHITE_WINNER:
            printf("Checkmate! white player wins the game\n");
            break;
        case SP_CHESS_GAME_BLACK_WINNER:
            printf("Checkmate! black player wins the game\n");
            break;
        default:
            break;
    }
    return;
}
