//
// Created by 0mer on 26/09/2017.
//

#ifndef SPFINALPROJECT_SPCHESSLOADWIN_H
#define SPFINALPROJECT_SPCHESSLOADWIN_H

#include <stdbool.h>
#include <SDL.h>
#include "../SPMainAux.h"



//Definitions

#define LABEL_H 47
#define LABEL_W 250
#define LABALX 210
#define LABELY 75
#define NUM_BUTTONS_H 52
#define NUM_BUTTONS_W 80
#define NUMY 200
#define ONEX 75
#define TWOX 185
#define THREEX 295
#define FOURX 405
#define FIVEX 515
#define LOAD_W 174
#define LOAD_H 48
#define LOADX 380
#define LOAD_AND_BACK_Y 325


#define LOAD_BACK_W 235
#define LOAD_BACK_H 47
#define LOAD_BACKX 100



typedef enum {
    SP_LOAD_1,
    SP_LOAD_2,
    SP_LOAD_3,
    SP_LOAD_4,
    SP_LOAD_5,
    SP_LOAD_BACK_MAIN,
    SP_LOAD_BACK_GAME,
    SP_LOAD_INVALID_ARGUMENT,
    SP_LOAD_NONE,
} SP_LOAD_EVENT;

typedef enum {
    GAME_CALLER,
    MAIN_CALLER,
} SP_LOAD_CALLER;

typedef struct {
    SDL_Window* loadWindow;
    SDL_Renderer* loadRenderer;
    SDL_Texture** one;
    SDL_Texture* oneThin;
    SDL_Texture* oneBold;
    SDL_Texture** two;
    SDL_Texture* twoThin;
    SDL_Texture* twoBold;
    SDL_Texture** three;
    SDL_Texture* threeThin;
    SDL_Texture* threeBold;
    SDL_Texture** four;
    SDL_Texture* fourThin;
    SDL_Texture* fourBold;
    SDL_Texture** five;
    SDL_Texture* fiveThin;
    SDL_Texture* fiveBold;
    SDL_Texture* loadGame;
    SDL_Texture* back;
    SDL_Texture* loadGameTitle;

    SP_LOAD_CALLER caller;
    int marked;
    int numOfSlots;

} SPLoadWin;

SPLoadWin* spLoadWindowCreate(SP_LOAD_CALLER father);
void spLoadWindowDestroy(SPLoadWin* src);
void spLoadWindowDraw(SPLoadWin* src);
void spLoadWindowHide(SPLoadWin* src);
void spLoadWindowShow(SPLoadWin* src);
SP_LOAD_EVENT spLoadWindowHandleEvent(SPLoadWin* src, SDL_Event* event);


#endif //SPFINALPROJECT_SPCHESSLOADWIN_H
