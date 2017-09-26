#include <stdio.h>
#include <stdlib.h>
#include "SPChessGUIManager.h"

SPGuiManager* spManagerCreate() {
	SPGuiManager* res = (SPGuiManager*) malloc(sizeof(SPGuiManager));
	if (res == NULL ) {
		return NULL ;
	}
	res->mainWin = spMainWindowCreate();
	if (res->mainWin == NULL ) {
		free(res);
		return NULL ;
	}
    res->loadWin = NULL;
    res->settingsWin = NULL;
	res->gameWin = NULL;
	res->activeWin = SP_MAIN_WINDOW_ACTIVE;
	return res;
}


void spManagerDestroy(SPGuiManager* src) {
	if (!src) {
		return;
	}
	if (src->gameWin != NULL) {
		spGameWindowDestroy(src->gameWin);
	}
    if (src->loadWin != NULL) {
        spLoadWindowDestroy(src->loadWin);
    }
    if (src->settingsWin != NULL) {
        spSettingsWindowDestroy(src->settingsWin);
    }
	spMainWindowDestroy(src->mainWin);
	free(src);
}


void spManagerDraw(SPGuiManager* src) {
	if (!src) {
		return;
	}
	if (src->activeWin == SP_MAIN_WINDOW_ACTIVE) {
		spMainWindowDraw(src->mainWin);
	} else if (src->activeWin == SP_SETTINGS_WINDOW_ACTIVE){
		spGameWindowDraw(src->settingsWin);
	} else if (src->activeWin == SP_LOAD_WINDOW_ACTIVE){
        spGameWindowDraw(src->loadWin);
    } else if (src->activeWin == SP_GAME_WINDOW_ACTIVE){
        spGameWindowDraw(src->gameWin);
    }
}


SP_MANAGER_EVENT handleManagerDueToMainEvent(SPGuiManager* src, SP_MAIN_EVENT event) {
	if (src == NULL ) {
		return SP_MANAGER_NONE;
	}
    switch (event){
        case SP_MAIN_NEW_GAME:
            spMainWindowHide(src->mainWin);
            src->settingsWin = spSettingsWindowCreate();
            if (src->settingsWin == NULL ) {
                printf("Couldn't create settings window\n");
                return SP_MANAGER_QUTT;
            }
            src->activeWin = SP_SETTINGS_WINDOW_ACTIVE;
            break;
        case SP_MAIN_LOAD_GAME:
            spMainWindowHide(src->mainWin);
            src->settingsWin = spSettingsWindowCreate();
            if (src->settingsWin == NULL ) {
                printf("Couldn't create settings window\n");
                return SP_MANAGER_QUTT;
            }
            src->activeWin = SP_LOAD_WINDOW_ACTIVE;
            break;
        case SP_MAIN_QUIT_GAME:
            return SP_MANAGER_QUTT;
        default:
            break;
    }
    return SP_MANAGER_NONE;
}


SP_MANAGER_EVENT handleManagerDueToSettingsEvent(SPGuiManager* src, SP_SETTINGS_EVENT event) {
    if (src == NULL) {
        return SP_MANAGER_NONE;
    }
    switch (event){
        case SP_SETTINGS_BACK:
            spSettingsWindowDestroy(src->settingsWin);
            src->activeWin = SP_MAIN_WINDOW_ACTIVE;
            break;
        case SP_SETTINGS_START:
            spMainWindowHide(src->settingsWin);
            src->settingsWin = spGameWindowCreate();
            if (src->gameWin == NULL ) {
                printf("Couldn't create settings window\n");
                return SP_MANAGER_QUTT;
            }
            src->activeWin = SP_GAME_WINDOW_ACTIVE;
            break;
        default:
            break;
    }
    return SP_MANAGER_NONE;
}


//SP_MANAGER_EVENT handleManagerDueToGameEvent(SPGuiManager* src,
//		SP_GAME_EVENT event) {
//	if (event == SP_GAME_EVENT_NONE || src == NULL ) {
//		return SP_MANAGER_NONE;
//	}
//	if (event == SP_GAME_EVENT_X_WON) {
//		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "X won",
//				NULL );
//	} else if (event == SP_GAME_EVENT_O_WON) {
//		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "O won",
//				NULL );
//	} else if (event == SP_GAME_EVENT_TIE) {
//		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over",
//				"it's a tie", NULL );
//	}
//	spGameWindowDestroy(src->gameWin);
//	src->gameWin = NULL;
//	src->activeWin = SP_MAIN_WINDOW_ACTIVE;
//	spMainWindowShow(src->mainWin);
//	return SP_MANAGER_NONE;
//}
//
//
//SP_MANAGER_EVENT spManagerHandleEvent(SPGuiManager* src, SDL_Event* event) {
//	if (src == NULL || event == NULL ) {
//		return SP_MANAGER_NONE;
//	}
//	if (src->activeWin == SP_MAIN_WINDOW_ACTIVE) {
//		SP_MAIN_EVENT mainEvent = spMainWindowHandleEvent(src->mainWin, event);
//		return handleManagerDueToMainEvent(src, mainEvent);
//	} else {
//		SP_GAME_EVENT gameEvent = spGameWindowHandleEvent(src->gameWin, event);
//		spManagerDraw(src);
//		return handleManagerDueToGameEvent(src, gameEvent);
//	}
//	return SP_MANAGER_NONE;
//}
