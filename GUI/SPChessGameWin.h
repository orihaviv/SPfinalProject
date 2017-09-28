#ifndef SPCHESSGAMEWIN_H_
#define SPCHESSGAMEWIN_H_
#include <SDL.h>
#include <SDL_video.h>
#include "../SPMainAux.h"

//Board Definitions
#define ZERO_X 59
#define ZERO_Y 540
#define ONE_X 119
#define ONE_Y 480
#define TWO_X 179
#define TWO_Y 420
#define THREE_X 239
#define THREE_Y 360
#define FOUR_X 299
#define FOUR_Y 300
#define FIVE_X 359
#define FIVE_Y 240
#define SIX_X 419
#define SIX_Y 180
#define SEVEN_X 479
#define SEVEN_Y 120
#define RIGHT_X 539
#define BOTTOM_Y 60

#define PIECE_SIZE 60
#define BOARD_H 516
#define BOARD_W 514

#define GAME_WINDOW_H 600
#define GAME_WINDOW_W 900

#define BOARD_X 42
#define BOARD_Y 42
#define PIECE_DISTANCE_UPDATE 25


//Buttons Definitions
#define GAME_BUTTON_H 50
#define GAME_BUTTON_W 242
#define GAME_BUTTONS_X 616
#define RESTART_BUTTON_Y 42
#define SAVE_BUTTON_Y 122
#define LOAD_BUTTON_Y 202
#define UNDO_BUTTON_Y 282
#define MAIN_MENU_BUTTON_Y 362
#define QUIT_BUTTON_Y 442



typedef enum {
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
	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;
	SDL_Texture* board;
	SDL_Texture* whiteKing;
	SDL_Texture* blackKing;
	SDL_Texture* whiteQueen;
	SDL_Texture* blackQueen;
	SDL_Texture* whiteBishop;
	SDL_Texture* blackBishop;
	SDL_Texture* whiteKnight;
	SDL_Texture* blackKnight;
	SDL_Texture* whiteRook;
	SDL_Texture* blackRook;
	SDL_Texture* whitePawn;
	SDL_Texture* blackPawn;

	SDL_Texture* restartGame;
	SDL_Texture* saveGame;
	SDL_Texture* saveGameEnabled;
	SDL_Texture* loadGame;
	SDL_Texture* undoMove;
	SDL_Texture* undoMoveEnabled;
	SDL_Texture* mainMenu;
	SDL_Texture* quitGame;
    SDL_Texture** boardTiles;
//    SDL_Rect boardRects[GAMESIZE][GAMESIZE];

    SDL_Texture* yellow;
    SDL_Texture* red;
    SDL_Texture* green;
    SDL_Texture* purple;

	SDL_Event* mouseDownEvent;

	SDL_Rect dragRec;
	position moveOrigin;
	position moveDestination;

	int isTheGameSaved;
	int getMovesOn;
	int isPieceDragged;
}SPGameWin;


/**
 * Creates a new game window
 *
 * @return
 * NULL if either a memory allocation failure occurs.
 * Otherwise, a new game window instant is returned.
 */
SPGameWin* spGameWindowCreate();


/**
 * Frees all memory allocation associated with a given window.
 * If src==NULL - the function does nothing.
 *
 * @param src - the source window
 */
void spGameWindowDestroy(SPGameWin* src);


/**
 * Draws the window according to the specified fields
 *
 * @param src - the source window
 */
void spGameWindowDraw(SPGameWin* src, SPChessGame* game);


/**
 * Hides the specified window
 *
 * @param src - the source window
 */
void spGameWindowHide(SPGameWin *src);


/**
 * Shows the specified window
 *
 * @param src - the source window
 */
void spGameWindowShow(SPGameWin *src);


/**
 * Handles events occured in the specified window
 *
 * @param src - the source window
 * @param game - the current game
 * @param event - the event to be handled
 */
SP_GAME_EVENT spGameWindowHandleEvent(SPGameWin* src, SPChessGame* game, SDL_Event* event);


#endif
