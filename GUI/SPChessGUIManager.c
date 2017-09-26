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
        spSettingsWindowDraw(src->settingsWin);
    } else if (src->activeWin == SP_LOAD_WINDOW_ACTIVE){
        spLoadWindowDraw(src->loadWin);
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
            src->game = chessGameCreate();
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
            spSettingsWindowHide(src->settingsWin);
            src->gameWin = spGameWindowCreate();
            src->game->state = 1;
            if (src->gameWin == NULL ) {
                printf("Couldn't create settings window\n");
                return SP_MANAGER_QUTT;
            }
            src->activeWin = SP_GAME_WINDOW_ACTIVE;
            break;
        case SP_SETTINGS_ONE_PLAYER:
            src->game->gameMode = 1;
            src->game->userColor = 1;
            src->game->difficulty = 2;
            break;
        case SP_SETTINGS_TWO_PLAYERS:
            src->game->gameMode = 2;
            break;
        case SP_SETTINGS_WHITE_USER:
            src->game->userColor = 1;
            break;
        case SP_SETTINGS_BLACK_USER:
            src->game->userColor = 0;
            break;
        case SP_SETTINGS_NOOB:
            src->game->difficulty = 1;
            break;
        case SP_SETTINGS_EASY:
            src->game->difficulty = 2;
            break;
        case SP_SETTINGS_MODERATE:
            src->game->difficulty = 3;
            break;
        case SP_SETTINGS_HARD:
            src->game->difficulty = 4;
            break;
        default:
            break;
    }
    return SP_MANAGER_NONE;
}


void handleSaveGame(SPGuiManager* src){
    if (src->gameWin->isTheGameSaved == 0){
        if (guiSaveGame(src->game) == 0){
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Not able to save the game", NULL);
        }
        else {
            src->gameWin->isTheGameSaved = 1;
        }
    }
}

void handleLoadGame(SPGuiManager* src){
    //TODO
    src->gameWin->isTheGameSaved = 1;
}

int askWhetherToSave(SPGuiManager* src){
    const SDL_MessageBoxButtonData buttons[] = {
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "yes" },
            {                                       0, 1, "no" },
            { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "cancel" },
    };
    const SDL_MessageBoxColorScheme colorScheme = {
            {
                    /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
                    { 255,   0,   0 },
                    /* [SDL_MESSAGEBOX_COLOR_TEXT] */
                    {   0, 255,   0 },
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
                    { 255, 255,   0 },
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
                    {   0,   0, 255 },
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
                    { 255,   0, 255 }
            }
    };
    const SDL_MessageBoxData messageBoxData = {
            SDL_MESSAGEBOX_INFORMATION,
            NULL,
            "You are about to quit the game" , /* .title */
            "Do you want to save the current game?", /* .message */
            SDL_arraysize(buttons), /* .numOfButtons */
            buttons, /* .buttons */
            &colorScheme /* .colorScheme */
    };
    int buttonID;
    if (SDL_ShowMessageBox(&messageBoxData, &buttonID) < 0) {
        SDL_Log("error displaying message box");
        return 0;
    }
    switch (buttonID) {
        case 0:
            handleSaveGame(src);
            return 1;
        case 1:
            return 1;
        case 2:
            return 0;
        default:
            break;
    }
    return 0;
}


void handleMainMenu(SPGuiManager* src){
    int whetherToQuit = 1;
    if (src->gameWin->isTheGameSaved == 0) {
        whetherToQuit = askWhetherToSave(src);
    }
    if (whetherToQuit == 1) {
        spGameWindowDestroy(src->gameWin);
        spSettingsWindowDestroy(src->settingsWin);
        src->activeWin = SP_MAIN_WINDOW_ACTIVE;
    }
}


SP_MANAGER_EVENT handleQuitGame(SPGuiManager* src){
    int whetherToQuit = 1;
    if (src->gameWin->isTheGameSaved == 0) {
        whetherToQuit = askWhetherToSave(src);
    }
    if (whetherToQuit == 1){
        return SP_MANAGER_QUTT;
    }
    return SP_MANAGER_NONE;
}


SP_MANAGER_EVENT handleManagerDueToGameEvent(SPGuiManager* src, SP_GAME_EVENT event) {
    if (event == SP_GAME_EVENT_NONE || src == NULL ) {
        return SP_MANAGER_NONE;
    }
    switch(event){
        case SP_GAME_EVENT_WHITE_WON:
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "White won", NULL);
            break;
        case SP_GAME_EVENT_BLACK_WON:
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "Black won", NULL);
            break;
        case SP_GAME_EVENT_TIE:
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "It's a tie", NULL);
            break;
        case SP_GAME_EVENT_RESTART:
            initializeBoard(src->game);
            src->gameWin->isTheGameSaved = 0;
            break;
        case SP_GAME_EVENT_SAVE:
            handleSaveGame(src);
            break;
        case SP_GAME_EVENT_LOAD:
            handleLoadGame(src);
            break;
        case SP_GAME_EVENT_UNDO:
            chessGameUndoPrevMove(src->game);
            chessGameUndoPrevMove(src->game);
            break;
        case SP_GAME_EVENT_MAIN_MENU:
            handleMainMenu(src);
            break;
        case SP_GAME_EVENT_QUIT:
            return handleQuitGame(src);
        case SP_GAME_EVENT_MOVE:
            src->gameWin->isTheGameSaved = 1;
            // TODO
            break;
        default:
            break;
    }
//	spGameWindowDestroy(src->gameWin);
//	src->gameWin = NULL;
//	src->activeWin = SP_MAIN_WINDOW_ACTIVE;
//	spMainWindowShow(src->mainWin);
    return SP_MANAGER_NONE;
}


SP_MANAGER_EVENT spManagerHandleEvent(SPGuiManager* src, SDL_Event* event) {
    if (src == NULL || event == NULL ) {
        return SP_MANAGER_NONE;
    }
    SP_MAIN_EVENT mainEvent;
    SP_SETTINGS_EVENT settingsEvent;
    SP_GAME_EVENT gameEvent;
    SP_LOAD_EVENT loadEvent;
    switch (src->activeWin){
        case SP_MAIN_WINDOW_ACTIVE:
            mainEvent = spMainWindowHandleEvent(src->mainWin, event);
            return handleManagerDueToMainEvent(src, mainEvent);
        case SP_SETTINGS_WINDOW_ACTIVE:
            settingsEvent = spSettingsWindowHandleEvent(src->settingsWin, event);
            return handleManagerDueToSettingsEvent(src, settingsEvent);
        case SP_GAME_WINDOW_ACTIVE:
            gameEvent = spGameWindowHandleEvent(src->gameWin, event);
            return handleManagerDueToGameEvent(src, gameEvent);
        case SP_LOAD_WINDOW_ACTIVE:
//            loadEvent = spLoadWindowHandleEvent(src->loadWin, event); //TODO
//            return handleManagerDueToLoadEvent(src, loadEvent);
        default:
            break;
    }
    return SP_MANAGER_NONE;
}
