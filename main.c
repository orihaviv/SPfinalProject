
#include "chessGame.h"
#include "chessParser.h"
#include "SPMainAux.h"

int main() {



    SPChessGame * game = chessGameCreate();
    if (!game){
        printf("Error: game was not created\n");
        return 0;
    }
    int winner = -1;
    SPCommand lastCommand;
    beginning:
    int status = settings(game);
    if (status == 0){ return 0; } // Quit command executed
    if (game->gameMode == 1 && game->userColor == 0){
        executeComputerMove(game);
    }
    while (status > 0 && winner == -1) {
        chessGamePrintBoard(game);
        printf("%s player - enter your move\n", game->currentPlayer);
        lastCommand = gameState(game);
        if (lastCommand.cmd == QUIT){ return 0; }
        if (lastCommand.cmd == RESET){
            goto beginning;
        }
        if (lastCommand.cmd == MOVE){

            executeComputerMove(game);
            //check winner
        }
    }
    return 0;

}