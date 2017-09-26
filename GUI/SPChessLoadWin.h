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
#define BUTTONS_H 49
#define BUTTONS_W 78
#define PRESSED_BUTTONS_H 57
#define PRESSED_BUTTONS_W 86
#define LOAD_W 78



typedef enum {
    SP_LOAD_1,
    SP_LOAD_2,
    SP_LOAD_3,
    SP_LOAD_4,
    SP_LOAD_5,
    SP_LOAD_GAME,
    SP_SETTINGS_INVALID_ARGUMENT,
    SP_SETTINGS_NONE,
} SP_LOAD_EVENT;

typedef struct {
    SDL_Window* loadWindow;
    SDL_Renderer* loadRenderer;
    SDL_Texture* one;
    SDL_Texture* oneBold;
    SDL_Texture* two;
    SDL_Texture* twoBold;
    SDL_Texture* three;
    SDL_Texture* threeBold;
    SDL_Texture* four;
    SDL_Texture* fourBold;
    SDL_Texture* five;
    SDL_Texture* fiveBold;
    SDL_Texture* loadGame;
} SPLoadWin;

SPLoadWin* spLoadWindowCreate();
void spLoadWindowDestroy(SPLoadWin* src);
void spLoadWindowDraw(SPLoadWin* src);
void spLoadWindowHide(SPLoadWin* src);
void spLoadWindowShow(SPLoadWin* src);
//SP_LOAD_EVENT spLoadWindowHandleEvent(SPLoadWin* src, SDL_Event* event);


#endif //SPFINALPROJECT_SPCHESSLOADWIN_H
