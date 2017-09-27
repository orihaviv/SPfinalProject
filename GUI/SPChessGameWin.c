
#include <stdio.h>
#include "SPChessGameWin.h"



int getClickColumn(int x) {
    /* Returns the click's relevant column on the board */

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
    /* Returns the click's relevant row on the board */

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
    /* Indicates whether a click was on the "Restart Game" button */

    if ((x >= GAME_BUTTONS_X && x <= GAME_BUTTONS_X + GAME_BUTTON_W) && (y >= RESTART_BUTTON_Y && y <= RESTART_BUTTON_Y + GAME_BUTTON_H)) {
        return 1;
    }
    return 0;
}


int isClickOnSave(int x, int y) {
    /* Indicates whether a click was on the "Save Game" button */

    if ((x >= GAME_BUTTONS_X && x <= GAME_BUTTONS_X + GAME_BUTTON_W) && (y >= SAVE_BUTTON_Y && y <= SAVE_BUTTON_Y + GAME_BUTTON_H)) {
        return 1;
    }
    return 0;
}


int isClickOnLoad(int x, int y) {
    /* Indicates whether a click was on the "Load Game" button */

    if ((x >= GAME_BUTTONS_X && x <= GAME_BUTTONS_X + GAME_BUTTON_W) && (y >= LOAD_BUTTON_Y && y <= LOAD_BUTTON_Y + GAME_BUTTON_H)) {
        return 1;
    }
    return 0;
}

int isClickOnUndo(int x, int y) {
    /* Indicates whether a click was on the "Undo Move" button */

    if ((x >= GAME_BUTTONS_X && x <= GAME_BUTTONS_X + GAME_BUTTON_W) && (y >= UNDO_BUTTON_Y && y <= UNDO_BUTTON_Y + GAME_BUTTON_H)) {
        return 1;
    }
    return 0;
}

int isClickOnMainMenu(int x, int y) {
    /* Indicates whether a click was on the "Main Menu" button */

    if ((x >= GAME_BUTTONS_X && x <= GAME_BUTTONS_X + GAME_BUTTON_W) && (y >= MAIN_MENU_BUTTON_Y && y <= MAIN_MENU_BUTTON_Y + GAME_BUTTON_H)) {
        return 1;
    }
    return 0;
}


int isClickOnQuit(int x, int y) {
    /* Indicates whether a click was on the "Quit Game" button */

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

    // yellow square
    check =loadingSurfaceFunc(res , &(res->yellow), "../GUI/images/gameWindow/yellow.bmp");
    if (!check){ return 0; }

    // red square
    check =loadingSurfaceFunc(res , &(res->red), "../GUI/images/gameWindow/red.bmp");
    if (!check){ return 0; }

    // green square
    check =loadingSurfaceFunc(res , &(res->green), "../GUI/images/gameWindow/green.bmp");
    if (!check){ return 0; }

    // purple square
    check =loadingSurfaceFunc(res , &(res->purple), "../GUI/images/gameWindow/purple.bmp");
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
    /* Destroys board */

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
    /* Destroys buttons */

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
    /* Draws a specific piece in a spacific rectangle on the board */

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
    /* Draws the relevant pieces over the board */

    SDL_Rect rec = { .x = 59, .y = 60, .w = BOARD_W, .h = BOARD_W };
    int i = 0, j = 0;
    for (i = 0; i < GAMESIZE; i++) {
        for (j = 0; j < GAMESIZE; j++) {
            rec.x = 59 + j * PIECE_SIZE;
            rec.y = 60 + (GAMESIZE - 1 - i) * PIECE_SIZE;
            rec.w = PIECE_SIZE;
            rec.h = PIECE_SIZE;
            putTextureInRec(src, game, i, j, &rec);
        }
    }
}


void spGameWindowDrawBoard(SPGameWin* src, SPChessGame* game) {
    /* Draws the board's side */

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
    /* Draws the buttons' side */

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
    if (spArrayListIsEmpty(game->lastMoves) || game->gameMode == 2) { SDL_RenderCopy(src->gameRenderer, src->undoMoveEnabled, NULL, &undoRec); }
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

void resetGetMoves(SPGameWin* src, SPChessGame* game){
    /* Restoring the game board - no highlights */

    SDL_Rect rec = { .x = 42, .y = 42, .w = BOARD_W, .h = BOARD_W };
    int i = 0, j = 0;
    for (i = 0; i < GAMESIZE; i++) {
        for (j = 0; j < GAMESIZE; j++) {
            rec.x = 17 + j * PIECE_SIZE;
            rec.y = 18 + (GAMESIZE - 1 - i) * PIECE_SIZE;
            rec.w = PIECE_SIZE;
            rec.h = PIECE_SIZE;
            SDL_RenderCopy(src->gameRenderer, NULL, NULL, rec);
        }
    }
    updateGameBoard(src, game);
}


void spGameWindowDeactivateGetMoves(SPGameWin* src, SPChessGame* game){
    /* Deactivate get_moves highlights */

    if (src->getMovesOn == 1){
        src->getMovesOn = 0;
        resetGetMoves(src, game);
    }
}


int spGameWindowActivateGetMoves(SPGameWin* src, SPChessGame* game, SDL_Event* event){
    /* Handles "get_moves" events */

    int eventX = getClickColumn(event->button.x) , eventY = getClickRow(event->button.y) , i , row , col;
    if (eventX < 0 || eventY < 0){ return 0; }
    if (game->userColor == 0 && !isBlack(game->gameBoard[eventY][eventX])){ return 0; }
    if (game->userColor == 1 && !isWhite(game->gameBoard[eventY][eventX])){ return 0; }

    SPArrayList *possibleMoves = getMovesForSoldier(game, eventY, eventX);
    action move;
    SDL_Rect rec;

    for (i = 0 ; i < possibleMoves->actualSize ; i++){
        move = *(spArrayListGetAt(possibleActions, i));
        row = move.current.row;
        col = move.current.column;
        rec.x = 59 + (col) * PIECE_SIZE;
        rec.y = 60 + (GAMESIZE - 1 - row) * PIECE_SIZE;
        rec.w = PIECE_SIZE;
        rec.h = PIECE_SIZE;
        if (move.castling == SP_CHESS_NO_CASTLING){
            SDL_RenderCopy(src->gameRenderer, src->yellow, NULL, rec);
            if (move.captured != BLANK) { SDL_RenderCopy(src->gameRenderer, src->green, NULL, rec); }
            if (isTheSoldierThreatened(game, game->currentPlayer, move.current)){
                SDL_RenderCopy(src->gameRenderer, src->red, NULL, rec);
            }
        }
        else{
            SDL_RenderCopy(src->gameRenderer, src->purple, NULL, rec);
        }
    }
    return 1;
}


SP_GAME_EVENT spGameWindowHandleBoardEvent(SPGameWin* src, SPChessGame* game, SDL_Event* event){
    /* Handles events on the board's side */

    int originCol = getClickColumn(src->mouseDownEvent->button.x) , originRow = getClickRow(src->mouseDownEvent->button.y);
    src->mouseDownEvent = NULL;
    int destCol = getClickColumn(event->button.x) , destRow = getClickRow(event->button.y);

    if (originCol < 0 || originRow < 0 || destCol < 0 || originRow < 0) { return SP_GAME_EVENT_NONE; }
    if (game->userColor == 0 && !isBlack(game->gameBoard[originRow][originCol])) { return SP_GAME_EVENT_NONE; }
    if (game->userColor == 1 && !isWhite(game->gameBoard[originRow][originCol])) { return SP_GAME_EVENT_NONE; }

    src->moveOrigin.row = originRow;
    src->moveOrigin.column = originCol;
    src->moveDestination.row = destRow;
    src->moveDestination.column = destCol;

    return SP_GAME_EVENT_MOVE;
}


SP_GAME_EVENT spGameWindowHandleButtonsEvent(SPGameWin* src, SPChessGame* game, SDL_Event* event){
    /* Handles events on the buttons' side */

    int eventX = event->button.x , eventY = event->button.y;
    if (isClickOnRestart(eventX, eventY)){
        return SP_GAME_EVENT_RESTART;
    } else if (isClickOnSave(eventX, eventY)){
        if (src->isTheGameSaved == 0){
            return SP_GAME_EVENT_SAVE;
        }
    } else if (isClickOnLoad(eventX, eventY)){
        return SP_GAME_EVENT_LOAD;
    } else if (isClickOnUndo(eventX, eventY)){
        if (!spArrayListIsEmpty(game->lastMoves) && game->gameMode == 1){
            return SP_GAME_EVENT_UNDO;
        }
    } else if (isClickOnMainMenu(eventX, eventY)){
        return SP_GAME_EVENT_MAIN_MENU;
    } else if (isClickOnQuit(eventX, eventY)){
        return SP_GAME_EVENT_QUIT;
    }
    return SP_GAME_EVENT_NONE;
}


void spGameWindowDrag(SPGameWin* src, SPChessGame* game, SDL_Event* event){             // TODO
    /* drags the piece across the board */


}


SP_GAME_EVENT spGameWindowHandleEvent(SPGameWin* src, SPChessGame* game, SDL_Event* event) {
    if (event == NULL || src == NULL ) {
        return SP_GAME_EVENT_INVALID_ARGUMENT;
    }
    switch (event->type) {

        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_LEFT){ spGameWindowDeactivateGetMoves(src,game); }
            if (event->button.x > RIGHT_X){
                src->mouseDownEvent = NULL;
            }
            else if (event->button.x <= RIGHT_X && event->button.button == SDL_BUTTON_LEFT) {
                src->mouseDownEvent = event;
            }
            return SP_GAME_EVENT_NONE;

        case SDL_MOUSEBUTTONUP:
            if (event->button.button == SDL_BUTTON_LEFT) {
                spGameWindowDeactivateGetMoves(src, game);
                if (event->button.x > RIGHT_X && src->mouseDownEvent == NULL) {
                    return spGameWindowHandleButtonsEvent(src, game, event);
                } else if (event->button.x <= RIGHT_X && src->mouseDownEvent != NULL) {
                    return spGameWindowHandleBoardEvent(src, game, event);
                }
                else { return SP_GAME_EVENT_NONE; }
            }
            else if (event->button.button == SDL_BUTTON_RIGHT && event->button.x <= RIGHT_X
                     && game->difficulty <= 2 && game->gameMode == 1) {
                if (src->getMovesOn == 1) {
                    resetGetMoves(src, game);
                    src->getMovesOn = 1 - src->getMovesOn;
                }
                else {
                    if (spGameWindowActivateGetMoves(src, game, event) == 1) {
                        src->getMovesOn = 1 - src->getMovesOn;
                    }
                }
            }
            return SP_GAME_EVENT_NONE;

        case SDL_MOUSEMOTION:
            spGameWindowDrag(src, game, event);

        case SDL_WINDOWEVENT:
            if (event->button.button == SDL_BUTTON_LEFT){ spGameWindowDeactivateGetMoves(src,game); }
            if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
                return SP_GAME_EVENT_QUIT;
            }
            break;

        default:
            return SP_GAME_EVENT_NONE;
    }
    return SP_GAME_EVENT_NONE;
}
