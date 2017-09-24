#ifndef SPCHESSGUIMANAGER_H_
#define SPCHESSGUIMANAGER_H_
#include <SDL.h>
#include "SPChessGameWin.h"
#include "SPChessMainWin.h"

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
} SPGuiManager;

SPGuiManager* spManagerCreate();

void spManagerDestroy(SPGuiManager* src);

void spManagerDraw(SPGuiManager* src);

SP_MANAGER_EVENT spManagerHandleEvent(SPGuiManager* src, SDL_Event* event) ;


#endif
