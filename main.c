
#include "chessGame.h"
#include "chessParser.h"

int main() {
    SPChessGame* game = chessGameCreate();

    if (chessGameUndoPrevMove(game) != SP_CHESS_GAME_NO_HISTORY){ printf(" Error 1\n");}

    if (whosThere(game, 3,2) != BLANK){printf(" Error 2\n");}
    if (whosThere(game, 0,0) != ROOKWHITE){printf(" Error 3\n");}
    if (whosThere(game, 0,3) != QUEENWHITE){printf(" Error 4\n");}
    if (whosThere(game, 8,2) != '\0'){printf(" Error 5\n");}
    if (whosThere(game, 6,2) != PAWNBLACK){printf(" Error 6\n");}
    if (whosThere(game, 7,1) != KNIGHTBLACK){printf(" Error 7\n");}
    if (whosThere(game, 7,4) != KINGBLACK){printf(" Error 8\n");}

    chessGamePrintBoard(game);


    position a;
    a.row = 0;
    a.column= 0;

    position b;
    b.row = 11;
    b.column= 0;

    position c;
    c.row = 0;
    c.column= 12;

    position d;
    d.row = 1;
    d.column= 1;

    position f;
    f.row = 3;
    f.column= 1;

    position g;
    g.row = 7;
    g.column= 6;

    position h;
    h.row = 5;
    h.column= 7;

    position k;
    k.row = 7;
    k.column= 4;

    position l;
    l.row = 7;
    l.column= 3;

    position m;
    m.row = 6;
    m.column= 6;

    position n;
    n.row = 5;
    n.column= 6;

    position p;
    p.row = 0;
    p.column= 2;

    position q;
    q.row = 2;
    q.column= 0;


    if (chessGameSetMove(game,a,f) != SP_CHESS_GAME_INVALID_MOVE){printf("Error 9\n");}
    if (chessGameSetMove(game,b,a) != SP_CHESS_GAME_INVALID_ARGUMENT){printf("Error 10\n");}
    if (chessGameSetMove(game,d,c) != SP_CHESS_GAME_INVALID_ARGUMENT){printf("Error 11\n");}
    if (chessGameSetMove(game,k,l) != SP_CHESS_GAME_INVALID_MOVE){printf("Error 12\n");}
    if (chessGameSetMove(game,k,f) != SP_CHESS_GAME_INVALID_MOVE){printf("Error 13\n");}

    a.row = 7; a.column = 3;
    b.row = 4; b.column = 3;
    c.row = 6; c.column = 2;


    if (chessGameSetMove(game,a,b) != SP_CHESS_GAME_INVALID_MOVE){printf("Error 14\n");}
    if (chessGameSetMove(game,a,c) != SP_CHESS_GAME_INVALID_MOVE){printf("Error 15\n");}



    if (chessGameSetMove(game,d,f) != SP_CHESS_GAME_SUCCESS){printf("Error 16\n");} // 1,1 -> 3,1 whitePawn
    if (chessGameSetMove(game,g,h) != SP_CHESS_GAME_SUCCESS){printf("Error 17\n");} // 7,6 -> 5,7 blackKnight



    if (chessGameSetMove(game,p,q) != SP_CHESS_GAME_SUCCESS){printf("Error 18\n");} // 0,2 -> 2,0 whiteBishop
    if (chessGameSetMove(game,m,n) != SP_CHESS_GAME_SUCCESS){printf("Error 19\n");} // 6,6 -> 5,6 blackPawn

    chessGamePrintBoard(game);



    printf("\n copied game: \n");

    SPChessGame* game1 = chessGameCopy(game);
    chessGameDestroy(game);

    chessGamePrintBoard(game1);
    chessGameDestroy(game1);


    printf("\n\n\n new game \n\n\n");

    game1 = chessGameCreate();

    a.row = 1; a.column = 7;
    b.row = 3; b.column = 7;
    c.row = 6; c.column = 6;
    d.row = 4; d.column = 6;


    if (chessGameSetMove(game1,a,b) != SP_CHESS_GAME_SUCCESS){printf("Error 20\n");} // 1,7 -> 3,7 whitePawn
    if (chessGameSetMove(game1,c,d) != SP_CHESS_GAME_SUCCESS){printf("Error 21\n");} // 6,6 -> 4,6 blackPawn

    a.row = 3; a.column = 7;
    b.row = 4; b.column = 6;
//    c.row = ; c.column = ;
//    d.row = ; d.column = ;

    if (chessGameSetMove(game1,a,b) != SP_CHESS_GAME_SUCCESS){printf("Error 22\n");} // 3,7 -> 4,6 whitepawn
    if (chessGameUndoPrevMove(game1) != SP_CHESS_GAME_SUCCESS){printf("Error 23\n");}
//    if (chessGameSetMove(game1,c,d) != SP_CHESS_GAME_SUCCESS){printf("Error 23\n");} // 6,6 -> 5,6 blackPawn

    chessGamePrintBoard(game1);



}

