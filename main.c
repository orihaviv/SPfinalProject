
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
    int status = settings(game);
    if (status == 0){ return 0; }
    if (game->gameMode == 1 && game->userColor == 0){
        executeComputerMove(game);
    }
    while (status > 0 && winner == -1) {
        chessGamePrintBoard(game);
        printf("%s player - enter your move\n", game->currentPlayer);
    }

    return 0;

}