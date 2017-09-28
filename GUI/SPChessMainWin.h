



#ifndef SPCHESSMAINWIN_H_
#define SPCHESSMAINWIN_H_

#include <stdbool.h>
#include "../SPMainAux.h"
#include <SDL.h>

//Definitions
#define BUTTONS_H 49
#define BUTTONS_W 260

typedef enum {
	SP_MAIN_QUIT_GAME, SP_MAIN_NEW_GAME, SP_MAIN_LOAD_GAME ,SP_MAIN_INVALID_ARGUMENT, SP_MAIN_NONE
} SP_MAIN_EVENT;

typedef struct {
	//SDL_Window* window;
	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;
	SDL_Texture* quitGameTexture;
	SDL_Texture* newGameTexture;
	SDL_Texture* loadGameTexture;
	SDL_Texture* pictureTexture;
} SPMainWin;

SPMainWin* spMainWindowCreate();
void spMainWindowDestroy(SPMainWin* src);
void spMainWindowDraw(SPMainWin* src);
void spMainWindowHide(SPMainWin* src);
void spMainWindowShow(SPMainWin* src);
SP_MAIN_EVENT spMainWindowHandleEvent(SPMainWin* src, SDL_Event* event);

#endif
