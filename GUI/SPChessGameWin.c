
#include <stdio.h>
#include "SPChessGameWin.h"



int getClickColumn(int x) {
    if (x < ZERO_X || x > RIGHT_X){
        return -1;
    }
    else if (x >= ZERO_X && x < ONE_X){
        return 0;
    } else if (x >= ONE_X && x < TWO_X){
        return 1;
    } else if (x >= TWO_X && x < THREE_X){
        return 2;
    } else if (x >= THREE_X && x < FOUR_X){
        return 3;
    } else if (x >= FOUR_X && x < FIVE_X){
        return 4;
    } else if (x >= FIVE_X && x < SIX_X){
        return 5;
    } else if (x >= SIX_X && x < SEVEN_X){
        return 6;
    } else if (x >= SEVEN_X && x <= RIGHT_X) {
        return 7;
    }
    return -1;
}

int getClickRow(int y) {
    if (y > ZERO_Y || y < BOTTOM_Y){
        return -1;
    }
    else if (y <= ZERO_Y && y > ONE_Y){
        return 0;
    } else if (y <= ONE_Y && y > TWO_Y){
        return 1;
    } else if (y <= TWO_Y && y > THREE_Y){
        return 2;
    } else if (y <= THREE_Y && y > FOUR_Y){
        return 3;
    } else if (y <= FOUR_Y && y > FIVE_Y){
        return 4;
    } else if (y <= FIVE_Y && y > SIX_Y){
        return 5;
    } else if (y <= SIX_Y && y > SEVEN_Y){
        return 6;
    } else if (y <= SEVEN_Y && y >= BOTTOM_Y) {
        return 7;
    }
    return -1;
}

int isClickOnRestart(int x, int y) {
    if ((x >= GAME_BUTTONS_X && x <= GAME_BUTTONS_X + GAME_BUTTON_W) && (y >= RESTART_BUTTON_Y && y <= RESTART_BUTTON_Y + GAME_BUTTON_H)) {
        return 1;
    }
    return 0;
}


int isClickOnSave(int x, int y) {
    if ((x >= GAME_BUTTONS_X && x <= GAME_BUTTONS_X + GAME_BUTTON_W) && (y >= SAVE_BUTTON_Y && y <= SAVE_BUTTON_Y + GAME_BUTTON_H)) {
        return 1;
    }
    return 0;
}


int isClickOnLoad(int x, int y) {
    if ((x >= GAME_BUTTONS_X && x <= GAME_BUTTONS_X + GAME_BUTTON_W) && (y >= LOAD_BUTTON_Y && y <= LOAD_BUTTON_Y + GAME_BUTTON_H)) {
        return 1;
    }
    return 0;
}

int isClickOnUndo(int x, int y) {
    if ((x >= GAME_BUTTONS_X && x <= GAME_BUTTONS_X + GAME_BUTTON_W) && (y >= UNDO_BUTTON_Y && y <= UNDO_BUTTON_Y + GAME_BUTTON_H)) {
        return 1;
    }
    return 0;
}

int isClickOnMainMenu(int x, int y) {
    if ((x >= GAME_BUTTONS_X && x <= GAME_BUTTONS_X + GAME_BUTTON_W) && (y >= MAIN_MENU_BUTTON_Y && y <= MAIN_MENU_BUTTON_Y + GAME_BUTTON_H)) {
        return 1;
    }
    return 0;
}


int isClickOnQuit(int x, int y) {
    if ((x >= GAME_BUTTONS_X && x <= GAME_BUTTONS_X + GAME_BUTTON_W) && (y >= QUIT_BUTTON_Y && y <= QUIT_BUTTON_Y + GAME_BUTTON_H)) {
        return 1;
    }
    return 0;
}


bool loadingSurfaceFunc(SPGameWin *src, SDL_Texture** texture, char* path) {
    SDL_Surface *loadingSurface = NULL;
    loadingSurface = SDL_LoadBMP(path);
    if (loadingSurface == NULL) {
        spGameWindowDestroy(src);
        printf("couldn't create %s surface\n", path);
        SDL_FreeSurface(loadingSurface);
        return false;
    }
    *texture = SDL_CreateTextureFromSurface(src->gameRenderer, loadingSurface);
    if (*texture == NULL) {
        SDL_FreeSurface(loadingSurface);
        spGameWindowDestroy(src);
        printf("couldn't create %s texture\n", path);
        SDL_FreeSurface(loadingSurface);
        return false;
    }
    SDL_FreeSurface(loadingSurface);
    return true;
}

int createBoardTextures(SPGameWin* res){
    bool check;

    // board
    check = loadingSurfaceFunc(res, &(res->board), "../GUI/images/gameWindow/board.bmp");
    if (!check){ return 0; }

    // white king
    check = loadingSurfaceFunc(res, &(res->whiteKing), "../GUI/images/gameWindow/whiteKing.bmp");
    if (!check){ return 0; }

    // black king
    check = loadingSurfaceFunc(res, &(res->blackKing), "../GUI/images/gameWindow/blackKing.bmp");
    if (!check){ return 0; }

    // white queen
    check = loadingSurfaceFunc(res, &(res->whiteQueen), "../GUI/images/gameWindow/whiteQueen.bmp");
    if (!check){ return 0; }

    // black queen
    check = loadingSurfaceFunc(res, &(res->blackQueen), "../GUI/images/gameWindow/blackQueen.bmp");
    if (!check){ return 0; }

    // white bishop
    check = loadingSurfaceFunc(res, &(res->whiteBishop), "../GUI/images/gameWindow/whiteBishop.bmp");
    if (!check){ return 0; }

    // black bishop
    check = loadingSurfaceFunc(res, &(res->blackBishop), "../GUI/images/gameWindow/blackBishop.bmp");
    if (!check){ return 0; }

    // white knight
    check = loadingSurfaceFunc(res, &(res->whiteKnight), "../GUI/images/gameWindow/whiteKnight.bmp");
    if (!check){ return 0; }

    // black knight
    check = loadingSurfaceFunc(res, &(res->blackKnight), "../GUI/images/gameWindow/blackKnight.bmp");
    if (!check){ return 0; }

    // white rook
    check = loadingSurfaceFunc(res, &(res->whiteRook), "../GUI/images/gameWindow/whiteRook.bmp");
    if (!check){ return 0; }

    // black rook
    check = loadingSurfaceFunc(res, &(res->blackRook), "../GUI/images/gameWindow/blackRook.bmp");
    if (!check){ return 0; }

    // white pawn
    check = loadingSurfaceFunc(res, &(res->whitePawn), "../GUI/images/gameWindow/whitePawn.bmp");
    if (!check){ return 0; }

    // black pawn
    check = loadingSurfaceFunc(res, &(res->blackPawn), "../GUI/images/gameWindow/blackPawn.bmp");
    if (!check){ return 0; }

    return 1;
}


int createButtonsTextures(SPGameWin* res){
    bool check;

    // restart game
    check = loadingSurfaceFunc(res, &(res->restartGame), "../GUI/images/gameWindow/restartGame.bmp");
    if (!check){ return 0; }

    // save game
    check = loadingSurfaceFunc(res, &(res->saveGame), "../GUI/images/gameWindow/saveGame.bmp");
    if (!check){ return 0; }

    // save game - enabled
    check = loadingSurfaceFunc(res, &(res->saveGameEnabled), "../GUI/images/gameWindow/saveGameEnabled.bmp");
    if (!check){ return 0; }

    // load game
    check = loadingSurfaceFunc(res, &(res->loadGame), "../GUI/images/gameWindow/loadGame.bmp");
    if (!check){ return 0; }

    // undo move
    check = loadingSurfaceFunc(res, &(res->undoMove), "../GUI/images/gameWindow/undoMove.bmp");
    if (!check){ return 0; }

    // undo move - enabled
    check = loadingSurfaceFunc(res, &(res->undoMoveEnabled), "../GUI/images/gameWindow/undoMoveEnabled.bmp");
    if (!check){ return 0; }

    // main menu
    check = loadingSurfaceFunc(res, &(res->mainMenu), "../GUI/images/gameWindow/mainMenu.bmp");
    if (!check){ return 0; }

    // quit game
    check = loadingSurfaceFunc(res, &(res->quitGame), "../GUI/images/gameWindow/quitGame.bmp");
    if (!check){ return 0; }

    return 1;
}


SPGameWin* spGameWindowCreate() {
	SPGameWin* res =NULL;
    res = (SPGameWin*) malloc(sizeof(SPGameWin));
    if (res == NULL ) {
        printf("Couldn't create SPGameWin struct\n");
        return NULL ;
    }

    res->isTheGameSaved = 0;
    res->getMovesOn = 0;

	SDL_Surface* loadingSurface = NULL; //Used as temp surface

//	res->game = chessGameCreate();
//	if (res->game == NULL ) {
//		printf("Couldn't create game\n");
//		spGameWindowDestroy(res);
//		return NULL ;
//	}
	// Create an application window with the following settings:
	res->gameWindow = SDL_CreateWindow("Chess Game", // window title
			SDL_WINDOWPOS_CENTERED,           // initial x position
			SDL_WINDOWPOS_CENTERED,           // initial y position
			900,                               // width, in pixels
			600,                               // height, in pixels
			SDL_WINDOW_OPENGL                  // flags - see below
			);

	// Check that the window was successfully created
	if (res->gameWindow == NULL ) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	res->gameRenderer = SDL_CreateRenderer(res->gameWindow, -1, SDL_RENDERER_ACCELERATED);
	if (res->gameRenderer == NULL ) {
		printf("Could not create a renderer: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}

    int check = createBoardTextures(res);
    if (check == 0) { return NULL;}
    check = createButtonsTextures(res);
    if (check == 0) { return NULL;}

    SDL_FreeSurface(loadingSurface);
    return res;
}


void spGameWindowDestroyBoard(SPGameWin* src){
    if (src->board != NULL ) {
        SDL_DestroyTexture(src->board);
    }
    if (src->whiteKing != NULL ) {
        SDL_DestroyTexture(src->whiteKing);
    }
    if (src->blackKing != NULL ) {
        SDL_DestroyTexture(src->blackKing);
    }
    if (src->whiteQueen != NULL ) {
        SDL_DestroyRenderer(src->whiteQueen);
    }
    if (src->blackQueen != NULL ) {
        SDL_DestroyWindow(src->blackQueen);
    }
    if (src->whiteBishop != NULL ) {
        SDL_DestroyWindow(src->whiteBishop);
    }
    if (src->blackBishop != NULL ) {
        SDL_DestroyWindow(src->blackBishop);
    }
    if (src->whiteKnight != NULL ) {
        SDL_DestroyWindow(src->whiteKnight);
    }
    if (src->blackKnight != NULL ) {
        SDL_DestroyWindow(src->blackKnight);
    }
    if (src->whiteRook != NULL ) {
        SDL_DestroyWindow(src->whiteRook);
    }
    if (src->blackRook != NULL ) {
        SDL_DestroyWindow(src->blackRook);
    }
    if (src->whitePawn != NULL ) {
        SDL_DestroyWindow(src->whitePawn);
    }
    if (src->blackPawn != NULL ) {
        SDL_DestroyWindow(src->blackPawn);
    }
}

void spGameWindowDestroyButtons(SPGameWin* src){
    if (src->restartGame != NULL ) {
        SDL_DestroyTexture(src->restartGame);
    }
    if (src->saveGame != NULL ) {
        SDL_DestroyTexture(src->saveGame);
    }
    if (src->loadGame != NULL ) {
        SDL_DestroyTexture(src->loadGame);
    }
    if (src->undoMove != NULL ) {
        SDL_DestroyTexture(src->undoMove);
    }
    if (src->mainMenu != NULL ) {
        SDL_DestroyTexture(src->mainMenu);
    }
    if (src->quitGame != NULL ) {
        SDL_DestroyTexture(src->quitGame);
    }
}


void spGameWindowDestroy(SPGameWin* src) {
	if (!src) {
		return;
	}
    if (src->gameWindow != NULL ) {
        SDL_DestroyTexture(src->gameWindow);
    }
    if (src->gameRenderer != NULL ) {
        SDL_DestroyTexture(src->gameRenderer);
    }
    spGameWindowDestroyBoard(src);
    spGameWindowDestroyButtons(src);
	free(src);
}


void putTextureInRec(SPGameWin* src, SPChessGame* game, int i, int j, SDL_Rect* rec) {
    switch (game->gameBoard[i][j]){
        case BLANK:
            return;
        case KINGWHITE:
            SDL_RenderCopy(src->gameRenderer, src->whiteKing, NULL, rec);
        case KINGBLACK:
            SDL_RenderCopy(src->gameRenderer, src->blackKing, NULL, rec);
        case QUEENWHITE:
            SDL_RenderCopy(src->gameRenderer, src->whiteQueen, NULL, rec);
        case QUEENBLACK:
            SDL_RenderCopy(src->gameRenderer, src->blackQueen, NULL, rec);
        case BISHOPWHITE:
            SDL_RenderCopy(src->gameRenderer, src->whiteBishop, NULL, rec);
        case BISHOPBLACK:
            SDL_RenderCopy(src->gameRenderer, src->blackBishop, NULL, rec);
        case KNIGHTWHITE:
            SDL_RenderCopy(src->gameRenderer, src->whiteKnight, NULL, rec);
        case KNIGHTBLACK:
            SDL_RenderCopy(src->gameRenderer, src->blackKnight, NULL, rec);
        case ROOKWHITE:
            SDL_RenderCopy(src->gameRenderer, src->whiteRook, NULL, rec);
        case ROOKBLACK:
            SDL_RenderCopy(src->gameRenderer, src->blackRook, NULL, rec);
        case PAWNWHITE:
            SDL_RenderCopy(src->gameRenderer, src->whitePawn, NULL, rec);
        case PAWNBLACK:
            SDL_RenderCopy(src->gameRenderer, src->blackPawn, NULL, rec);
        default:
            return;
    }
}

void updateGameBoard(SPGameWin* src, SPChessGame* game){
    SDL_Rect rec = { .x = 42, .y = 42, .w = BOARD_W, .h = BOARD_W };
    int i = 0, j = 0;
    for (i = 0; i < GAMESIZE; i++) {
        for (j = 0; j < GAMESIZE; j++) {
            rec.x = 17 + j * PIECE_SIZE;
            rec.y = 18 + (GAMESIZE - 1 - i) * PIECE_SIZE;
            rec.w = PIECE_SIZE;
            rec.h = PIECE_SIZE;
            putTextureInRec(src, game, i, j, &rec);
        }
    }
}

void spGameWindowDrawBoard(SPGameWin* src, SPChessGame* game) {
	if(src == NULL || game == NULL){
		return;
	}
	SDL_Rect rec = { .x = 42, .y = 42, .w = BOARD_W, .h = BOARD_W };
	SDL_SetRenderDrawColor(src->gameRenderer, 134, 134, 134, 192);
	SDL_RenderClear(src->gameRenderer);
	SDL_RenderCopy(src->gameRenderer, src->board, NULL, &rec);

	updateGameBoard(src, game);

	SDL_RenderPresent(src->gameRenderer);
}


void spGameWindowDrawButtons(SPGameWin* src, SPChessGame* game){
    if(src == NULL || game == NULL){
        return;
    }
    SDL_SetRenderDrawColor(src->gameRenderer, 134, 134, 134, 192);
    SDL_RenderClear(src->gameRenderer);

    SDL_Rect restartRec = { .x = GAME_BUTTONS_X, .y = RESTART_BUTTON_Y, .w = GAME_BUTTON_W, .h = GAME_BUTTON_H };
    SDL_RenderCopy(src->gameRenderer, src->restartGame, NULL, &restartRec);

    SDL_Rect loadRec = { .x = GAME_BUTTONS_X, .y = LOAD_BUTTON_Y, .w = GAME_BUTTON_W, .h = GAME_BUTTON_H };
    SDL_RenderCopy(src->gameRenderer, src->loadGame, NULL, &loadRec);

    SDL_Rect saveRec = { .x = GAME_BUTTONS_X, .y = SAVE_BUTTON_Y, .w = GAME_BUTTON_W, .h = GAME_BUTTON_H };
    if (src->isTheGameSaved == 0) { SDL_RenderCopy(src->gameRenderer, src->saveGame, NULL, &saveRec); }
    else{ SDL_RenderCopy(src->gameRenderer, src->saveGameEnabled, NULL, &saveRec);}

    SDL_Rect undoRec = { .x = GAME_BUTTONS_X, .y = UNDO_BUTTON_Y, .w = GAME_BUTTON_W, .h = GAME_BUTTON_H };
    if (spArrayListIsEmpty(game->lastMoves)) { SDL_RenderCopy(src->gameRenderer, src->undoMoveEnabled, NULL, &undoRec); }
    else { SDL_RenderCopy(src->gameRenderer, src->undoMove, NULL, &undoRec); }


    SDL_Rect mainMenuRec = { .x = GAME_BUTTONS_X, .y = MAIN_MENU_BUTTON_Y, .w = GAME_BUTTON_W, .h = GAME_BUTTON_H };
    SDL_RenderCopy(src->gameRenderer, src->mainMenu, NULL, &mainMenuRec);

    SDL_Rect quitRec = { .x = GAME_BUTTONS_X, .y = QUIT_BUTTON_Y, .w = GAME_BUTTON_W, .h = GAME_BUTTON_H };
    SDL_RenderCopy(src->gameRenderer, src->quitGame, NULL, &quitRec);
}


void spGameWindowDraw(SPGameWin* src, SPChessGame* game){
    spGameWindowDrawBoard(src, game);
    spGameWindowDrawButtons(src, game);
}


SP_GAME_EVENT spGameWindowHandleBoardEvent(SPGameWin* src, SPChessGame* game, SDL_Event* event){           // TODO
    int eventX = event->button.x , eventY = event->button.y;
}


SP_GAME_EVENT spGameWindowHandleButtonsEvent(SPGameWin* src, SPChessGame* game, SDL_Event* event){         // TODO
    int eventX = event->button.x , eventY = event->button.y;
    if (isClickOnRestart(eventX, eventY)){

    } else if (isClickOnSave(eventX, eventY)){
    } else if (isClickOnLoad(eventX, eventY)){
    } else if (isClickOnUndo(eventX, eventY)){
    } else if (isClickOnSave(eventX, eventY)){
    } else if (isClickOnSave(eventX, eventY)){
    }
}



SP_GAME_EVENT spGameWindowHandleEvent(SPGameWin* src, SPChessGame* game, SDL_Event* event) {
    if (event == NULL || src == NULL ) {
        return SP_GAME_EVENT_INVALID_ARGUMENT;
    }
    switch (event->type) {
        case SDL_MOUSEBUTTONDOWN:
            if (event->button.x > RIGHT_X){ src->mouseDownEvent = NULL; }
            else if (event->button.x <= RIGHT_X && event->button.button == SDL_BUTTON_LEFT) { src->mouseDownEvent = event; }
//            else if (event->button.x <= RIGHT_X && event->button.button == SDL_BUTTON_RIGHT && game->difficulty <= 2) { src->mouseDownEvent = event; }
            return SP_GAME_EVENT_NONE;
        case SDL_MOUSEBUTTONUP:
            if (event->button.button == SDL_BUTTON_LEFT) {
                if (event->button.x > RIGHT_X && src->mouseDownEvent == NULL) {
                    return spGameWindowHandleButtonsEvent(src, game, event);
                } else if (event->button.x <= RIGHT_X && src->mouseDownEvent != NULL) {
                    return spGameWindowHandleBoardEvent(src, game, event);
                }
                else { return SP_GAME_EVENT_NONE; }
            }
            else if (event->button.button == SDL_BUTTON_RIGHT && event->button.x <= RIGHT_X && game->difficulty <= 2) {
                if (src->getMovesOn == 0){
                    src->getMovesOn = 1;
                }
                else{
                    src->getMovesOn = 0;
                }
            }
            else { return SP_GAME_EVENT_NONE; }
            break;
        case SDL_MOUSEMOTION:
        case SDL_WINDOWEVENT:
            if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
                return SP_GAME_EVENT_QUIT;
            }
            break;
        default:
            return SP_GAME_EVENT_NONE;
    }
    return SP_GAME_EVENT_NONE;
}

