//
// Created by Omer Koren & Ori Haviv 2017
//

#include "GuiGame.h"
#include "SPChessGUIManager.h"


int executeGuiGame() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) { //SDL2 INIT
        printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
        return 1;
    }

    SPGuiManager *manager = spManagerCreate();
    if (manager == NULL) {
        SDL_Quit();
        return 0;
    }
    SDL_Event event;
    while (1) {
        SDL_WaitEvent(&event);
        SP_MANAGER_EVENT status;
        status = spManagerHandleEvent(manager, &event);
        if (status == SP_MANAGER_QUTT) {
            break;
        } else {

            spManagerDraw(manager);

            if (status == SP_MANAGER_TIE) {
                showEndingMessageBox(2, manager);
                break;
            } else if (status == SP_MANAGER_WHITE_WON) {
                showEndingMessageBox(1, manager);
                break;
            } else if (status == SP_MANAGER_BLACK_WON) {
                showEndingMessageBox(0, manager);
                break;
            }
            if (manager->game != NULL && manager->checked == 1) {
                showCheckMessage(manager->game->currentPlayer);
                manager->checked = 0;
            }
        }
    }
    spManagerDestroy(manager);
    SDL_Quit();
    return 0;
}
