#ifndef SPCHESSGUIMANAGER_H_
#define SPCHESSGUIMANAGER_H_
#include <SDL.h>
#include "SPChessMainWin.h"
#include "SPChessSettingsWin.h"
#include "SPChessLoadWin.h"
#include "SPChessGameWin.h"


typedef enum{
	SP_MAIN_WINDOW_ACTIVE,
	SP_GAME_WINDOW_ACTIVE,
	SP_LOAD_WINDOW_ACTIVE,
	SP_SETTINGS_WINDOW_ACTIVE,
}ACTIVE_WINDOW;

typedef enum{
	SP_MANAGER_QUTT,
	SP_MANAGER_NONE,
}SP_MANAGER_EVENT;

typedef struct {
	SPMainWin* mainWin;
	SPSettingsWin* settingsWin;
	SPLoadWin* loadWin;
	SPGameWin* gameWin;
	ACTIVE_WINDOW activeWin;
	SPChessGame* game;
} SPGuiManager;



typedef enum {
	SP_PROMOTION_PAWN,
	SP_PROMOTION_ROOK,
	SP_PROMOTION_KNIGHT,
	SP_PROMOTION_BISHOP,
	SP_PROMOTION_QUEEN,
	SP_PROMOTION_INVALID
} SP_PROMOTION_EVENT;


SPGuiManager* spManagerCreate();

void spManagerDestroy(SPGuiManager* src);

void spManagerDraw(SPGuiManager* src);

SP_MANAGER_EVENT spManagerHandleEvent(SPGuiManager* src, SDL_Event* event) ;


#endif
