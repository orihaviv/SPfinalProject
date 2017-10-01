//
// Created by Omer Koren & Ori Haviv 2017
//

#include "SPChessMainWin.h"



int isClickOnNew(int x, int y) {
// Indicates whether a click was on the "New Game" button

    if ((x >= OBJECTS_X && x <= BUTTONS_W + OBJECTS_X) && (y >= NEW_Y && y <= NEW_Y + BUTTONS_H)) {
        return 1;
    }
    return 0;
}

int isClickOnLoadInMain(int x, int y) {
// Indicates whether a click was on the "Load Game" button

    if ((x >= OBJECTS_X && x <= BUTTONS_W + OBJECTS_X) && (y >= LOAD_Y && y <= LOAD_Y + BUTTONS_H)) {
        return 1;
    }
    return 0;
}

int isClickOnQuitInMain(int x, int y) {
// Indicates whether a click was on the "Quit Game" button

    if ((x >= OBJECTS_X && x <= BUTTONS_W + OBJECTS_X) && (y >= QUIT_Y && y <= QUIT_Y + BUTTONS_H)) {
        return 1;
    }
    return 0;
}



bool mainLoadingSurfaceFunc(SPMainWin *src, SDL_Texture** texture, char* path) {
// Loading a surface into the given texture from the given path

    SDL_Surface *loadingSurface = NULL;
    loadingSurface = SDL_LoadBMP(path);
    if (loadingSurface == NULL) {
        spMainWindowDestroy(src);
        printf("couldn't create %s surface\n", path);
        SDL_FreeSurface(loadingSurface);
        return false;
    }
    *texture = SDL_CreateTextureFromSurface(src->mainRenderer, loadingSurface);
    if (*texture == NULL) {
        SDL_FreeSurface(loadingSurface);
        spMainWindowDestroy(src);
        printf("couldn't create %s texture\n", path);
        SDL_FreeSurface(loadingSurface);
        return false;
    }
    SDL_FreeSurface(loadingSurface);
    return true;
}




SPMainWin *spMainWindowCreate() {
    SPMainWin *res = NULL;
    SDL_Surface *loadingSurface = NULL;
    res = (SPMainWin *) malloc(sizeof(SPMainWin));
    if (res == NULL) {
        return NULL;
    }

    // Create an application window with the following settings:
    res->mainWindow = SDL_CreateWindow("Chess Game - Main Menu", // window title
                                       SDL_WINDOWPOS_CENTERED,           // initial x position
                                       SDL_WINDOWPOS_CENTERED,           // initial y position
                                       MAIN_WINDOW_W,                               // width, in pixels
                                       MAIN_WINDOW_H,                               // height, in pixels
                                       SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (res->mainWindow == NULL) {
        spMainWindowDestroy(res);
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL;
    }

    bool check;


    // Creating rederer and checking it's real
    res->mainRenderer = SDL_CreateRenderer(res->mainWindow, -1,
                                           SDL_RENDERER_ACCELERATED);
    if (res->mainRenderer == NULL) {
        // In the case that the window could not be made...
        spMainWindowDestroy(res);
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL;
    }

    // picture
    check = mainLoadingSurfaceFunc(res, &(res->pictureTexture), "../GUI/images/mainWindow/dragon.bmp");
    if (!check){ return  NULL; }

    // New Game button
    check = mainLoadingSurfaceFunc(res, &(res->newGameTexture), "../GUI/images/mainWindow/newGame.bmp");
    if (!check){ return  NULL; }


    // Load Game button
    check = mainLoadingSurfaceFunc(res, &(res->loadGameTexture), "../GUI/images/mainWindow/loadGame.bmp");
    if (!check){ return  NULL; }


    // Quit Game button
    check = mainLoadingSurfaceFunc(res, &(res->quitGameTexture), "../GUI/images/mainWindow/quitGame.bmp");
    if (!check){ return  NULL; }


    SDL_FreeSurface(loadingSurface);
    return res;
}


void spMainWindowDestroy(SPMainWin *src) {
    if (!src) {
        return;
    }
    if (src->newGameTexture != NULL) {
        SDL_DestroyTexture(src->newGameTexture);
    }
    if (src->loadGameTexture != NULL) {
        SDL_DestroyTexture(src->loadGameTexture);
    }
    if (src->quitGameTexture != NULL) {
        SDL_DestroyTexture(src->quitGameTexture);
    }
    if (src->mainRenderer != NULL) {
        SDL_DestroyRenderer(src->mainRenderer);
    }
    if (src->mainWindow != NULL) {
        SDL_DestroyWindow(src->mainWindow);
    }
    free(src);
}


void spMainWindowDraw(SPMainWin *src) {
    if (src == NULL) {
        return;
    }
    SDL_Rect pictureR = {.x = OBJECTS_X, .y = PIC_Y, .h = PICTURE_W_H, .w = PICTURE_W_H};
    SDL_Rect newR = {.x = OBJECTS_X, .y = NEW_Y, .h = BUTTONS_H, .w = BUTTONS_W};
    SDL_Rect loadR = {.x = OBJECTS_X, .y = LOAD_Y, .h = BUTTONS_H, .w = BUTTONS_W};
    SDL_Rect quitR = {.x = OBJECTS_X, .y = QUIT_Y, .h = BUTTONS_H, .w = BUTTONS_W};
    SDL_SetRenderDrawColor(src->mainRenderer, 134, 134, 134, BUTTONS_W);
    SDL_RenderClear(src->mainRenderer);
    SDL_RenderCopy(src->mainRenderer, src->pictureTexture, NULL, &pictureR);
    SDL_RenderCopy(src->mainRenderer, src->newGameTexture, NULL, &newR);
    SDL_RenderCopy(src->mainRenderer, src->loadGameTexture, NULL, &loadR);
    SDL_RenderCopy(src->mainRenderer, src->quitGameTexture, NULL, &quitR);
    SDL_RenderPresent(src->mainRenderer);
}

SP_MAIN_EVENT spMainWindowHandleEvent(SDL_Event *event) {
    if (!event) {
        return SP_MAIN_INVALID_ARGUMENT;
    }
    switch (event->type) {
        case SDL_MOUSEBUTTONUP:
            if (isClickOnNew(event->button.x, event->button.y)) {
                return SP_MAIN_NEW_GAME;
            } else if (isClickOnQuitInMain(event->button.x, event->button.y)) {
                return SP_MAIN_QUIT_GAME;
            } else if (isClickOnLoadInMain(event->button.x, event->button.y)) {
                return SP_MAIN_LOAD_GAME;
            }
            break;
        case SDL_WINDOWEVENT:
            if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
                return SP_MAIN_QUIT_GAME;
            }
            break;
        default:
            return SP_MAIN_NONE;
    }
    return SP_MAIN_NONE;
}


void spMainWindowHide(SPMainWin *src) {
    SDL_HideWindow(src->mainWindow);
}

void spMainWindowShow(SPMainWin *src) {
    SDL_ShowWindow(src->mainWindow);
}
