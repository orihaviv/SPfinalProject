//
// Created by אורי חביב on 24/09/2017.
//

#ifndef FINALPROJECT_SPCHESSSETTINGSWIN_H
#define FINALPROJECT_SPCHESSSETTINGSWIN_H

#include <stdbool.h>
#include <SDL.h>
#include "../SPMainAux.h"

//Definitions
#define HEIGHT_SETTINGS 700
#define WIDTH_SETTINGS 1000

#define TITLE_SETTINGS_H 80
#define TITLE_SETTINGS_W 250
#define TITLE_SETTINGS_X 230
#define TITLE_SETTINGS_Y 90

#define LABELS_H 50
#define BUTTONS_H 50

#define GAME_MODE_W 250
#define COLOR_W 135
#define DIFFICULTY_W 200

#define PIC_W 170
#define PIC_H 250
#define PIC_X 470
#define PIC_Y 10

#define ONE_PLAYER_W 245
#define TWO_PLAYERS_W 254

#define WHITE_BLACK_W 222

#define NOOB_EASY_HARD_W 210

#define MODERATE_W 228

#define START_W 246
#define BACK_W 234

#define GAMEMODEX 20
#define GAMEMODEY 270
#define ONEPLAYERX 280
#define TWOPLAYERSX 600

#define USERCOLORX 20
#define USERCOLORY 350
#define WHITEX 290
#define BLACKX 610

#define STARTX 600
#define START_BACK_Y 600
#define BACKX 100

#define DIFFICULTYX 20
#define DIFFICULTYY 410
#define NOOB_EASY_MODERATE_HARD_Y 490
#define NOOBX 30
#define EASYX 250
#define MODERATEX 470
#define HARDX 710




typedef enum {
    SP_SETTINGS_BACK,
    SP_SETTINGS_START,
    SP_SETTINGS_ONE_PLAYER,
    SP_SETTINGS_TWO_PLAYERS,
    SP_SETTINGS_WHITE_USER,
    SP_SETTINGS_BLACK_USER,
    SP_SETTINGS_NOOB,
    SP_SETTINGS_EASY,
    SP_SETTINGS_MODERATE,
    SP_SETTINGS_HARD,
    SP_SETTINGS_INVALID_ARGUMENT,
    SP_SETTINGS_NONE,
} SP_SETTINGS_EVENT;

typedef struct {
    SDL_Window* settingsWindow;
    SDL_Renderer* settingsRenderer;
    SDL_Texture* settingsTitle;
    SDL_Texture* settingsPicture;
    SDL_Texture* numOfPlayersTitle;
    SDL_Texture* difficultyTitle;
    SDL_Texture* userColorTitle;
    SDL_Texture* startTexture;
    SDL_Texture* backTexture;
    SDL_Texture** onePlayerTexture;
    SDL_Texture* onePlayerBoldTexture;
    SDL_Texture* onePlayerThinTexture;
    SDL_Texture** twoPlayersTexture;
    SDL_Texture* twoPlayersThinTexture;
    SDL_Texture* twoPlayersBoldTexture;
    SDL_Texture** whiteUserTexture;
    SDL_Texture* whiteUserThinTexture;
    SDL_Texture* whiteUserBoldTexture;
    SDL_Texture** blackUserTexture;
    SDL_Texture* blackUserThinTexture;
    SDL_Texture* blackUserBoldTexture;
    SDL_Texture** noobTexture;
    SDL_Texture* noobThinTexture;
    SDL_Texture* noobBoldTexture;
    SDL_Texture** easyTexture;
    SDL_Texture* easyThinTexture;
    SDL_Texture* easyBoldTexture;
    SDL_Texture** moderateTexture;
    SDL_Texture* moderateThinTexture;
    SDL_Texture* moderateBoldTexture;
    SDL_Texture** hardTexture;
    SDL_Texture* hardThinTexture;
    SDL_Texture* hardBoldTexture;
    int numOfPlayers;
    int diff;
    int color;
} SPSettingsWin;

SPSettingsWin* spSettingsWindowCreate();
void spSettingsWindowDestroy(SPSettingsWin* src);
void spSettingsWindowDraw(SPSettingsWin* src);
void spSettingsWindowHide(SPSettingsWin* src);
void spSettingsWindowShow(SPSettingsWin* src);
SP_SETTINGS_EVENT spSettingsWindowHandleEvent(SPSettingsWin* src, SDL_Event* event);

#endif //FINALPROJECT_SPCHESSSETTINGSWIN_H
