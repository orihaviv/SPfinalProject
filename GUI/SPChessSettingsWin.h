//
// Created by אורי חביב on 24/09/2017.
//

#ifndef FINALPROJECT_SPCHESSSETTINGSWIN_H
#define FINALPROJECT_SPCHESSSETTINGSWIN_H

#include <stdbool.h>
#include <SDL.h>

//Definitions
#define LABELS_H 43
#define BUTTONS_H 49
#define PRESSED_BUTTONS_H 55
#define GAME_MODE_W 194
#define COLOR_W 86
#define DIFFICULTY_W 210
#define 1_PLAYER_W 242
#define 1_PLAYER_PRESSED_W 248
#define 2_PLAYERS_W 254
#define 2_PLAYERS_PRESSED_W 260
#define WHITE_BLACK_W 222
#define WHITE_BLACKR_PRESSED_W 228
#define NOOB_EASY_HARD_W 210
#define NOOB_EASY_HARD_PRESSED_W 216
#define MODERATE_W 228
#define MODERATE_PRESSED_W 236
#define START_W 246
#define BACK_W 234

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
} SPSettingsWin;

SPSettingsWin* spSettingsWindowCreate();
void spSettingsWindowDestroy(SPSettingsWin* src);
void spSettingsWindowDraw(SPSettingsWin* src);
void spSettingsWindowHide(SPSettingsWin* src);
void spSettingsWindowShow(SPSettingsWin* src);
//SP_SETTINGS_EVENT spSettingsWindowHandleEvent(SPSettingsWin* src, SDL_Event* event);

#endif //FINALPROJECT_SPCHESSSETTINGSWIN_H
