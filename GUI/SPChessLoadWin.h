//
// Created by 0mer on 26/09/2017.
//

#ifndef SPFINALPROJECT_SPCHESSLOADWIN_H
#define SPFINALPROJECT_SPCHESSLOADWIN_H

#include <stdbool.h>
#include <SDL.h>
#include "../SPMainAux.h"


//Definitions
#define LABELS_H 43
#define BUTTONS_H 49
//#define PRESSED_BUTTONS_H 55
#define GAME_MODE_W 194
#define COLOR_W 86
#define DIFFICULTY_W 210
#define ONE_PLAYER_W 242
//#define ONE_PLAYER_PRESSED_W 248
#define TWO_PLAYERS_W 254
//#define TWO_PLAYERS_PRESSED_W 260
#define WHITE_BLACK_W 222
//#define WHITE_BLACKR_PRESSED_W 228
#define NOOB_EASY_HARD_W 210
//#define NOOB_EASY_HARD_PRESSED_W 216
#define MODERATE_W 228
//#define MODERATE_PRESSED_W 236
#define START_W 246
#define BACK_W 234

#define GAMEMODEX 20
#define GAMEMODEY 50
#define ONEPLAYERX 170
#define TWOPLAYERSX 390

#define USERCOLORX 20
#define USERCOLORY 155
#define WHITEX 175
#define BLACKX 395

#define STARTX 350
#define START_BACK_Y 430
#define BACKX 100

#define DIFFICULTYX 20
#define DIFFICULTYY 260
#define NOOB_EASY_MODERATE_HARD_Y 350
#define NOOBX 30
#define EASYX 170
#define MODERATEX 310
#define HARDX 450




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
    SDL_Texture* numOfPlayersTitle;
    SDL_Texture* difficultyTitle;
    SDL_Texture* userColorTitle;
    SDL_Texture* startTexture;
    SDL_Texture* backTexture;
    SDL_Texture* onePlayerTexture;
    SDL_Texture* onePlayerBoldTexture;
    SDL_Texture* twoPlayersTexture;
    SDL_Texture* twoPlayersBoldTexture;
    SDL_Texture* whiteUserTexture;
    SDL_Texture* whiteUserBoldTexture;
    SDL_Texture* blackUserTexture;
    SDL_Texture* blackUserBoldTexture;
    SDL_Texture* noobTexture;
    SDL_Texture* noobBoldTexture;
    SDL_Texture* easyTexture;
    SDL_Texture* easyBoldTexture;
    SDL_Texture* moderateTexture;
    SDL_Texture* moderateBoldTexture;
    SDL_Texture* hardTexture;
    SDL_Texture* hardBoldTexture;
    int numOfPlayers;
    int diff;
    int color;
    SDL_Rect gameModeR;
    SDL_Rect onePlayerR;
    SDL_Rect twoPlayersR;
    SDL_Rect userColorR;
    SDL_Rect whiteR;
    SDL_Rect blackR;
    SDL_Rect difficultyR;
    SDL_Rect noobR;
    SDL_Rect easyR;
    SDL_Rect moderateR;
    SDL_Rect hardR;
    SDL_Rect startR;
    SDL_Rect backR;
} SPSettingsWin;

SPSettingsWin* spSettingsWindowCreate();
void spSettingsWindowDestroy(SPSettingsWin* src);
void spSettingsWindowDraw(SPSettingsWin* src);
void spSettingsWindowHide(SPSettingsWin* src);
void spSettingsWindowShow(SPSettingsWin* src);
SP_SETTINGS_EVENT spSettingsWindowHandleEvent(SPSettingsWin* src, SDL_Event* event);

#endif //FINALPROJECT_SPCHESSSETTINGSWIN_H








//Definitions
#define LABEL_H 47
#define LABEL_W 250
#define LOAD_BUTTONS_H 52
#define LOAD_BUTTONS_W 80
#define LOAD_W 78



typedef enum {
    SP_LOAD_1,
    SP_LOAD_2,
    SP_LOAD_3,
    SP_LOAD_4,
    SP_LOAD_5,
    SP_LOAD_INVALID_ARGUMENT,
    SP_LOAD_NONE,
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

    int loaded;


} SPLoadWin;

SPLoadWin* spLoadWindowCreate();
void spLoadWindowDestroy(SPLoadWin* src);
void spLoadWindowDraw(SPLoadWin* src);
void spLoadWindowHide(SPLoadWin* src);
void spLoadWindowShow(SPLoadWin* src);
SP_LOAD_EVENT spLoadWindowHandleEvent(SPLoadWin* src, SDL_Event* event);


#endif //SPFINALPROJECT_SPCHESSLOADWIN_H
