

#include "SPMainAux.h"

int main() {

    SPChessGame * game = chessGameCreate();
    if (!game){
        printf("Error: game was not created\n");
        return 0;
    }
    SP_CHESS_GAME_STATE winner = SP_CHESS_GAME_NO_WINNER;
    SPCommand lastCommand;
    char* player;
    int status;
    beginning:
    status = settings(&game);
    if (status == 0){ return 0; }                       // Quit command executed
    if (game->gameMode == 1 && game->userColor == 0){
        executeComputerMove(game);
    }
    while (winner == SP_CHESS_GAME_NO_WINNER) {
        chessGamePrintBoard(game);
        player = game->currentPlayer == 0 ? "black" : "white";
        printf("%s player - enter your move\n", player);
        lastCommand = gameState(game);
        if (lastCommand.cmd == QUIT){ return 0; }       // Quit command executed
        if (lastCommand.cmd == RESET){
            game = chessGameCreate();
            goto beginning;
        }
        if (lastCommand.cmd == MOVE){
            winner = chessCheckWinner(game);
            if (game->gameMode == 1 && winner == SP_CHESS_GAME_NO_WINNER){
                executeComputerMove(game);
                winner = chessCheckWinner(game);
            }
        }
    }
    printWinnerMessage(winner, game);
    chessGameDestroy(&game);
    return 0;

}