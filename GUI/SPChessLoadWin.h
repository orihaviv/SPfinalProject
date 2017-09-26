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
} SP_SETTINGS_EVENT;

typedef struct {
    SDL_Window* settingsWindow;
    SDL_Renderer* settingsRenderer;

    SDL_Texture* loadGameTitle;
    SDL_Texture* load;
    SDL_Texture* back;
    SDL_Texture* slotOne;
    SDL_Texture* slotOneBold;
    SDL_Texture* slotTwo;
    SDL_Texture* slotTwoBold;
    SDL_Texture* slotThree;
    SDL_Texture* slotThreeBold;
    SDL_Texture* slotFour;
    SDL_Texture* slotFourBold;
    SDL_Texture* slotFive;
    SDL_Texture* slotFiveBold;

    int chosen;
    int diff;
    int color;
} SPSettingsWin;

SPSettingsWin* spSettingsWindowCreate();
void spSettingsWindowDestroy(SPSettingsWin* src);
void spSettingsWindowDraw(SPSettingsWin* src);
void spSettingsWindowHide(SPSettingsWin* src);
void spSettingsWindowShow(SPSettingsWin* src);
SP_SETTINGS_EVENT spSettingsWindowHandleEvent(SPSettingsWin* src, SDL_Event* event);


#endif //SPFINALPROJECT_SPCHESSLOADWIN_H
