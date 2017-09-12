
#include "chessGame.h"
#include "chessParser.h"
#include "SPMainAux.h"

int main() {
//    SPChessGame * game = chessGameCreate();
//    int winner = -1;
//    int status = settings(game);
//    if (status == 0){ return 0; }
//    if (game->gameMode == 1 && game->userColor == 0){
//        executeComputerMove(game);
//    }
//    while (status > 0 && winner == -1) {







//    }
//    return 0;









        SPChessGame *game = chessGameCreate();

        if (chessGameUndoPrevMove(game) != SP_CHESS_GAME_NO_HISTORY) { printf(" Error 1\n"); }

        if (whosThere(game, 3, 2) != BLANK) { printf(" Error 2\n"); }
        if (whosThere(game, 0, 0) != ROOKWHITE) { printf(" Error 3\n"); }
        if (whosThere(game, 0, 3) != QUEENWHITE) { printf(" Error 4\n"); }
        if (whosThere(game, 8, 2) != '\0') { printf(" Error 5\n"); }
        if (whosThere(game, 6, 2) != PAWNBLACK) { printf(" Error 6\n"); }
        if (whosThere(game, 7, 1) != KNIGHTBLACK) { printf(" Error 7\n"); }
        if (whosThere(game, 7, 4) != KINGBLACK) { printf(" Error 8\n"); }

        chessGamePrintBoard(game);


        position a;
        a.row = 0;
        a.column = 0;

        position b;
        b.row = 11;
        b.column = 0;

        position c;
        c.row = 0;
        c.column = 12;

        position d;
        d.row = 1;
        d.column = 1;

        position f;
        f.row = 3;
        f.column = 1;

        position g;
        g.row = 7;
        g.column = 6;

        position h;
        h.row = 5;
        h.column = 7;

        position k;
        k.row = 7;
        k.column = 4;

        position l;
        l.row = 7;
        l.column = 3;

        position m;
        m.row = 6;
        m.column = 6;

        position n;
        n.row = 5;
        n.column = 6;

        position p;
        p.row = 0;
        p.column = 2;

        position q;
        q.row = 2;
        q.column = 0;


        if (chessGameSetMove(game, a, f) != SP_CHESS_GAME_INVALID_MOVE) { printf("Error 9\n"); }
        if (chessGameSetMove(game, b, a) != SP_CHESS_GAME_INVALID_ARGUMENT) { printf("Error 10\n"); }
        if (chessGameSetMove(game, d, c) != SP_CHESS_GAME_INVALID_ARGUMENT) { printf("Error 11\n"); }
        if (chessGameSetMove(game, k, l) != SP_CHESS_GAME_INVALID_MOVE) { printf("Error 12\n"); }
        if (chessGameSetMove(game, k, f) != SP_CHESS_GAME_INVALID_MOVE) { printf("Error 13\n"); }

        a.row = 7;
        a.column = 3;
        b.row = 4;
        b.column = 3;
        c.row = 6;
        c.column = 2;


        if (chessGameSetMove(game, a, b) != SP_CHESS_GAME_INVALID_MOVE) { printf("Error 14\n"); }
        if (chessGameSetMove(game, a, c) != SP_CHESS_GAME_INVALID_MOVE) { printf("Error 15\n"); }


        if (chessGameSetMove(game, d, f) != SP_CHESS_GAME_SUCCESS) { printf("Error 16\n"); } // 1,1 -> 3,1 whitePawn
        if (chessGameSetMove(game, g, h) != SP_CHESS_GAME_SUCCESS) { printf("Error 17\n"); } // 7,6 -> 5,7 blackKnight



        if (chessGameSetMove(game, p, q) != SP_CHESS_GAME_SUCCESS) { printf("Error 18\n"); } // 0,2 -> 2,0 whiteBishop
        if (chessGameSetMove(game, m, n) != SP_CHESS_GAME_SUCCESS) { printf("Error 19\n"); } // 6,6 -> 5,6 blackPawn

        chessGamePrintBoard(game);


        printf("\n copied game: \n");

        SPChessGame *game1 = chessGameCopy(game);


        chessGamePrintBoard(game1);
        chessGameDestroy(&game1);


        printf("\n\n\n new game \n\n\n");

        chessGameDestroy(&game);
        game = chessGameCreate();

        a.row = 1;
        a.column = 7;
        b.row = 3;
        b.column = 7;
        c.row = 6;
        c.column = 6;
        d.row = 4;
        d.column = 6;


        if (chessGameSetMove(game, a, b) != SP_CHESS_GAME_SUCCESS) { printf("Error 20\n"); } // 1,7 -> 3,7 whitePawn
        if (whosThere(game, 3, 7) != PAWNWHITE) { printf(" Error 21\n"); }
        if (whosThere(game, 1, 7) != BLANK) { printf(" Error 22\n"); }
        if (chessGameSetMove(game, c, d) != SP_CHESS_GAME_SUCCESS) { printf("Error 23\n"); } // 6,6 -> 4,6 blackPawn
        if (whosThere(game, 4, 6) != PAWNBLACK) { printf(" Error 24\n"); }
        if (whosThere(game, 6, 6) != BLANK) { printf(" Error 25\n"); }

        a.row = 3;
        a.column = 7;
        b.row = 4;
        b.column = 6;
        c.row = 7;
        c.column = 1;
        d.row = 5;
        d.column = 0;

        if (chessGameSetMove(game, a, b) != SP_CHESS_GAME_SUCCESS) { printf("Error 26\n"); } // 3,7 -> 4,6 whitepawn
        if (whosThere(game, 4, 6) != PAWNWHITE) { printf(" Error 27\n"); }
        if (whosThere(game, 3, 7) != BLANK) { printf(" Error 28\n"); }
        if (chessGameSetMove(game, c, d) != SP_CHESS_GAME_SUCCESS) { printf("Error 29\n"); } // 7,1 -> 5,0 blackKnight
        if (whosThere(game, 5, 0) != KNIGHTBLACK) { printf(" Error 30\n"); }
        if (whosThere(game, 7, 1) != BLANK) { printf(" Error 31\n"); }


        a.row = 1;
        a.column = 1;
        b.row = 2;
        b.column = 1;
        c.row = 5;
        c.column = 0;
        d.row = 4;
        d.column = 2;

        if (chessGameSetMove(game, a, b) != SP_CHESS_GAME_SUCCESS) { printf("Error 32\n"); } // 1,1 -> 2,1 whitepawn
        if (whosThere(game, 2, 1) != PAWNWHITE) { printf(" Error 33\n"); }
        if (whosThere(game, 1, 1) != BLANK) { printf(" Error 34\n"); }
        if (chessGameSetMove(game, c, d) != SP_CHESS_GAME_SUCCESS) { printf("Error 35\n"); } // 5,0 -> 4,2 blackKnight
        if (whosThere(game, 4, 2) != KNIGHTBLACK) { printf(" Error 36\n"); }
        if (whosThere(game, 5, 0) != BLANK) { printf(" Error 37\n"); }


        chessGamePrintBoard(game);


        if (chessGameUndoPrevMove(game1) != SP_CHESS_GAME_INVALID_ARGUMENT) { printf("Error 38\n"); } // destroyed
        if (chessGameUndoPrevMove(game) != SP_CHESS_GAME_SUCCESS) { printf("Error 39\n"); }
        if (chessGameUndoPrevMove(game) != SP_CHESS_GAME_SUCCESS) { printf("Error 40\n"); }
        if (chessGameUndoPrevMove(game) != SP_CHESS_GAME_SUCCESS) { printf("Error 41\n"); }
        if (chessGameUndoPrevMove(game) != SP_CHESS_GAME_SUCCESS) { printf("Error 42\n"); }
        if (chessGameUndoPrevMove(game) != SP_CHESS_GAME_SUCCESS) { printf("Error 43\n"); }
        if (chessGameUndoPrevMove(game) != SP_CHESS_GAME_SUCCESS) { printf("Error 44\n"); }
        if (chessGameUndoPrevMove(game) != SP_CHESS_GAME_NO_HISTORY) { printf("Error 45\n"); }


        chessGamePrintBoard(game);

        a.row = 1;
        a.column = 3;
        b.row = 3;
        b.column = 3;
        c.row = 6;
        c.column = 2;
        d.row = 5;
        d.column = 2;
        if (chessGameSetMove(game, a, b) != SP_CHESS_GAME_SUCCESS) { printf("Error 46\n"); } // 1,3 -> 3,3 whitepawn
        if (whosThere(game, 3, 3) != PAWNWHITE) { printf(" Error 47\n"); }
        if (whosThere(game, 1, 3) != BLANK) { printf(" Error 48\n"); }
        if (chessGameSetMove(game, c, d) != SP_CHESS_GAME_SUCCESS) { printf("Error 49\n"); } // 6,2 -> 5,2 blackPawn
        if (whosThere(game, 5, 2) != PAWNBLACK) { printf(" Error 50\n"); }
        if (whosThere(game, 6, 2) != BLANK) { printf(" Error 51\n"); }
        a.row = 1;
        a.column = 7;
        b.row = 2;
        b.column = 7;
        c.row = 7;
        c.column = 3;
        d.row = 4;
        d.column = 0;
        if (chessGameSetMove(game, a, b) != SP_CHESS_GAME_SUCCESS) { printf("Error 52\n"); } // 1,7 -> 2,7 whitepawn
        if (whosThere(game, 2, 7) != PAWNWHITE) { printf(" Error 53\n"); }
        if (whosThere(game, 1, 7) != BLANK) { printf(" Error 54\n"); }
        if (chessGameSetMove(game, c, d) != SP_CHESS_GAME_SUCCESS) { printf("Error 55\n"); } // 7,3// -> 4,0 blackQueen
        if (whosThere(game, 4, 0) != QUEENBLACK) { printf(" Error 56\n"); }
        if (whosThere(game, 7, 3) != BLANK) { printf(" Error 57\n"); }


        //Check to the blacks

        a.row = 0;
        a.column = 3;
        b.row = 2;
        b.column = 3;
        if (chessGameSetMove(game, a, b) != SP_CHESS_GAME_INVALID_MOVE) {
            printf("Error 58\n");
        } // 0,3 -> 2,3 whiteQueen
        a.row = 1;
        a.column = 5;
        b.row = 3;
        b.column = 5;
        if (chessGameSetMove(game, a, b) != SP_CHESS_GAME_INVALID_MOVE) {
            printf("Error 59\n");
        } // 1,5 -> 3,5 whitePawn

        a.row = 0;
        a.column = 3;
        b.row = 1;
        b.column = 3;
        c.row = 4;
        c.column = 0;
        d.row = 0;
        d.column = 4;
        if (chessGameSetMove(game, a, b) != SP_CHESS_GAME_SUCCESS) { printf("Error 60\n"); } // 0,3 -> 1,3 whiteQueen
        if (whosThere(game, 1, 3) != QUEENWHITE) { printf(" Error 61\n"); }
        if (whosThere(game, 0, 3) != BLANK) { printf(" Error 62\n"); }
        if (chessGameSetMove(game, c, d) != SP_CHESS_GAME_INVALID_MOVE) {
            printf("Error 63\n");
        } // 4,0 -> 0,4 blackQueen IMPOSSIBLE TO SKIP q
        d.row = 1;
        d.column = 3;
        if (chessGameSetMove(game, c, d) != SP_CHESS_GAME_SUCCESS) { printf("Error 64\n"); } // 4,0 -> 1,3 blackQueen
        if (whosThere(game, 1, 3) != QUEENBLACK) { printf(" Error 65\n"); }
        if (whosThere(game, 4, 0) != BLANK) { printf(" Error 66\n"); }

        chessGamePrintBoard(game);
    }

//char whosThere(SPChessGame *src, int row, int col) {
//    if (col < 0 || col > 7 || row < 0 || row > 7) {
//        return '\0';
//    }
//    return src->gameBoard[row][col];
//}


//}