//
// Created by 0mer on 26/09/2017.
//

#include "SPChessLoadWin.h"



int isClickOnOne(int x, int y) {
    if ((x >= ONEX && x <= ONEX + NUM_BUTTONS_W) && (y >= NUMY && y <= NUMY + NUM_BUTTONS_H)) {
        return 1;
    }
    return 0;
}

int isClickOnTwo(int x, int y) {
    if ((x >= TWOX && x <= TWOX + NUM_BUTTONS_W) && (y >= NUMY && y <= NUMY + NUM_BUTTONS_H)) {
        return 1;
    }
    return 0;
}

int isClickOnThree(int x, int y) {
    if ((x >= THREEX && x <= THREEX + NUM_BUTTONS_W) && (y >= NUMY && y <= NUMY + NUM_BUTTONS_H)) {
        return 1;
    }
    return 0;
}

int isClickOnFour(int x, int y) {
    if ((x >= FOURX && x <= FOURX + NUM_BUTTONS_W) && (y >= NUMY && y <= NUMY + NUM_BUTTONS_H)) {
        return 1;
    }
    return 0;
}

int isClickOnFive(int x, int y) {
    if ((x >= FIVEX && x <= FIVEX + NUM_BUTTONS_W) && (y >= NUMY && y <= NUMY + NUM_BUTTONS_H)) {
        return 1;
    }
    return 0;
}

int isClickOnLoadGame(int x, int y) {
    if ((x >= LOADX && x <= LOADX + LOAD_W) && (y >= LOAD_AND_BACK_Y && y <= LOAD_AND_BACK_Y + LOAD_H)) {
        return 1;
    }
    return 0;
}

int isClickOnBackInLoad(int x, int y) {
    if ((x >= LOAD_BACKX && x <= LOAD_BACKX + LOAD_AND_BACK_Y) && (y >= LOAD_AND_BACK_Y && y <= LOAD_AND_BACK_Y + LOAD_BACK_H)) {
        return 1;
    }
    return 0;
}





bool loadLoadingSurfaceFunc(SPLoadWin *src, SDL_Texture** texture, char* path) {
    SDL_Surface *loadingSurface = NULL;
    loadingSurface = SDL_LoadBMP(path);
    if (loadingSurface == NULL) {
        spLoadWindowDestroy(src);
        printf("couldn't create %s surface\n", path);
        SDL_FreeSurface(loadingSurface);
        return false;
    }
    *texture = SDL_CreateTextureFromSurface(src->loadRenderer, loadingSurface);
    if (*texture == NULL) {
        SDL_FreeSurface(loadingSurface);
        spLoadWindowDestroy(src);
        printf("couldn't create %s texture\n", path);
        SDL_FreeSurface(loadingSurface);
        return false;
    }
    SDL_FreeSurface(loadingSurface);
    return true;
}





SPLoadWin *spLoadWindowCreate(SP_LOAD_CALLER father) {
    SPLoadWin *res = NULL;
    res = (SPLoadWin *) malloc(sizeof(SPLoadWin));
    if (res == NULL) {
        return NULL;
    }

    // Create an application window with the following settings:
    res->loadWindow = SDL_CreateWindow("Chess Game - Load Game", // window title
                                           SDL_WINDOWPOS_CENTERED,           // initial x position
                                           SDL_WINDOWPOS_CENTERED,           // initial y position
                                           LOAD_WINDOW_W,                               // width, in pixels
                                           LOAD_WINDOW_H,                               // height, in pixels
                                           SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (res->loadWindow == NULL) {
        spLoadWindowDestroy(res);
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL;
    }

    // Creating rederer and checking it's real
    res->loadRenderer = SDL_CreateRenderer(res->loadWindow, -1,
                                               SDL_RENDERER_ACCELERATED);
    if (res->loadRenderer == NULL) {
        // In the case that the window could not be made...
        spLoadWindowDestroy(res);
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL;
    }

    res->caller = father;
    res->marked = 0;
    res->numOfSlots = (savedGameExists()) ? extractNumOfSavedGames() : 0;

    bool check;

    // Load Game button
    check = loadLoadingSurfaceFunc(res, &(res->loadGame), "../GUI/images/loadWindow/load.bmp");
    if (!check){ return  NULL; }

    // Back button
    check = loadLoadingSurfaceFunc(res, &(res->back), "../GUI/images/loadWindow/back.bmp");
    if (!check){ return  NULL; }

    // Load Game Title button
    check = loadLoadingSurfaceFunc(res, &(res->loadGameTitle), "../GUI/images/loadWindow/loadGame.bmp");
    if (!check){ return  NULL; }

    // 1 button
    check = loadLoadingSurfaceFunc(res, &(res->oneThin), "../GUI/images/loadWindow/one.bmp");
    if (!check){ return  NULL; }

    // 2 button
    check = loadLoadingSurfaceFunc(res, &(res->twoThin), "../GUI/images/loadWindow/two.bmp");
    if (!check){ return  NULL; }

    // 3 button
    check = loadLoadingSurfaceFunc(res, &(res->threeThin), "../GUI/images/loadWindow/three.bmp");
    if (!check){ return  NULL; }

    // 4 button
    check = loadLoadingSurfaceFunc(res, &(res->fourThin), "../GUI/images/loadWindow/four.bmp");
    if (!check){ return  NULL; }

    // 5 button
    check = loadLoadingSurfaceFunc(res, &(res->fiveThin), "../GUI/images/loadWindow/five.bmp");
    if (!check){ return  NULL; }

    // 1 Bold button
    check = loadLoadingSurfaceFunc(res, &(res->oneBold), "../GUI/images/loadWindow/oneBold.bmp");
    if (!check){ return  NULL; }

    // 2 Bold button
    check = loadLoadingSurfaceFunc(res, &(res->twoBold), "../GUI/images/loadWindow/twoBold.bmp");
    if (!check){ return  NULL; }

    // 3 Bold button
    check = loadLoadingSurfaceFunc(res, &(res->threeBold), "../GUI/images/loadWindow/threeBold.bmp");
    if (!check){ return  NULL; }


    // 4 Bold button
    check = loadLoadingSurfaceFunc(res, &(res->fourBold), "../GUI/images/loadWindow/fourBold.bmp");
    if (!check){ return  NULL; }

    // 5 Bold  button
    check = loadLoadingSurfaceFunc(res, &(res->fiveBold), "../GUI/images/loadWindow/fiveBold.bmp");
    if (!check){ return  NULL; }

    res->one = &(res->oneThin);
    res->two = &(res->twoThin);
    res->three = &(res->threeThin);
    res->four = &(res->fourThin);
    res->five = &(res->fiveThin);

    return res;
}


void spLoadWindowDestroy(SPLoadWin *src) {

    if (!src) { return; }

    if (src->oneThin != NULL) { SDL_DestroyTexture(src->oneThin); }
    if (src->oneBold != NULL) { SDL_DestroyTexture(src->oneBold); }
    if (src->twoThin != NULL) { SDL_DestroyTexture(src->twoThin); }
    if (src->twoBold != NULL) { SDL_DestroyTexture(src->twoBold); }
    if (src->threeThin != NULL) { SDL_DestroyTexture(src->threeThin); }
    if (src->threeBold != NULL) { SDL_DestroyTexture(src->threeBold); }
    if (src->fourThin != NULL) { SDL_DestroyTexture(src->fourThin); }
    if (src->fourBold != NULL) { SDL_DestroyTexture(src->fourBold); }
    if (src->fiveThin != NULL) { SDL_DestroyTexture(src->fiveThin); }
    if (src->fiveBold != NULL) { SDL_DestroyTexture(src->fiveBold); }

    if (src->loadGameTitle != NULL) { SDL_DestroyTexture(src->loadGameTitle); }
    if (src->loadGame != NULL) { SDL_DestroyTexture(src->loadGame); }
    if (src->back != NULL) { SDL_DestroyTexture(src->back); }

    if (src->loadRenderer != NULL) { SDL_DestroyRenderer(src->loadRenderer); }
    if (src->loadWindow != NULL) { SDL_DestroyWindow(src->loadWindow); }

    free(src);
}


void spLoadWindowDraw(SPLoadWin *src) {
    if (src == NULL) {
        return;
    }
    SDL_Rect oneR = { .x = ONEX, .y = NUMY, .h = NUM_BUTTONS_H, .w = NUM_BUTTONS_W};
    SDL_Rect twoR = { .x = TWOX, .y = NUMY, .h = NUM_BUTTONS_H, .w = NUM_BUTTONS_W};
    SDL_Rect threeR = { .x = THREEX, .y = NUMY, .h = NUM_BUTTONS_H, .w = NUM_BUTTONS_W};
    SDL_Rect fourR = {.x = FOURX, .y = NUMY, .h = NUM_BUTTONS_H, .w = NUM_BUTTONS_W};
    SDL_Rect fiveR = {.x = FIVEX, .y = NUMY, .h = NUM_BUTTONS_H, .w = NUM_BUTTONS_W};

    SDL_Rect loadR = {.x = LOADX, .y = LOAD_AND_BACK_Y, .h = LOAD_H, .w = LOAD_W};
    SDL_Rect backR = {.x = LOAD_BACKX, .y = LOAD_AND_BACK_Y, .h = LOAD_BACK_H, .w = LOAD_BACK_W};
    SDL_Rect titleR = {.x = LABALX, .y = LABELY, .h = LABEL_H, .w = LABEL_W};


    SDL_SetRenderDrawColor(src->loadRenderer, 134, 134, 134, 192);

    SDL_RenderClear(src->loadRenderer);
    SDL_RenderCopy(src->loadRenderer, src->loadGameTitle, NULL, &titleR);
    SDL_RenderCopy(src->loadRenderer, src->loadGame, NULL, &loadR);
    SDL_RenderCopy(src->loadRenderer, src->back, NULL, &backR);
    SDL_RenderCopy(src->loadRenderer, *(src->one), NULL, &oneR);
    SDL_RenderCopy(src->loadRenderer, *(src->two), NULL, &twoR);
    SDL_RenderCopy(src->loadRenderer, *(src->three), NULL, &threeR);
    SDL_RenderCopy(src->loadRenderer, *(src->four), NULL, &fourR);
    SDL_RenderCopy(src->loadRenderer, *(src->five), NULL, &fiveR);

    SDL_RenderPresent(src->loadRenderer);
}





SP_LOAD_EVENT spLoadWindowHandleEvent(SPLoadWin *src, SDL_Event *event) {
    if (!event) {
        return SP_LOAD_INVALID_ARGUMENT;
    }
    switch (event->type) {
        case SDL_MOUSEBUTTONUP:
            if (isClickOnOne(event->button.x, event->button.y) && src->numOfSlots > 0) {
                src->one = &(src->oneBold);
                src->two = &(src->twoThin);
                src->three = &(src->threeThin);
                src->four = &(src->fourThin);
                src->five = &(src->fiveThin);
                src->marked = 1;
                return SP_LOAD_NONE;
            } else if (isClickOnTwo(event->button.x, event->button.y) && src->numOfSlots > 1) {
                src->one = &(src->oneThin);
                src->two = &(src->twoBold);
                src->three = &(src->threeThin);
                src->four = &(src->fourThin);
                src->five = &(src->fiveThin);
                src->marked = 2;
                return SP_LOAD_NONE;
            } else if (isClickOnThree(event->button.x, event->button.y) && src->numOfSlots > 2) {
                src->one = &(src->oneThin);
                src->two = &(src->twoThin);
                src->three = &(src->threeBold);
                src->four = &(src->fourThin);
                src->five = &(src->fiveThin);
                src->marked = 3;
                return SP_LOAD_NONE;
            } else if (isClickOnFour(event->button.x, event->button.y) && src->numOfSlots > 3) {
                src->one = &(src->oneThin);
                src->two = &(src->twoThin);
                src->three = &(src->threeThin);
                src->four = &(src->fourBold);
                src->five = &(src->fiveThin);
                src->marked = 4;
                return SP_LOAD_NONE;
            } else if (isClickOnFive(event->button.x, event->button.y) && src->numOfSlots > 4) {
                src->one = &(src->oneThin);
                src->two = &(src->twoThin);
                src->three = &(src->threeThin);
                src->four = &(src->fourThin);
                src->five = &(src->fiveBold);
                src->marked = 5;
                return SP_LOAD_NONE;
            } else if (isClickOnLoadGame(event->button.x, event->button.y) && src->marked > 0) {
                switch (src->marked) {
                    case 1:
                        return SP_LOAD_1;
                    case 2:
                        return SP_LOAD_2;
                    case 3:
                        return SP_LOAD_3;
                    case 4:
                        return SP_LOAD_4;
                    case 5:
                        return SP_LOAD_5;
                    default:
                        return SP_LOAD_NONE;
                }
            } else if (isClickOnBackInLoad(event->button.x, event->button.y)) {
                if (src->caller == GAME_CALLER){
                    return SP_LOAD_BACK_GAME;
                }
                return SP_LOAD_BACK_MAIN;
            }
            break;
        case SDL_WINDOWEVENT:
            if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
                return SP_LOAD_BACK_MAIN;
            }
            break;
        default:
            return SP_LOAD_NONE;
    }
    return SP_LOAD_NONE;
}


void spLoadWindowHide(SPLoadWin *src) {
    SDL_HideWindow(src->loadWindow);
}

void spLoadWindowShow(SPLoadWin *src) {
    SDL_ShowWindow(src->loadWindow);
}
