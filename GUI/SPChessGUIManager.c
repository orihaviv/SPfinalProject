#include <stdio.h>
#include <stdlib.h>
#include "SPChessGUIManager.h"



SPGuiManager *spManagerCreate() {
    SPGuiManager *res = (SPGuiManager *) malloc(sizeof(SPGuiManager));
    if (res == NULL) {
        return NULL;
    }
    res->mainWin = spMainWindowCreate();
    if (res->mainWin == NULL) {
        free(res);
        return NULL;
    }
    res->loadWin = NULL;
    res->settingsWin = NULL;
    res->gameWin = NULL;
    res->game = NULL;
    res->activeWin = SP_MAIN_WINDOW_ACTIVE;
    return res;
}


void spManagerDestroy(SPGuiManager *src) {
    if (!src) {
        return;
    }
    if (src->gameWin != NULL) {
        spGameWindowDestroy(src->gameWin);
        src->gameWin = NULL;
    }
    if (src->loadWin != NULL) {
        spLoadWindowDestroy(src->loadWin);
        src->loadWin = NULL;
    }
    if (src->settingsWin != NULL) {
        spSettingsWindowDestroy(src->settingsWin);
        src->settingsWin = NULL;
    }
    if (src->game != NULL) {
        chessGameDestroy(&(src->game));
    }
    spMainWindowDestroy(src->mainWin);
    src->mainWin = NULL;
    free(src);
}


void spManagerDraw(SPGuiManager *src) {
    if (!src) {
        return;
    }
    if (src->activeWin == SP_MAIN_WINDOW_ACTIVE) {
        spMainWindowDraw(src->mainWin);
    } else if (src->activeWin == SP_SETTINGS_WINDOW_ACTIVE) {
        spSettingsWindowDraw(src->settingsWin);
    } else if (src->activeWin == SP_LOAD_WINDOW_ACTIVE) {
        spLoadWindowDraw(src->loadWin);
    } else if (src->activeWin == SP_GAME_WINDOW_ACTIVE) {
        spGameWindowDraw(src->gameWin, src->game);
    }
}


SP_MANAGER_EVENT handleManagerDueToMainEvent(SPGuiManager *src, SP_MAIN_EVENT event) {
    if (src == NULL) {
        return SP_MANAGER_NONE;
    }
    switch (event) {
        case SP_MAIN_NEW_GAME:
            spMainWindowHide(src->mainWin);
            src->settingsWin = spSettingsWindowCreate();
            if (src->settingsWin == NULL) {
                printf("Couldn't create settings window\n");
                return SP_MANAGER_QUTT;
            }
            src->game = chessGameCreate();
            if (!src->game) {
                printf("Couldn't create manager->game\n");
                return SP_MANAGER_QUTT;
            }
            src->activeWin = SP_SETTINGS_WINDOW_ACTIVE;
            break;
        case SP_MAIN_LOAD_GAME:
            spMainWindowHide(src->mainWin);
            src->loadWin = spLoadWindowCreate(MAIN_CALLER);
            if (src->loadWin == NULL) {
                printf("Couldn't create load window\n");
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


SP_MANAGER_EVENT handleManagerDueToSettingsEvent(SPGuiManager *src, SP_SETTINGS_EVENT event) {
    if (src == NULL) {
        return SP_MANAGER_NONE;
    }
    switch (event) {
        case SP_SETTINGS_BACK:
            chessGameDestroy(&(src->game));
            spSettingsWindowDestroy(src->settingsWin);
            src->settingsWin = NULL;
            src->activeWin = SP_MAIN_WINDOW_ACTIVE;
            spMainWindowShow(src->mainWin);
            break;
        case SP_SETTINGS_START:
            spSettingsWindowDestroy(src->settingsWin);
            src->settingsWin = NULL;
            src->gameWin = spGameWindowCreate();
            src->game->state = 1;
            if (src->gameWin == NULL) {
                printf("Couldn't create settings window\n");
                return SP_MANAGER_QUTT;
            }
            if (src->game->userColor == 0){
                action nextMove = *(spMinimaxSuggestMove(src->game, src->game->difficulty));
                while (chessGameSetMove(src->game, nextMove.prev, nextMove.current, 0, 1) !=
                       SP_CHESS_GAME_SUCCESS) { continue; }
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


SP_PROMOTION_EVENT showPromotionMessageBox(SPGuiManager *src) {
    const SDL_MessageBoxButtonData buttons[] = {
            {0, 0, "Pawn"},
            {1, 1, "Rook"},
            {2, 2, "Knight"},
            {3, 3, "Bishop"},
            {4, 4, "Queen"},
    };
    const SDL_MessageBoxColorScheme colorScheme = {
            { /* .colors (.r, .g, .b) */
                    /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
                    {192, 192, 192},
                    /* [SDL_MESSAGEBOX_COLOR_TEXT] */
                    {0, 0, 0},
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
                    {0, 0, 0},
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
                    {192, 192, 192},
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
                    {90, 139, 199}
            }
    };
    const SDL_MessageBoxData messageboxdata = {
            SDL_MESSAGEBOX_INFORMATION, /* .flags */
            src->gameWin->gameWindow, /* .window */
            "Pawn Promotion", /* .title */
            "Your pawn can be promoted - Select a promotion", /* .message */
            SDL_arraysize(buttons), /* .numbuttons */
            buttons, /* .buttons */
            &colorScheme /* .colorScheme */
    };
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        printf("Error: displaying message box");
        return SP_PROMOTION_INVALID;
    }
    if (buttonid == -1) {
        printf("no selection");
        return SP_PROMOTION_PAWN;
    } else {
        switch (buttonid) {
            case 0:
                return SP_PROMOTION_PAWN;
            case 1:
                return SP_PROMOTION_ROOK;
            case 2:
                return SP_PROMOTION_KNIGHT;
            case 3:
                return SP_PROMOTION_BISHOP;
            case 4:
                return SP_PROMOTION_QUEEN;
            default:
                return SP_PROMOTION_INVALID;

        }
    }
}

int showEndingMessageBox(int winner, SPGuiManager *src) {
    char *msg = "A problem occurred";
    if (winner == 0) { msg = "Checkmate! black player wins the game"; }
    if (winner == 1) { msg = "Checkmate! white player wins the game"; }
    if (winner == 2) { msg = "It's a tie!"; }
    const SDL_MessageBoxButtonData buttons[] = {{0, 0, "Quit"},};
    const SDL_MessageBoxColorScheme colorScheme = {
            { /* .colors (.r, .g, .b) */
                    /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
                    {192, 192, 192},
                    /* [SDL_MESSAGEBOX_COLOR_TEXT] */
                    {0, 0, 0},
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
                    {0, 0, 0},
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
                    {192, 192, 192},
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
                    {90, 139, 199}
            }
    };
    const SDL_MessageBoxData messageboxdata = {
            SDL_MESSAGEBOX_INFORMATION, /* .flags */
            src->gameWin->gameWindow, /* .window */
            "Game Over", /* .title */
            msg, /* .message */
            SDL_arraysize(buttons), /* .numbuttons */
            buttons, /* .buttons */
            &colorScheme /* .colorScheme */
    };
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        printf("Error: displaying message box");
        return 0;
    }
    if (buttonid == -1) {
        printf("No selection");
        return SP_PROMOTION_PAWN;
    } else if (buttonid == 0) { return 1; }
    return 0;
}

void handleSaveGame(SPGuiManager *src) {
    if (src->gameWin->isTheGameSaved == 0) {
        if (guiSaveGame(src->game) == 0) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Not able to save the game", NULL);
        } else {
            src->gameWin->isTheGameSaved = 1;
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "saved!", "Game saved", NULL);
        }
    }
}

void handleLoadGame(SPGuiManager *src, int slot) {
    bool loaded = guiLoadChessGame(&(src->game), slot);
    if (loaded || src->game == NULL) {
        src->gameWin = spGameWindowCreate();
        if (src->gameWin == NULL) { SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Not able to load the game", NULL); }
        src->game->state = 1;
        src->gameWin->isTheGameSaved = 1;
    } else { SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Not able to load the game", NULL); }
}

int askWhetherToSave(SPGuiManager *src) {
    const SDL_MessageBoxButtonData buttons[] = {
            {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Yes"},
            {0,                                       1, "No"},
            {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "Cancel"},
    };
    const SDL_MessageBoxColorScheme colorScheme = {
            {
                    /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
                    {192, 192, 192},
                    /* [SDL_MESSAGEBOX_COLOR_TEXT] */
                    {0, 0, 0},
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
                    {0, 0, 0},
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
                    {192, 192, 192},
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
                    {90, 139, 199}
            }
    };
    const SDL_MessageBoxData messageBoxData = {
            SDL_MESSAGEBOX_INFORMATION,
            NULL,
            "You are about to quit the game", /* .title */
            "Do you want to save the current game?", /* .message */
            SDL_arraysize(buttons), /* .numOfButtons */
            buttons, /* .buttons */
            &colorScheme /* .colorScheme */
    };
    int buttonID;
    if (SDL_ShowMessageBox(&messageBoxData, &buttonID) < 0) {
        SDL_Log("Error displaying message box");
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


void handleMainMenu(SPGuiManager *src) {
    int whetherToQuit = 1;
    if (src->gameWin->isTheGameSaved == 0) {
        whetherToQuit = askWhetherToSave(src);
    }
    if (whetherToQuit == 1) {
        spGameWindowDestroy(src->gameWin);
        src->gameWin = NULL;
        src->activeWin = SP_MAIN_WINDOW_ACTIVE;
    }
}


SP_MANAGER_EVENT handleQuitGame(SPGuiManager *src) {
    int whetherToQuit = 1;
    if (src->gameWin->isTheGameSaved == 0) {
        whetherToQuit = askWhetherToSave(src);
    }
    if (whetherToQuit == 1) {
        return SP_MANAGER_QUTT;
    }
    return SP_MANAGER_NONE;
}


void guiPawnPromotionHandler(SPGuiManager *src, position dest, int isMini) {
    if (!src) { return; }
    char piece = BLANK;
    SP_PROMOTION_EVENT msg;
    if ((src->game->gameMode == 1 && src->game->currentPlayer == src->game->userColor) || isMini == 1) {
        piece = QUEENWHITE;
        if (isMini == 0) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Pawn Promotion",
                                     "Computer promoted his Pawn to a Queen", NULL);
        }
    } else { // user's turn
        msg = showPromotionMessageBox(src);
        switch (msg) {
            case SP_PROMOTION_ROOK:
                piece = ROOKWHITE;
                break;
            case SP_PROMOTION_BISHOP:
                piece = BISHOPWHITE;
                break;
            case SP_PROMOTION_KNIGHT:
                piece = KNIGHTWHITE;
                break;
            case SP_PROMOTION_QUEEN:
                piece = QUEENWHITE;
                break;
            default:
                break;
        }
    }
    if (src->game->gameBoard[dest.row][dest.column] == PAWNBLACK) {
        src->game->gameBoard[dest.row][dest.column] = (char) (toupper(piece));
    } else if (src->game->gameBoard[dest.row][dest.column] == PAWNWHITE) {
        src->game->gameBoard[dest.row][dest.column] = piece;
    }
}



void showCheckMessage(int player) {
    // Showing message box for check
    if (player == 0) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Check!", "Black King is threatened!", NULL);
    } else if (player == 1) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Check!", "White King is threatened!", NULL);
    }
}


SP_MANAGER_EVENT handleMove(SPGuiManager *src) {
    char soldier;
    position origin = src->gameWin->moveOrigin;
    position dest = src->gameWin->moveDestination;
    SP_CHESS_GAME_MESSAGE msg = chessGameSetMove(src->game, origin, dest, 0, 1);
    SP_CHESS_GAME_STATE winner;
    if (msg == SP_CHESS_GAME_SUCCESS) {
        soldier = src->game->gameBoard[dest.row][dest.column];
        if ((soldier == PAWNBLACK && dest.row == 0) || (soldier == PAWNWHITE && dest.row == 7)) {
            guiPawnPromotionHandler(src, dest, 0);
        }
        goto moveDone;
    } else if (msg == SP_CHESS_GAME_ILLEGAL_MOVE) {
        if (((origin.column == 7 && dest.column == 4) || (dest.column == 7 && origin.column == 4)) && origin.row == 7 &&
            dest.row == 7 &&
            isBlackRightCastlingValid(src->game) == 1) {
            executeBlackRightCastling(src->game);
            goto moveDone;
        } else if (((origin.column == 0 && dest.column == 4) || (dest.column == 0 && origin.column == 4)) &&
                   origin.row == 7 && dest.row == 7 &&
                   isBlackLeftCastlingValid(src->game) == 1) {
            executeBlackLeftCastling(src->game);
            goto moveDone;
        } else if (((origin.column == 0 && dest.column == 4) || (dest.column == 0 && origin.column == 4)) &&
                   origin.row == 0 && dest.row == 0 &&
                   isWhiteLeftCastlingValid(src->game) == 1) {
            executeWhiteLeftCastling(src->game);
            goto moveDone;
        } else if (((origin.column == 7 && dest.column == 4) || (dest.column == 7 && origin.column == 4)) &&
                   origin.row == 0 && dest.row == 0 &&
                   isWhiteRightCastlingValid(src->game) == 1) {
            executeWhiteRightCastling(src->game);
            goto moveDone;
        }
    }
    goto anyway;

    moveDone:
    src->gameWin->isTheGameSaved = 0;
    winner = chessCheckWinner(src->game, 0, 1);

    if (src->game->gameMode == 1 && winner == SP_CHESS_GAME_NO_WINNER) {
        if (isTheKingThreatened(src->game, src->game->currentPlayer)) { showCheckMessage(src->game->currentPlayer); }
        action nextMove = *(spMinimaxSuggestMove(src->game, src->game->difficulty));
        while (chessGameSetMove(src->game, nextMove.prev, nextMove.current, 0, 1) !=
               SP_CHESS_GAME_SUCCESS) { continue; }
        soldier = src->game->gameBoard[nextMove.current.row][nextMove.current.column];
        if ((soldier == PAWNBLACK && nextMove.current.row == 0) ||
            (soldier == PAWNWHITE && nextMove.current.row == 7)) {
            guiPawnPromotionHandler(src, dest, 0);
        }
        winner = chessCheckWinner(src->game, 0, 1);
    }
    switch (winner) {
        case SP_CHESS_GAME_TIE:
            showEndingMessageBox(2, src);
            return SP_MANAGER_QUTT;
        case SP_CHESS_GAME_WHITE_WINNER:
            showEndingMessageBox(1, src);
            return SP_MANAGER_QUTT;
        case SP_CHESS_GAME_BLACK_WINNER:
            showEndingMessageBox(0, src);
            return SP_MANAGER_QUTT;
        case SP_CHESS_GAME_NO_WINNER:
            if (isTheKingThreatened(src->game, src->game->currentPlayer)) { showCheckMessage(src->game->currentPlayer); }
        default:
            break;
    }
    anyway:
    return SP_MANAGER_NONE;
}

SP_MANAGER_EVENT handleManagerDueToGameEvent(SPGuiManager *src, SP_GAME_EVENT event) {
    if (event == SP_GAME_EVENT_NONE || src == NULL) {
        return SP_MANAGER_NONE;
    }
    switch (event) {
        case SP_GAME_EVENT_RESTART:
            initializeBoard(src->game);
            src->gameWin->isTheGameSaved = 0;
            break;
        case SP_GAME_EVENT_SAVE:
            handleSaveGame(src);
            break;
        case SP_GAME_EVENT_LOAD:
            spGameWindowHide(src->gameWin);
            src->loadWin = spLoadWindowCreate(GAME_CALLER);
            if (src->loadWin == NULL) {
                printf("Couldn't create load window\n");
                return SP_MANAGER_QUTT;
            }
            src->activeWin = SP_LOAD_WINDOW_ACTIVE;
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
            handleMove(src);
            break;
        default:
            break;
    }
    return SP_MANAGER_NONE;
}


SP_MANAGER_EVENT handleManagerDueToLoadEvent(SPGuiManager *src, SP_LOAD_EVENT event) {
    if (src == NULL) {
        return SP_MANAGER_NONE;
    }
    switch (event) {
        case SP_LOAD_BACK_MAIN:
            spLoadWindowDestroy(src->loadWin);
            src->loadWin = NULL;
            src->activeWin = SP_MAIN_WINDOW_ACTIVE;
            spMainWindowShow(src->mainWin);
            break;
        case SP_LOAD_BACK_GAME:
            spLoadWindowDestroy(src->loadWin);
            src->loadWin = NULL;
            src->activeWin = SP_GAME_WINDOW_ACTIVE;
            spGameWindowShow(src->gameWin);
            break;
        case SP_LOAD_NONE:
            break;
        case SP_LOAD_1:
            handleLoadGame(src, 1);
            src->activeWin = SP_GAME_WINDOW_ACTIVE;
            break;
        case SP_LOAD_2:
            handleLoadGame(src, 2);
            src->activeWin = SP_GAME_WINDOW_ACTIVE;
            break;
        case SP_LOAD_3:
            handleLoadGame(src, 3);
            src->activeWin = SP_GAME_WINDOW_ACTIVE;
            break;
        case SP_LOAD_4:
            handleLoadGame(src, 4);
            src->activeWin = SP_GAME_WINDOW_ACTIVE;
            break;
        case SP_LOAD_5:
            handleLoadGame(src, 5);
            src->activeWin = SP_GAME_WINDOW_ACTIVE;
            break;
        default:
            break;
    }
    return SP_MANAGER_NONE;
}


SP_MANAGER_EVENT spManagerHandleEvent(SPGuiManager *src, SDL_Event *event) {
    if (src == NULL || event == NULL) {
        return SP_MANAGER_NONE;
    }
    SP_MAIN_EVENT mainEvent;
    SP_SETTINGS_EVENT settingsEvent;
    SP_GAME_EVENT gameEvent;
    SP_LOAD_EVENT loadEvent;
    switch (src->activeWin) {
        case SP_MAIN_WINDOW_ACTIVE:
            mainEvent = spMainWindowHandleEvent(event);
            return handleManagerDueToMainEvent(src, mainEvent);
        case SP_SETTINGS_WINDOW_ACTIVE:
            settingsEvent = spSettingsWindowHandleEvent(src->settingsWin, event);
            return handleManagerDueToSettingsEvent(src, settingsEvent);
        case SP_GAME_WINDOW_ACTIVE:
            gameEvent = spGameWindowHandleEvent(src->gameWin, src->game, event);
            return handleManagerDueToGameEvent(src, gameEvent);
        case SP_LOAD_WINDOW_ACTIVE:
            loadEvent = spLoadWindowHandleEvent(src->loadWin, event);
            return handleManagerDueToLoadEvent(src, loadEvent);
        default:
            break;
    }
    return SP_MANAGER_NONE;
}

