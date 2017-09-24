//#ifndef SPCHESSGAMEWIN_H_
//#define SPCHESSGAMEWIN_H_
//#include <SDL.h>
//#include <SDL_video.h>
//#include "SPChessWindow.h"
//#include "../SPMainAux.h"
//
//typedef enum {
//	SP_GAME_EVENT_WHITE_WON,
//	SP_GAME_EVENT_BLACK_WON,
//	SP_GAME_EVENT_TIE,
//	SP_GAME_EVENT_QUIT,
//	SP_GAME_EVENT_INVALID_ARGUMENT,
//	SP_GAME_EVENT_NONE
//} SP_GAME_EVENT;
//
//typedef struct{
//	SDL_Window* window;
//	SDL_Renderer* renderer;
//	SDL_Texture* bgTexture;
//	SDL_Texture* xTexture;
//	SDL_Texture* oTexture;
//	SPChessGame* game;
//}SPGameWin;
//
//SPGameWin* spGameWindowCreate();
//void spGameWindowDraw(SPGameWin*);
//void spGameWindowDestroy(SPGameWin*);
//SP_GAME_EVENT spGameWindowHandleEvent(SPGameWin* src, SDL_Event* event);
//
//
//#endif
