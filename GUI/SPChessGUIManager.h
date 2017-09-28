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
	SP_MANAGER_WHITE_WON,
	SP_MANAGER_BLACK_WON,
	SP_MANAGER_TIE,
	SP_MANAGER_CHECK,
	SP_MANAGER_NONE,
}SP_MANAGER_EVENT;

typedef struct {
	SPMainWin* mainWin;
	SPSettingsWin* settingsWin;
	SPLoadWin* loadWin;
	SPGameWin* gameWin;
	ACTIVE_WINDOW activeWin;
	SPChessGame* game;
	int checked;
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

/**
 * Showing an ending relevant winner message box
 * @param winner  - 1 = white, 2 = tie, 0 = black
 * @param src - the gui manager
 * @return
 */

int showEndingMessageBox(int winner, SPGuiManager *src);


/**
 * Showing an check message box
 * @param player - the player that his king is threatened
 * @return
 */

void showCheckMessage(int player);


SP_MANAGER_EVENT spManagerHandleEvent(SPGuiManager* src, SDL_Event* event);


#endif
