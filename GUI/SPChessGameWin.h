#ifndef SPCHESSGAMEWIN_H_
#define SPCHESSGAMEWIN_H_
#include <SDL.h>
#include <SDL_video.h>
#include "../SPMainAux.h"

//Board Definitions
#define ZERO_X 59
#define ZERO_Y 60
#define ONE_X 119
#define ONE_Y 120
#define TWO_X 179
#define TWO_Y 180
#define THREE_X 239
#define THREE_Y 240
#define FOUR_X 299
#define FOUR_Y 300
#define FIVE_X 359
#define FIVE_Y 360
#define SIX_X 419
#define SIX_Y 420
#define SEVEN_X 479
#define SEVEN_Y 480
#define RIGHT_X 539
#define BOTTOM_Y 540

#define PIECE_SIZE 60
#define BOARD_H 516
#define BOARD_W 514

#define BOARD_X 42
#define BOARD_Y 42


//Buttons Definitions
#define BUTTON_H 50
#define BUTTON_W 242
#define BUTTONS_X 616
#define FIRST_BUTTON_Y 42
#define SECOND_BUTTON_Y 122
#define THIRD_BUTTON_Y 202
#define FOURTH_BUTTON_Y 282
#define FIFTH_BUTTON_Y 362
#define SIXTH_BUTTON_Y 442



typedef enum {
	SP_GAME_EVENT_WHITE_WON,
	SP_GAME_EVENT_BLACK_WON,
	SP_GAME_EVENT_TIE,
	SP_GAME_EVENT_RESTART,
	SP_GAME_EVENT_SAVE,
	SP_GAME_EVENT_LOAD,
	SP_GAME_EVENT_UNDO,
	SP_GAME_EVENT_MAIN_MENU,
	SP_GAME_EVENT_QUIT,
	SP_GAME_EVENT_MOVE,
	SP_GAME_EVENT_INVALID_ARGUMENT,
	SP_GAME_EVENT_NONE,
} SP_GAME_EVENT;

typedef struct{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* bgTexture;
	SDL_Texture* xTexture;
	SDL_Texture* oTexture;
	SPChessGame* game;
	int isTheGameSaved;
}SPGameWin;

//SPGameWin* spGameWindowCreate();
//void spGameWindowDraw(SPGameWin*);
//void spGameWindowDestroy(SPGameWin*);
//SP_GAME_EVENT spGameWindowHandleEvent(SPGameWin* src, SDL_Event* event);


#endif
