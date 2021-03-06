//
// Created by Omer Koren & Ori Haviv 2017
//


#include <stdio.h>
#include "SPChessGameWin.h"



int getClickColumn(int x) {
    // Returns the click's relevant column on the board */

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
    // Returns the click's relevant row on the board */

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

int isClickOnBoard(SDL_Event* event) {
    // Indicates whether a click was on the the game board */

    int x = event->button.x , y = event->button.y;
    if ((x >= BOARD_X && x <= BOARD_X + BOARD_W) && (y >= BOARD_Y && y <= BOARD_Y + BOARD_H)) {
        return 1;
    }
    return 0;
}


int isClickOnRestart(int x, int y) {
    // Indicates whether a click was on the "Restart Game" button */

    if ((x >= GAME_BUTTONS_X && x <= GAME_BUTTONS_X + GAME_BUTTON_W) && (y >= RESTART_BUTTON_Y && y <= RESTART_BUTTON_Y + GAME_BUTTON_H)) {
        return 1;
    }
    return 0;
}



int isClickOnSave(int x, int y) {
    // Indicates whether a click was on the "Save Game" button */

    if ((x >= GAME_BUTTONS_X && x <= GAME_BUTTONS_X + GAME_BUTTON_W) && (y >= SAVE_BUTTON_Y && y <= SAVE_BUTTON_Y + GAME_BUTTON_H)) {
        return 1;
    }
    return 0;
}


int isClickOnLoad(int x, int y) {
    // Indicates whether a click was on the "Load Game" button */

    if ((x >= GAME_BUTTONS_X && x <= GAME_BUTTONS_X + GAME_BUTTON_W) && (y >= LOAD_BUTTON_Y && y <= LOAD_BUTTON_Y + GAME_BUTTON_H)) {
        return 1;
    }
    return 0;
}

int isClickOnUndo(int x, int y) {
    // Indicates whether a click was on the "Undo Move" button */

    if ((x >= GAME_BUTTONS_X && x <= GAME_BUTTONS_X + GAME_BUTTON_W) && (y >= UNDO_BUTTON_Y && y <= UNDO_BUTTON_Y + GAME_BUTTON_H)) {
        return 1;
    }
    return 0;
}

int isClickOnMainMenu(int x, int y) {
    // Indicates whether a click was on the "Main Menu" button */

    if ((x >= GAME_BUTTONS_X && x <= GAME_BUTTONS_X + GAME_BUTTON_W) && (y >= MAIN_MENU_BUTTON_Y && y <= MAIN_MENU_BUTTON_Y + GAME_BUTTON_H)) {
        return 1;
    }
    return 0;
}


int isClickOnQuit(int x, int y) {
    // Indicates whether a click was on the "Quit Game" button */

    if ((x >= GAME_BUTTONS_X && x <= GAME_BUTTONS_X + GAME_BUTTON_W) && (y >= QUIT_BUTTON_Y && y <= QUIT_BUTTON_Y + GAME_BUTTON_H)) {
        return 1;
    }
    return 0;
}


bool GameLoadingSurfaceFunc(SPGameWin *src, SDL_Texture** texture, char* path) {
    // Loading a surface into the given texture from the given path */

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
    // Creates textures for the board */

    bool check;

    // board
    check = GameLoadingSurfaceFunc(res, &(res->board), "../GUI/images/gameWindow/board.bmp");
    if (!check){ return 0; }

    // white king
    check = GameLoadingSurfaceFunc(res, &(res->whiteKing), "../GUI/images/gameWindow/whiteKing.bmp");
    if (!check){ return 0; }

    // black king
    check = GameLoadingSurfaceFunc(res, &(res->blackKing), "../GUI/images/gameWindow/blackKing.bmp");
    if (!check){ return 0; }

    // white queen
    check = GameLoadingSurfaceFunc(res, &(res->whiteQueen), "../GUI/images/gameWindow/whiteQueen.bmp");
    if (!check){ return 0; }

    // black queen
    check = GameLoadingSurfaceFunc(res, &(res->blackQueen), "../GUI/images/gameWindow/blackQueen.bmp");
    if (!check){ return 0; }

    // white bishop
    check = GameLoadingSurfaceFunc(res, &(res->whiteBishop), "../GUI/images/gameWindow/whiteBishop.bmp");
    if (!check){ return 0; }

    // black bishop
    check = GameLoadingSurfaceFunc(res, &(res->blackBishop), "../GUI/images/gameWindow/blackBishop.bmp");
    if (!check){ return 0; }

    // white knight
    check = GameLoadingSurfaceFunc(res, &(res->whiteKnight), "../GUI/images/gameWindow/whiteKnight.bmp");
    if (!check){ return 0; }

    // black knight
    check = GameLoadingSurfaceFunc(res, &(res->blackKnight), "../GUI/images/gameWindow/blackKnight.bmp");
    if (!check){ return 0; }

    // white rook
    check = GameLoadingSurfaceFunc(res, &(res->whiteRook), "../GUI/images/gameWindow/whiteRook.bmp");
    if (!check){ return 0; }

    // black rook
    check = GameLoadingSurfaceFunc(res, &(res->blackRook), "../GUI/images/gameWindow/blackRook.bmp");
    if (!check){ return 0; }

    // white pawn
    check = GameLoadingSurfaceFunc(res, &(res->whitePawn), "../GUI/images/gameWindow/whitePawn.bmp");
    if (!check){ return 0; }

    // black pawn
    check = GameLoadingSurfaceFunc(res, &(res->blackPawn), "../GUI/images/gameWindow/blackPawn.bmp");
    if (!check){ return 0; }

    // yellow square
    check =GameLoadingSurfaceFunc(res , &(res->yellow), "../GUI/images/gameWindow/yellow.bmp");
    if (!check){ return 0; }

    // red square
    check =GameLoadingSurfaceFunc(res , &(res->red), "../GUI/images/gameWindow/red.bmp");
    if (!check){ return 0; }

    // green square
    check =GameLoadingSurfaceFunc(res , &(res->green), "../GUI/images/gameWindow/green.bmp");
    if (!check){ return 0; }

    // purple square
    check =GameLoadingSurfaceFunc(res , &(res->purple), "../GUI/images/gameWindow/purple.bmp");
    if (!check){ return 0; }

    return 1;
}


int createButtonsTextures(SPGameWin* res){
    // Creates textures for the buttons */

    bool check;

    // restart game
    check = GameLoadingSurfaceFunc(res, &(res->restartGame), "../GUI/images/gameWindow/restartGame.bmp");
    if (!check){ return 0; }

    // save game
    check = GameLoadingSurfaceFunc(res, &(res->saveGame), "../GUI/images/gameWindow/saveGame.bmp");
    if (!check){ return 0; }

    // save game - enabled
    check = GameLoadingSurfaceFunc(res, &(res->saveGameEnabled), "../GUI/images/gameWindow/saveGameEnabled.bmp");
    if (!check){ return 0; }

    // load game
    check = GameLoadingSurfaceFunc(res, &(res->loadGame), "../GUI/images/gameWindow/loadGame.bmp");
    if (!check){ return 0; }

    // undo move
    check = GameLoadingSurfaceFunc(res, &(res->undoMove), "../GUI/images/gameWindow/undoMove.bmp");
    if (!check){ return 0; }

    // undo move - enabled
    check = GameLoadingSurfaceFunc(res, &(res->undoMoveEnabled), "../GUI/images/gameWindow/undoMoveEnabled.bmp");
    if (!check){ return 0; }

    // main menu
    check = GameLoadingSurfaceFunc(res, &(res->mainMenu), "../GUI/images/gameWindow/mainMenu.bmp");
    if (!check){ return 0; }

    // quit game
    check = GameLoadingSurfaceFunc(res, &(res->quitGame), "../GUI/images/gameWindow/quitGame.bmp");
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
    res->isPieceDragged = 0;
    res->moveOrigin.row = -1;
    res->moveOrigin.column = -1;
    res->moveDestination.row = -1;
    res->moveDestination.column = -1;

    SDL_Surface* loadingSurface = NULL; //Used as temp surface

	// Create an application window with the following settings:
	res->gameWindow = SDL_CreateWindow("Chess Game", // window title
			SDL_WINDOWPOS_CENTERED,           // initial x position
			SDL_WINDOWPOS_CENTERED,           // initial y position
            GAME_WINDOW_W,                               // width, in pixels
            GAME_WINDOW_H,                               // height, in pixels
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

    res->boardTiles = (SDL_Texture**) calloc(GAMESIZE*GAMESIZE, sizeof(SDL_Texture*));
    if (!res->boardTiles){
        printf("ERROR: calloc failed - board tiles\n");
        return NULL;
    }

    SDL_FreeSurface(loadingSurface);
    return res;
}


void spGameWindowDestroyBoard(SPGameWin* src){
    // Destroys board */

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
        SDL_DestroyTexture(src->whiteQueen);
    }
    if (src->blackQueen != NULL ) {
        SDL_DestroyTexture(src->blackQueen);
    }
    if (src->whiteBishop != NULL ) {
        SDL_DestroyTexture(src->whiteBishop);
    }
    if (src->blackBishop != NULL ) {
        SDL_DestroyTexture(src->blackBishop);
    }
    if (src->whiteKnight != NULL ) {
        SDL_DestroyTexture(src->whiteKnight);
    }
    if (src->blackKnight != NULL ) {
        SDL_DestroyTexture(src->blackKnight);
    }
    if (src->whiteRook != NULL ) {
        SDL_DestroyTexture(src->whiteRook);
    }
    if (src->blackRook != NULL ) {
        SDL_DestroyTexture(src->blackRook);
    }
    if (src->whitePawn != NULL ) {
        SDL_DestroyTexture(src->whitePawn);
    }
    if (src->blackPawn != NULL ) {
        SDL_DestroyTexture(src->blackPawn);
    }

}

void spGameWindowDestroyButtons(SPGameWin* src){
    // Destroys buttons */

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
        SDL_DestroyWindow(src->gameWindow);
    }
    if (src->gameRenderer != NULL ) {
        SDL_DestroyRenderer(src->gameRenderer);
    }
    if (src->boardTiles != NULL ) {
        free(src->boardTiles);
    }
    spGameWindowDestroyBoard(src);
    spGameWindowDestroyButtons(src);
	free(src);
}


void putTextureInRec(SPGameWin* src, SPChessGame* game, int i, int j, SDL_Rect* rec) {
    // Draws a specific piece in a spacific rectangle on the board */

    switch (game->gameBoard[i][j]){
        case BLANK:
            return;
        case KINGWHITE:
            SDL_RenderCopy(src->gameRenderer, src->whiteKing, NULL, rec);
            break;
        case KINGBLACK:
            SDL_RenderCopy(src->gameRenderer, src->blackKing, NULL, rec);
            break;
        case QUEENWHITE:
            SDL_RenderCopy(src->gameRenderer, src->whiteQueen, NULL, rec);
            break;
        case QUEENBLACK:
            SDL_RenderCopy(src->gameRenderer, src->blackQueen, NULL, rec);
            break;
        case BISHOPWHITE:
            SDL_RenderCopy(src->gameRenderer, src->whiteBishop, NULL, rec);
            break;
        case BISHOPBLACK:
            SDL_RenderCopy(src->gameRenderer, src->blackBishop, NULL, rec);
            break;
        case KNIGHTWHITE:
            SDL_RenderCopy(src->gameRenderer, src->whiteKnight, NULL, rec);
            break;
        case KNIGHTBLACK:
            SDL_RenderCopy(src->gameRenderer, src->blackKnight, NULL, rec);
            break;
        case ROOKWHITE:
            SDL_RenderCopy(src->gameRenderer, src->whiteRook, NULL, rec);
            break;
        case ROOKBLACK:
            SDL_RenderCopy(src->gameRenderer, src->blackRook, NULL, rec);
            break;
        case PAWNWHITE:
            SDL_RenderCopy(src->gameRenderer, src->whitePawn, NULL, rec);
            break;
        case PAWNBLACK:
            SDL_RenderCopy(src->gameRenderer, src->blackPawn, NULL, rec);
            break;
        default:
            break;
    }
    return;
}

void updateGameBoard(SPGameWin* src, SPChessGame* game) {
    // Draws the relevant pieces over the board */

    SDL_Rect rec;
    int i = 0, j = 0;
    for (i = 0; i < GAMESIZE; i++) {
        for (j = 0; j < GAMESIZE; j++) {
            rec.x = 59 + j * PIECE_SIZE;
            rec.y = 60 + (GAMESIZE - 1 - i) * PIECE_SIZE;
            rec.w = PIECE_SIZE;
            rec.h = PIECE_SIZE;
            if (src->moveOrigin.row == i && src->moveOrigin.column == j) {
                rec.x = src->dragRec.x;
                rec.y = src->dragRec.y;
            }
            putTextureInRec(src, game, i, j, &rec);
        }
    }
}


void updateSpecialTiles(SPGameWin* src){
    // Draws special tiles for get-moves */

    SDL_Rect rec;
    int i , j;
    for (i = 0 ; i < GAMESIZE ; i++){
        for (j = 0 ; j < GAMESIZE ; j++){
            rec.x = 59 + j * PIECE_SIZE;
            rec.y = 60 + (GAMESIZE - 1 - i) * PIECE_SIZE;
            rec.w = PIECE_SIZE;
            rec.h = PIECE_SIZE;
            if (src->getMovesOn == 1){
                SDL_RenderCopy(src->gameRenderer, (src->boardTiles[i* sizeof(SDL_Texture*) + j]), NULL, &rec);
            }
            else {
                src->boardTiles[i* sizeof(SDL_Texture*) + j] = NULL;
            }
        }
    }
}


void spGameWindowDrawBoard(SPGameWin* src, SPChessGame* game) {
    // Draws the board's side */

	if(src == NULL || game == NULL){
		return;
	}
	SDL_Rect rec = { .x = BOARD_X, .y = BOARD_Y, .w = BOARD_W, .h = BOARD_H };
	SDL_RenderCopy(src->gameRenderer, src->board, NULL, &rec);

	updateGameBoard(src, game);

    updateSpecialTiles(src);
}


void spGameWindowDrawButtons(SPGameWin* src, SPChessGame* game){
    // Draws the buttons' side */

    if(src == NULL || game == NULL){
        return;
    }


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
    SDL_RenderClear(src->gameRenderer);
    spGameWindowDrawBoard(src, game);
    spGameWindowDrawButtons(src, game);
    SDL_SetRenderDrawColor(src->gameRenderer, 134, 134, 134, 192);
    SDL_RenderPresent(src->gameRenderer);
}


int spGameWindowActivateGetMoves(SPGameWin* src, SPChessGame* game, SDL_Event* event){
    // Handles "get_moves" events */

    int eventCol = getClickColumn(event->button.x) , eventRow = getClickRow(event->button.y) , i , row , col;
    if (eventCol < 0 || eventRow < 0){ return 0; }
    if (game->userColor == 0 && !isBlack(game->gameBoard[eventRow][eventCol])){ return 0; }
    if (game->userColor == 1 && !isWhite(game->gameBoard[eventRow][eventCol])){ return 0; }

    SPArrayList *possibleMoves = getMovesForSoldier(game, eventRow, eventCol);
    action move;
//    SDL_Rect rec;

    for (i = 0 ; i < possibleMoves->actualSize ; i++){
        move = *(spArrayListGetAt(possibleMoves, i));
        row = move.current.row;
        col = move.current.column;
        if (move.castling == SP_CHESS_NO_CASTLING){
            (src->boardTiles[row* sizeof(SDL_Texture*) + col]) = src->yellow;
            if (game->difficulty <= 2) {
                if (move.captured != BLANK) { src->boardTiles[row* sizeof(SDL_Texture*) + col] = src->green; }
                if (isTheSoldierThreatened(game, game->currentPlayer, move.current)) {
                    src->boardTiles[row* sizeof(SDL_Texture*) + col] = src->red;
                }
            }
        }
        else{
            src->boardTiles[row* sizeof(SDL_Texture*) + col] = (src->purple);
        }
    }

    spArrayListDestroy(&possibleMoves);
    return 1;
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


double getDist(int x1, int y1, int x2, int y2){
    /* Computes the distance between two points on grid */

    int dx = x1 - x2, dy = y1 - y2;
    double res = pow(dx,2) + pow(dy,2);
    res = pow(res,0.5);
    return res;
}


void spGameWindowDrag(SPGameWin* src, SDL_Event* event){
    /* Drags the piece across the board.
     * The method is called <=> (src->isPieceDragged == 1 && the cursor is between board boundries */

    int mouseSourceX = src->dragRec.x + PIECE_SIZE/2 , mouseSourceY = src->dragRec.y + PIECE_SIZE/2;
    double dist = getDist(mouseSourceX, mouseSourceY ,event->button.x , event->button.y);
    if (dist > PIECE_DISTANCE_UPDATE){
        src->dragRec.x = event->button.x - PIECE_SIZE/2;
        src->dragRec.y = event->button.y - PIECE_SIZE/2;
    }
}

SP_GAME_EVENT spGameWindowDrop(SPGameWin* src, SDL_Event* event){
    /* Drops the piece to the right position on the board */

    src->isPieceDragged = 0;

    src->moveDestination.column = getClickColumn(event->button.x);
    src->moveDestination.row = getClickRow(event->button.y);

    return SP_GAME_EVENT_MOVE;
}


SP_GAME_EVENT spGameWindowHandleButtonDownEventOnBoard(SPGameWin* src, SPChessGame* game, SDL_Event* event){
    /* Handles a "button-down" event */

    if (event->button.button == SDL_BUTTON_LEFT){ src->getMovesOn = 0; }
    if (!isClickOnBoard(event)){
//        src->mouseDownEvent = NULL;
        src->isPieceDragged = 0;
    }
    else if (isClickOnBoard(event) && event->button.button == SDL_BUTTON_LEFT) {
//        src->mouseDownEvent = event;
        int eventCol = getClickColumn(event->button.x) , eventRow = getClickRow(event->button.y);
        if (game->userColor == 0 && !isBlack(game->gameBoard[eventRow][eventCol])) { return SP_GAME_EVENT_NONE; }
        if (game->userColor == 1 && !isWhite(game->gameBoard[eventRow][eventCol])) { return SP_GAME_EVENT_NONE; }
        src->moveOrigin.row = eventRow;
        src->moveOrigin.column = eventCol;
        src->dragRec.x = event->button.x - PIECE_SIZE/2;
        src->dragRec.y = event->button.y - PIECE_SIZE/2;
        src->isPieceDragged = 1;
    }
    return SP_GAME_EVENT_NONE;
}


SP_GAME_EVENT spGameWindowHandleButtonUpEvent(SPGameWin* src, SPChessGame* game, SDL_Event* event){
    /* Handles a "button-up" event */

    if (event->button.button == SDL_BUTTON_LEFT) {
//        spGameWindowDeactivateGetMoves(src, game);
        // support button event
        if (!isClickOnBoard(event) && src->isPieceDragged == 0) {
            return spGameWindowHandleButtonsEvent(src, game, event);
        }
            //support game event
        else if (isClickOnBoard(event) && src->isPieceDragged == 1) {
            return spGameWindowDrop(src, event);
        }
        else { return SP_GAME_EVENT_NONE; }
    }
        // support "get-moves"
    else if (event->button.button == SDL_BUTTON_RIGHT && isClickOnBoard(event)
             && game->difficulty <= 2 && game->gameMode == 1) {
        if (src->getMovesOn == 1) {
            src->getMovesOn = 0;
        }
        else {
            if (spGameWindowActivateGetMoves(src, game, event) == 1) {
                src->getMovesOn = 1;
            }
        }
    }
    return SP_GAME_EVENT_NONE;
}


SP_GAME_EVENT spGameWindowHandleEvent(SPGameWin* src, SPChessGame* game, SDL_Event* event) {
    if (event == NULL || src == NULL ) {
        return SP_GAME_EVENT_INVALID_ARGUMENT;
    }
    switch (event->type) {

        case SDL_MOUSEBUTTONDOWN:
            return spGameWindowHandleButtonDownEventOnBoard(src, game, event);

        case SDL_MOUSEBUTTONUP:
            return spGameWindowHandleButtonUpEvent(src, game, event);

        case SDL_MOUSEMOTION:
            if (src->isPieceDragged && isClickOnBoard(event)) {
                spGameWindowDrag(src, event);
            }
            else{
                src->isPieceDragged = 0;
                src->moveOrigin.row = -1;
                src->moveOrigin.column = -1;
            }

        case SDL_WINDOWEVENT:
            if (event->button.button == SDL_BUTTON_LEFT){ src->getMovesOn = 0; }
            if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
                return SP_GAME_EVENT_QUIT;
            }
            break;
        default:
            return SP_GAME_EVENT_NONE;
    }
    return SP_GAME_EVENT_NONE;
}


void spGameWindowHide(SPGameWin *src) {
    SDL_HideWindow(src->gameWindow);
}

void spGameWindowShow(SPGameWin *src) {
    SDL_ShowWindow(src->gameWindow);
}