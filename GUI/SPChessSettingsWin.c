//
// Created by אורי חביב on 24/09/2017.
//

#include <stdbool.h>
#include "SPChessSettingsWin.h"

//Inner functions
//int isClickOnNew(int x, int y) {
//    if ((x >= 75 && x <= 325) && (y >= 180 && y <= 230)) {
//        return 1;
//    }
//    return 0;
//}
//
//int isClickOnLoad(int x, int y) {
//    if ((x >= 75 && x <= 325) && (y >= 245 && y <= 295)) {
//        return 1;
//    }
//    return 0;
//}
//
//int isClickOnQuit(int x, int y) {
//    if ((x >= 75 && x <= 325) && (y >= 310 && y <= 360)) {
//        return 1;
//    }
//    return 0;
//}


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





SPSettingsWin *spMainWindowCreate() {
    SPSettingsWin *res = NULL;
    res = (SPSettingsWin *) malloc(sizeof(SPSettingsWin));
    if (res == NULL) {
        return NULL;
    }

    // Create an application window with the following settings:
    res->settingsWindow = SDL_CreateWindow("Chess Game - Settings", // window title
                                       SDL_WINDOWPOS_CENTERED,           // initial x position
                                       SDL_WINDOWPOS_CENTERED,           // initial y position
                                       600,                               // width, in pixels
                                       400,                               // height, in pixels
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


void spMainWindowDraw(SPSettingsWin *src) {
    if (src == NULL) {
        return;
    }
    SDL_Rect gameModeR = {.x = 75, .y = 10, .h = 200, .w = 200};
    SDL_Rect difficultyR = {.x = 75, .y = 10, .h = 200, .w = 200};
    SDL_Rect userColorR = {.x = 75, .y = 10, .h = 200, .w = 200};
    SDL_Rect whiteR = {.x = 75, .y = 10, .h = 200, .w = 200};
    SDL_Rect blackR = {.x = 75, .y = 10, .h = 200, .w = 200};
    SDL_Rect startR = {.x = 75, .y = 180, .h = 50, .w = 250};
    SDL_Rect backR = {.x = 75, .y = 245, .h = 50, .w = 250};
    SDL_Rect onePlayerR = {.x = 75, .y = 310, .h = 50, .w = 250};
    SDL_Rect twoPlayersR = {.x = 75, .y = 310, .h = 50, .w = 250};
    SDL_Rect noobR = {.x = 75, .y = 310, .h = 50, .w = 250};
    SDL_Rect easyR = {.x = 75, .y = 310, .h = 50, .w = 250};
    SDL_Rect moderateR = {.x = 75, .y = 310, .h = 50, .w = 250};
    SDL_Rect hardR = {.x = 75, .y = 310, .h = 50, .w = 250};

    SDL_SetRenderDrawColor(src->settingsRenderer, 134, 134, 134, 0);


    SDL_RenderClear(src->settingsRenderer);
    SDL_RenderCopy(src->settingsRenderer, src->numOfPlayersTitle, NULL, &gameModeR);
    SDL_RenderCopy(src->settingsRenderer, src->difficultyTitle, NULL, &difficultyR);
    SDL_RenderCopy(src->settingsRenderer, src->userColorTitle, NULL, &userColorR);
    SDL_RenderCopy(src->settingsRenderer, src->whiteUserBoldTexture, NULL, &whiteR);
    SDL_RenderCopy(src->settingsRenderer, src->blackUserTexture, NULL, &blackR);
    SDL_RenderCopy(src->settingsRenderer, src->startTexture, NULL, &startR);
    SDL_RenderCopy(src->settingsRenderer, src->backTexture, NULL, &backR);
    SDL_RenderCopy(src->settingsRenderer, src->onePlayerBoldTexture, NULL, &onePlayerR);
    SDL_RenderCopy(src->settingsRenderer, src->twoPlayersTexture, NULL, &twoPlayersR);
    SDL_RenderCopy(src->settingsRenderer, src->noobTexture, NULL, &noobR);
    SDL_RenderCopy(src->settingsRenderer, src->easyBoldTexture, NULL, &easyR);
    SDL_RenderCopy(src->settingsRenderer, src->moderateTexture, NULL, &moderateR);
    SDL_RenderCopy(src->settingsRenderer, src->hardTexture, NULL, &hardR);
    SDL_RenderPresent(src->settingsRenderer);
}

//SP_MAIN_EVENT spMainWindowHandleEvent(SPMainWin *src, SDL_Event *event) {
//    if (!event) {
//        return SP_MAIN_INVALID_ARGUMENT;
//    }
//    switch (event->type) {
//        case SDL_MOUSEBUTTONUP:
//            if (isClickOnNew(event->button.x, event->button.y)) {
//                return SP_MAIN_NEW_GAME;
//            } else if (isClickOnQuit(event->button.x, event->button.y)) {
//                return SP_MAIN_QUIT_GAME;
//            } else if (isClickOnLoad(event->button.x, event->button.y)) {
//                return SP_MAIN_LOAD_GAME;
//            }
//            break;
//        case SDL_WINDOWEVENT:
//            if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
//                return SP_MAIN_QUIT_GAME;
//            }
//            break;
//        default:
//            return SP_MAIN_NONE;
//    }
//    return SP_MAIN_NONE;
//}


void spSettingsWindowHide(SPSettingsWin *src) {
    SDL_HideWindow(src->settingsWindow);
}

void spSettingsWindowShow(SPSettingsWin *src) {
    SDL_ShowWindow(src->settingsWindow);
}
