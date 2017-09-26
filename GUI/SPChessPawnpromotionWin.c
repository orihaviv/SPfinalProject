//
// Created by אורי חביב on 25/09/2017.
//


#include "SPChessPawnpromotionWin.h"





SP_SETTINGS_EVENT showPromotionMessageBox ()
{
    const SDL_MessageBoxButtonData buttons[] = {
            { 0, 0, "Pawn" },
            { 1, 1, "Rook" },
            { 2, 2, "Knight" },
            { 3, 3, "Bishop" },
            { 4, 4, "Queen" },
    };
    const SDL_MessageBoxColorScheme colorScheme = {
            { /* .colors (.r, .g, .b) */
                    /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
                    { 192,   192,   192 },
                    /* [SDL_MESSAGEBOX_COLOR_TEXT] */
                    {   0, 0,   0 },
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
                    { 0, 0, 0 },
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
                    {   192,   192, 192 },
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
                    { 90,   139, 199 }
            }
    };
    const SDL_MessageBoxData messageboxdata = {
            SDL_MESSAGEBOX_INFORMATION, /* .flags */
            NULL, /* .window */     //TODO change to the game window as parent
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
        switch (buttonid){
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


