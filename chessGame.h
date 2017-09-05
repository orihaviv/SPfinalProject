//
// Created by אורי חביב on 05/09/2017.
//

#ifndef SPFINAL_CHESSGAME_H
#define SPFINAL_CHESSGAME_H

typedef struct sp_chess_game_t {
    char gameBoard[8][8];
    int gameMode; // 1 = 1 player, 2 = 2 players
    int numCurrentPlayer; //
    int difficulty;
    int userColor; // 0 = black, 1 = white
    int state; // settings = 0, game = 1
} SPChessGame;




#endif //SPFINAL_CHESSGAME_H
