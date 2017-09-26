//
// Created by אורי חביב on 24/09/2017.
//



#include "SPChessSettingsWin.h"

//Inner functions

int isClickOnStart(int x, int y) {
    if ((x >= STARTX && x <= START_W + STARTX) && (y >= START_BACK_Y && y <= START_BACK_Y + BUTTONS_H)) {
        return 1;
    }
    return 0;
}

int isClickOnBack(int x, int y) {
    if ((x >= BACKX && x <= START_W + BACKX) && (y >= START_BACK_Y && y <= START_BACK_Y + BUTTONS_H)) {
        return 1;
    }
    return 0;
}

int isClickOnOnePlayer(int x, int y) {
    if ((x >= ONEPLAYERX && x <= ONEPLAYERX + ONE_PLAYER_W) && (y >= GAMEMODEY && y <= GAMEMODEY + BUTTONS_H)) {
        return 1;
    }
    return 0;
}

int isClickOnTwoPlayers(int x, int y) {
    if ((x >= TWOPLAYERSX && x <= TWOPLAYERSX + TWO_PLAYERS_W) && (y >= GAMEMODEY && y <= GAMEMODEY + BUTTONS_H)) {
        return 1;
    }
    return 0;
}

int isClickOnNoob(int x, int y) {
    if ((x >= NOOBX && x <= NOOBX + NOOB_EASY_HARD_W) && (y >= NOOB_EASY_MODERATE_HARD_Y && y <= NOOB_EASY_MODERATE_HARD_Y + BUTTONS_H)) {
        return 1;
    }
    return 0;
}

int isClickOnEasy(int x, int y) {
    if ((x >= EASYX && x <= EASYX + NOOB_EASY_HARD_W) && (y >= NOOB_EASY_MODERATE_HARD_Y && y <= NOOB_EASY_MODERATE_HARD_Y + BUTTONS_H)) {
        return 1;
    }
    return 0;
}

int isClickOnModerate(int x, int y) {
    if ((x >= MODERATEX && x <= MODERATEX + MODERATE_W) && (y >= NOOB_EASY_MODERATE_HARD_Y && y <= NOOB_EASY_MODERATE_HARD_Y + BUTTONS_H)) {
        return 1;
    }
    return 0;
}

int isClickOnHard(int x, int y) {
    if ((x >= HARDX && x <= HARDX + NOOB_EASY_HARD_W) && (y >= NOOB_EASY_MODERATE_HARD_Y && y <= NOOB_EASY_MODERATE_HARD_Y + BUTTONS_H)) {
        return 1;
    }
    return 0;
}

int isClickOnWhite(int x, int y) {
    if ((x >= WHITEX && x <= WHITEX + WHITE_BLACK_W) && (y >= USERCOLORY && y <= USERCOLORY + BUTTONS_H)) {
        return 1;
    }
    return 0;
}

int isClickOnBlack(int x, int y) {
    if ((x >= BLACKX && x <= BLACKX + WHITE_BLACK_W) && (y >= USERCOLORY && y <= USERCOLORY + BUTTONS_H)) {
        return 1;
    }
    return 0;
}

bool loadingSurfaceFunc(SPSettingsWin *src, SDL_Texture** texture, char* path) {
    SDL_Surface *loadingSurface = NULL;
    loadingSurface = SDL_LoadBMP(path);
    if (loadingSurface == NULL) {
        spSettingsWindowDestroy(src);
        printf("couldn't create %s surface\n", path);
        SDL_FreeSurface(loadingSurface);
        return false;
    }
    *texture = SDL_CreateTextureFromSurface(src->settingsRenderer, loadingSurface);
    if (*texture == NULL) {
        SDL_FreeSurface(loadingSurface);
        spSettingsWindowDestroy(src);
        printf("couldn't create %s texture\n", path);
        SDL_FreeSurface(loadingSurface);
        return false;
    }
    SDL_FreeSurface(loadingSurface);
    return true;
}





SPSettingsWin *spSettingsWindowCreate() {
    SPSettingsWin *res = NULL;
    res = (SPSettingsWin *) malloc(sizeof(SPSettingsWin));
    if (res == NULL) {
        return NULL;
    }

    // Create an application window with the following settings:
    res->settingsWindow = SDL_CreateWindow("Chess Game - Settings", // window title
                                       SDL_WINDOWPOS_CENTERED,           // initial x position
                                       SDL_WINDOWPOS_CENTERED,           // initial y position
                                       800,                               // width, in pixels
                                       600,                               // height, in pixels
                                       SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (res->settingsWindow == NULL) {
        spSettingsWindowDestroy(res);
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL;
    }

    // Creating rederer and checking it's real
    res->settingsRenderer = SDL_CreateRenderer(res->settingsWindow, -1,
                                           SDL_RENDERER_ACCELERATED);
    if (res->settingsRenderer == NULL) {
        // In the case that the window could not be made...
        spSettingsWindowDestroy(res);
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL;
    }

    res->color = 1;
    res->diff = 2;
    res->numOfPlayers = 1;
    bool check;

    // Start button
    check = loadingSurfaceFunc(res, &(res->startTexture), "../GUI/images/settingsWindow/start.bmp");
    if (!check){ return  NULL; }

    // Back button
    check = loadingSurfaceFunc(res, &(res->backTexture), "../GUI/images/settingsWindow/back.bmp");
    if (!check){ return  NULL; }

    // Noob button
    check = loadingSurfaceFunc(res, &(res->noobTexture), "../GUI/images/settingsWindow/noob.bmp");
    if (!check){ return  NULL; }

    // Easy button
    check = loadingSurfaceFunc(res, &(res->easyTexture), "../GUI/images/settingsWindow/easy.bmp");
    if (!check){ return  NULL; }

    // moderate button
    check = loadingSurfaceFunc(res, &(res->moderateTexture), "../GUI/images/settingsWindow/moderate.bmp");
    if (!check){ return  NULL; }

    // Hard button
    check = loadingSurfaceFunc(res, &(res->hardTexture), "../GUI/images/settingsWindow/hard.bmp");
    if (!check){ return  NULL; }

    // White button
    check = loadingSurfaceFunc(res, &(res->whiteUserTexture), "../GUI/images/settingsWindow/white.bmp");
    if (!check){ return  NULL; }

    // Black button
    check = loadingSurfaceFunc(res, &(res->blackUserTexture), "../GUI/images/settingsWindow/black.bmp");
    if (!check){ return  NULL; }

    // onePlayer button
    check = loadingSurfaceFunc(res, &(res->onePlayerTexture), "../GUI/images/settingsWindow/onePlayer.bmp");
    if (!check){ return  NULL; }

    // twoPlayers button
    check = loadingSurfaceFunc(res, &(res->twoPlayersTexture), "../GUI/images/settingsWindow/twoPlayers.bmp");
    if (!check){ return  NULL; }


    // Bold Noob button
    check = loadingSurfaceFunc(res, &(res->noobBoldTexture), "../GUI/images/settingsWindow/noobBold.bmp");
    if (!check){ return  NULL; }

    // Bold Easy button
    check = loadingSurfaceFunc(res, &(res->easyBoldTexture), "../GUI/images/settingsWindow/easyBold.bmp");
    if (!check){ return  NULL; }

    // Bold moderate button
    check = loadingSurfaceFunc(res, &(res->moderateBoldTexture), "../GUI/images/settingsWindow/moderateBold.bmp");
    if (!check){ return  NULL; }

    // Bold Hard button
    check = loadingSurfaceFunc(res, &(res->hardBoldTexture), "../GUI/images/settingsWindow/hardBold.bmp");
    if (!check){ return  NULL; }

    // Bold White button
    check = loadingSurfaceFunc(res, &(res->whiteUserBoldTexture), "../GUI/images/settingsWindow/whiteBold.bmp");
    if (!check){ return  NULL; }

    // Bold Black button
    check = loadingSurfaceFunc(res, &(res->blackUserBoldTexture), "../GUI/images/settingsWindow/blackBold.bmp");
    if (!check){ return  NULL; }

    // Bold onePlayer button
    check = loadingSurfaceFunc(res, &(res->onePlayerBoldTexture), "../GUI/images/settingsWindow/onePlayerBold.bmp");
    if (!check){ return  NULL; }

    // Bold twoPlayers button
    check = loadingSurfaceFunc(res, &(res->twoPlayersBoldTexture), "../GUI/images/settingsWindow/twoPlayersBold.bmp");
    if (!check){ return  NULL; }

    // Num of players title
    check = loadingSurfaceFunc(res, &(res->numOfPlayersTitle), "../GUI/images/settingsWindow/gameMode.bmp");
    if (!check){ return  NULL; }

    // Difficulty title
    check = loadingSurfaceFunc(res, &(res->difficultyTitle), "../GUI/images/settingsWindow/difficulty.bmp");
    if (!check){ return  NULL; }

    // User color title
    check = loadingSurfaceFunc(res, &(res->userColorTitle), "../GUI/images/settingsWindow/userColor.bmp");
    if (!check){ return  NULL; }

    return res;
}


void spSettingsWindowDestroy(SPSettingsWin *src) {

    if (!src) { return; }

    if (src->startTexture != NULL) { SDL_DestroyTexture(src->startTexture); }
    if (src->backTexture != NULL) { SDL_DestroyTexture(src->backTexture); }
    if (src->whiteUserTexture != NULL) { SDL_DestroyTexture(src->whiteUserTexture); }
    if (src->whiteUserBoldTexture != NULL) { SDL_DestroyTexture(src->whiteUserBoldTexture); }
    if (src->blackUserTexture != NULL) { SDL_DestroyTexture(src->blackUserTexture); }
    if (src->blackUserBoldTexture != NULL) { SDL_DestroyTexture(src->blackUserBoldTexture); }
    if (src->onePlayerTexture != NULL) { SDL_DestroyTexture(src->onePlayerTexture); }
    if (src->onePlayerBoldTexture != NULL) { SDL_DestroyTexture(src->onePlayerBoldTexture); }
    if (src->twoPlayersTexture != NULL) { SDL_DestroyTexture(src->twoPlayersTexture); }
    if (src->twoPlayersBoldTexture != NULL) { SDL_DestroyTexture(src->twoPlayersBoldTexture); }
    if (src->noobTexture != NULL) { SDL_DestroyTexture(src->noobTexture); }
    if (src->noobBoldTexture != NULL) { SDL_DestroyTexture(src->noobBoldTexture); }
    if (src->easyTexture != NULL) { SDL_DestroyTexture(src->easyTexture); }
    if (src->easyBoldTexture != NULL) { SDL_DestroyTexture(src->easyBoldTexture); }
    if (src->moderateTexture != NULL) { SDL_DestroyTexture(src->moderateTexture); }
    if (src->moderateBoldTexture != NULL) { SDL_DestroyTexture(src->moderateBoldTexture); }
    if (src->hardTexture != NULL) { SDL_DestroyTexture(src->hardTexture); }
    if (src->hardBoldTexture != NULL) { SDL_DestroyTexture(src->hardBoldTexture); }

    if (src->numOfPlayersTitle != NULL) { SDL_DestroyTexture(src->hardBoldTexture); }
    if (src->difficultyTitle != NULL) { SDL_DestroyTexture(src->hardBoldTexture); }
    if (src->userColorTitle != NULL) { SDL_DestroyTexture(src->hardBoldTexture); }

    if (src->settingsRenderer != NULL) { SDL_DestroyRenderer(src->settingsRenderer); }
    if (src->settingsWindow != NULL) { SDL_DestroyWindow(src->settingsWindow); }
    free(src);
}


void spSettingsWindowDraw(SPSettingsWin *src) {
    if (src == NULL) {
        return;
    }
    src->gameModeR = (SDL_Rect){ .x = GAMEMODEX, .y = GAMEMODEY, .h = LABELS_H, .w = GAME_MODE_W};
    src->onePlayerR = (SDL_Rect){ .x = ONEPLAYERX, .y = GAMEMODEY, .h = BUTTONS_H, .w = ONE_PLAYER_W};
    src->twoPlayersR = (SDL_Rect){ .x = TWOPLAYERSX, .y = GAMEMODEY, .h = BUTTONS_H, .w = TWO_PLAYERS_W};

    src->userColorR = (SDL_Rect){.x = USERCOLORX, .y = USERCOLORY, .h = LABELS_H, .w = COLOR_W};
    src->whiteR = (SDL_Rect){.x = WHITEX, .y = USERCOLORY, .h = BUTTONS_H, .w = WHITE_BLACK_W};
    src->blackR = (SDL_Rect){.x = BLACKX, .y = USERCOLORY, .h = BUTTONS_H, .w = WHITE_BLACK_W};


    src->difficultyR = (SDL_Rect){.x = DIFFICULTYX, .y = DIFFICULTYY, .h = LABELS_H, .w = DIFFICULTY_W};
    src->noobR = (SDL_Rect){.x = NOOBX, .y = NOOB_EASY_MODERATE_HARD_Y, .h = BUTTONS_H, .w = NOOB_EASY_HARD_W};
    src->easyR = (SDL_Rect){.x = EASYX, .y = NOOB_EASY_MODERATE_HARD_Y, .h = BUTTONS_H, .w = NOOB_EASY_HARD_W};
    src->moderateR = (SDL_Rect){.x = MODERATEX, .y = NOOB_EASY_MODERATE_HARD_Y, .h = BUTTONS_H, .w = MODERATE_W};
    src->hardR = (SDL_Rect){ .x = HARDX, .y = NOOB_EASY_MODERATE_HARD_Y, .h = BUTTONS_H, .w = NOOB_EASY_HARD_W};

    src->startR = (SDL_Rect){.x = STARTX, .y = START_BACK_Y, .h = BUTTONS_H, .w = START_W};
    src->backR = (SDL_Rect){.x = BACKX, .y = START_BACK_Y, .h = BUTTONS_H, .w = BACK_W};

    SDL_SetRenderDrawColor(src->settingsRenderer, 134, 134, 134, 192);

    SDL_RenderClear(src->settingsRenderer);
    SDL_RenderCopy(src->settingsRenderer, src->numOfPlayersTitle, NULL, &src->gameModeR);
    SDL_RenderCopy(src->settingsRenderer, src->difficultyTitle, NULL, &src->difficultyR);
    SDL_RenderCopy(src->settingsRenderer, src->userColorTitle, NULL, &src->userColorR);
    SDL_RenderCopy(src->settingsRenderer, src->whiteUserBoldTexture, NULL, &src->whiteR);
    SDL_RenderCopy(src->settingsRenderer, src->blackUserTexture, NULL, &src->blackR);
    SDL_RenderCopy(src->settingsRenderer, src->startTexture, NULL, &src->startR);
    SDL_RenderCopy(src->settingsRenderer, src->backTexture, NULL, &src->backR);
    SDL_RenderCopy(src->settingsRenderer, src->onePlayerBoldTexture, NULL, &src->onePlayerR);
    SDL_RenderCopy(src->settingsRenderer, src->twoPlayersTexture, NULL, &src->twoPlayersR);
    SDL_RenderCopy(src->settingsRenderer, src->noobTexture, NULL, &src->noobR);
    SDL_RenderCopy(src->settingsRenderer, src->easyBoldTexture, NULL, &src->easyR);
    SDL_RenderCopy(src->settingsRenderer, src->moderateTexture, NULL, &src->moderateR);
    SDL_RenderCopy(src->settingsRenderer, src->hardTexture, NULL, &src->hardR);
    SDL_RenderPresent(src->settingsRenderer);
}

SP_SETTINGS_EVENT spSettingsWindowHandleEvent(SPSettingsWin *src, SDL_Event *event) {
    if (!event) {
        return SP_SETTINGS_INVALID_ARGUMENT;
    }
    switch (event->type) {
        case SDL_MOUSEBUTTONUP:
            if (isClickOnStart(event->button.x, event->button.y)) {
                return SP_SETTINGS_START;
            } else if (isClickOnBack(event->button.x, event->button.y)) {
                return SP_SETTINGS_BACK;
            } else if (isClickOnNoob(event->button.x, event->button.y) && src->numOfPlayers == 1) {
                SDL_RenderCopy(src->settingsRenderer, src->noobBoldTexture, NULL, &src->noobR);
                SDL_RenderCopy(src->settingsRenderer, src->easyTexture, NULL, &src->easyR);
                SDL_RenderCopy(src->settingsRenderer, src->moderateTexture, NULL, &src->moderateR);
                SDL_RenderCopy(src->settingsRenderer, src->hardTexture, NULL, &src->hardR);
                SDL_RenderPresent(src->settingsRenderer);
                return SP_SETTINGS_NOOB;
            } else if (isClickOnEasy(event->button.x, event->button.y) && src->numOfPlayers == 1) {
                SDL_RenderCopy(src->settingsRenderer, src->noobTexture, NULL, &src->noobR);
                SDL_RenderCopy(src->settingsRenderer, src->easyBoldTexture, NULL, &src->easyR);
                SDL_RenderCopy(src->settingsRenderer, src->moderateTexture, NULL, &src->moderateR);
                SDL_RenderCopy(src->settingsRenderer, src->hardTexture, NULL, &src->hardR);
                SDL_RenderPresent(src->settingsRenderer);
                return SP_SETTINGS_EASY;
            } else if (isClickOnModerate(event->button.x, event->button.y) && src->numOfPlayers == 1) {
                SDL_RenderCopy(src->settingsRenderer, src->noobTexture, NULL, &src->noobR);
                SDL_RenderCopy(src->settingsRenderer, src->easyTexture, NULL, &src->easyR);
                SDL_RenderCopy(src->settingsRenderer, src->moderateBoldTexture, NULL, &src->moderateR);
                SDL_RenderCopy(src->settingsRenderer, src->hardTexture, NULL, &src->hardR);
                SDL_RenderPresent(src->settingsRenderer);
                return SP_SETTINGS_MODERATE;
            } else if (isClickOnHard(event->button.x, event->button.y) && src->numOfPlayers == 1) {
                SDL_RenderCopy(src->settingsRenderer, src->noobTexture, NULL, &src->noobR);
                SDL_RenderCopy(src->settingsRenderer, src->easyTexture, NULL, &src->easyR);
                SDL_RenderCopy(src->settingsRenderer, src->moderateTexture, NULL, &src->moderateR);
                SDL_RenderCopy(src->settingsRenderer, src->hardBoldTexture, NULL, &src->hardR);
                SDL_RenderPresent(src->settingsRenderer);
                return SP_SETTINGS_HARD;
            } else if (isClickOnOnePlayer(event->button.x, event->button.y)  && src->numOfPlayers == 1) {
                SDL_RenderCopy(src->settingsRenderer, src->easyBoldTexture, NULL, &src->easyR);
                src->numOfPlayers = 1;
                SDL_RenderPresent(src->settingsRenderer);
                return SP_SETTINGS_ONE_PLAYER;
            } else if (isClickOnTwoPlayers(event->button.x, event->button.y)) {
                src->numOfPlayers = 2;
                SDL_RenderCopy(src->settingsRenderer, src->onePlayerTexture, NULL, &src->onePlayerR);
                SDL_RenderCopy(src->settingsRenderer, src->twoPlayersBoldTexture, NULL, &src->twoPlayersR);
                SDL_RenderCopy(src->settingsRenderer, src->whiteUserTexture, NULL, &src->whiteR);
                SDL_RenderCopy(src->settingsRenderer, src->blackUserTexture, NULL, &src->blackR);
                SDL_RenderCopy(src->settingsRenderer, src->noobTexture, NULL, &src->noobR);
                SDL_RenderCopy(src->settingsRenderer, src->easyTexture, NULL, &src->easyR);
                SDL_RenderCopy(src->settingsRenderer, src->moderateTexture, NULL, &src->moderateR);
                SDL_RenderCopy(src->settingsRenderer, src->hardTexture, NULL, &src->hardR);
                SDL_RenderPresent(src->settingsRenderer);
                return SP_SETTINGS_TWO_PLAYERS;
            } else if (isClickOnWhite(event->button.x, event->button.y) && src->numOfPlayers == 1) {
                SDL_RenderCopy(src->settingsRenderer, src->whiteUserBoldTexture, NULL, &src->whiteR);
                SDL_RenderCopy(src->settingsRenderer, src->blackUserTexture, NULL, &src->blackR);
                SDL_RenderPresent(src->settingsRenderer);
                return SP_SETTINGS_WHITE_USER;
            } else if (isClickOnBlack(event->button.x, event->button.y) && src->numOfPlayers == 1) {
                SDL_RenderCopy(src->settingsRenderer, src->whiteUserTexture, NULL, &src->whiteR);
                SDL_RenderCopy(src->settingsRenderer, src->blackUserBoldTexture, NULL, &src->blackR);
                SDL_RenderPresent(src->settingsRenderer);
                return SP_SETTINGS_BLACK_USER;
            }
            break;
        case SDL_WINDOWEVENT:
            if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
                return SP_SETTINGS_BACK;
            }
            break;
        default:
            return SP_SETTINGS_NONE;
    }
    return SP_SETTINGS_NONE;
}


void spSettingsWindowHide(SPSettingsWin *src) {
    SDL_HideWindow(src->settingsWindow);
}

void spSettingsWindowShow(SPSettingsWin *src) {
    SDL_ShowWindow(src->settingsWindow);
}
