



#ifndef SPCHESSMAINWIN_H_
#define SPCHESSMAINWIN_H_

#include <stdbool.h>
//#include "../SPMainAux.h"
#include <SDL.h>

//Definitions

#define MAIN_WINDOW_W 400
#define MAIN_WINDOW_H 400

#define OBJECTS_X 75
#define PIC_Y 10
#define NEW_Y 180
#define LOAD_Y 245
#define QUIT_Y 310



#define BUTTONS_W 250
#define BUTTONS_H 50
#define PICTURE_W_H 200

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


/**
 * Creates a new main window
 *
 * @return
 * NULL if either a memory allocation failure occurs.
 * Otherwise, a new main window instant is returned.
 */
SPMainWin* spMainWindowCreate();


/**
 * Frees all memory allocation associated with a given window.
 * If src==NULL - the function does nothing.
 *
 * @param src - the source window
 */
void spMainWindowDestroy(SPMainWin* src);


/**
 * Draws the window according to the specified fields
 *
 * @param src - the source window
 */
void spMainWindowDraw(SPMainWin* src);


/**
 * Hides the specified window
 *
 * @param src - the source window
 */
void spMainWindowHide(SPMainWin* src);


/**
 * Shows the specified window
 *
 * @param src - the source window
 */
void spMainWindowShow(SPMainWin* src);


/**
 * Handles events occured in the specified window
 *
 * @param event - the event to be handled
 */
SP_MAIN_EVENT spMainWindowHandleEvent(SDL_Event* event);

#endif
