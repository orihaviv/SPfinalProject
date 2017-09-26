#ifndef SPCHESSGAMEWIN_H_
#define SPCHESSGAMEWIN_H_
#include <SDL.h>
#include <SDL_video.h>
#include "SPChessWindow.h"
#include "../SPMainAux.h"

//Definitions
#define ZERO_X 0
#define ZERO_Y 0
#define ONE_X 0
#define ONE_Y 0
#define TWO_X 0
#define TWO_Y 0
#define THREE_X 0
#define FOUR_X 0
#define FOUR_Y 0
#define FIVE_X 0
#define FIVE_Y 0
#define SIX_X 0
#define SIX_Y 0
#define SEVEN_X 0
#define SEVEN_Y 0
#define RIGHT_X 0
#define BOTTOM_Y 0

typedef enum {
	SP_GAME_EVENT_WHITE_WON,
	SP_GAME_EVENT_BLACK_WON,
	SP_GAME_EVENT_TIE,
	SP_GAME_EVENT_QUIT,
	SP_GAME_EVENT_INVALID_ARGUMENT,
	SP_GAME_EVENT_NONE
} SP_GAME_EVENT;

typedef struct{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* bgTexture;
	SDL_Texture* xTexture;
	SDL_Texture* oTexture;
	SPChessGame* game;
}SPGameWin;

SPGameWin* spGameWindowCreate();
void spGameWindowDraw(SPGameWin*);
void spGameWindowDestroy(SPGameWin*);
SP_GAME_EVENT spGameWindowHandleEvent(SPGameWin* src, SDL_Event* event);


#endif
