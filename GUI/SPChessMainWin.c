 #include "SPChessMainWin.h"


//Inner functions
int isClickOnNew(int x, int y) {
    if ((x >= 75 && x <= 325) && (y >= 180 && y <= 230)) {
        return 1;
    }
    return 0;
}

int isClickOnLoad(int x, int y) {
    if ((x >= 75 && x <= 325) && (y >= 245 && y <= 295)) {
        return 1;
    }
    return 0;
}

int isClickOnQuit(int x, int y) {
    if ((x >= 75 && x <= 325) && (y >= 310 && y <= 360)) {
        return 1;
    }
    return 0;
}



bool loadingSurfaceFunc(SPMainWin *src, SDL_Texture** texture, char* path) {
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
                                       400,                               // width, in pixels
                                       400,                               // height, in pixels
                                       SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (res->mainWindow == NULL) {
        spMainWindowDestroy(res);
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL;
    }

    bool check;


    // Creating renderer and checking it's real
    res->mainRenderer = SDL_CreateRenderer(res->mainWindow, -1,
                                           SDL_RENDERER_ACCELERATED);
    if (res->mainRenderer == NULL) {
        // In the case that the window could not be made...
        spMainWindowDestroy(res);
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL;
    }

    // picture
    check = loadingSurfaceFunc(res, &(res->pictureTexture), "../GUI/images/mainWindow/dragon.bmp");
    if (!check){ return  NULL; }

    // New Game button
    check = loadingSurfaceFunc(res, &(res->newGameTexture), "../GUI/images/mainWindow/newGame.bmp");
    if (!check){ return  NULL; }


    // Load Game button
    check = loadingSurfaceFunc(res, &(res->loadGameTexture), "../GUI/images/mainWindow/loadGame.bmp");
    if (!check){ return  NULL; }


    // Quit Game button
    check = loadingSurfaceFunc(res, &(res->quitGameTexture), "../GUI/images/mainWindow/quitGame.bmp");
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
    SDL_Rect pictureR = {.x = 75, .y = 10, .h = 200, .w = 200};
    SDL_Rect newR = {.x = 75, .y = 180, .h = 50, .w = 250};
    SDL_Rect loadR = {.x = 75, .y = 245, .h = 50, .w = 250};
    SDL_Rect quitR = {.x = 75, .y = 310, .h = 50, .w = 250};
    SDL_SetRenderDrawColor(src->mainRenderer, 134, 134, 134, 0);
    SDL_RenderClear(src->mainRenderer);
    SDL_RenderCopy(src->mainRenderer, src->pictureTexture, NULL, &pictureR);
    SDL_RenderCopy(src->mainRenderer, src->newGameTexture, NULL, &newR);
    SDL_RenderCopy(src->mainRenderer, src->loadGameTexture, NULL, &loadR);
    SDL_RenderCopy(src->mainRenderer, src->quitGameTexture, NULL, &quitR);
    SDL_RenderPresent(src->mainRenderer);
}

SP_MAIN_EVENT spMainWindowHandleEvent(SPMainWin *src, SDL_Event *event) {
    if (!event) {
        return SP_MAIN_INVALID_ARGUMENT;
    }
    switch (event->type) {
        case SDL_MOUSEBUTTONUP:
            if (isClickOnNew(event->button.x, event->button.y)) {
                return SP_MAIN_NEW_GAME;
            } else if (isClickOnQuit(event->button.x, event->button.y)) {
                return SP_MAIN_QUIT_GAME;
            } else if (isClickOnLoad(event->button.x, event->button.y)) {
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
