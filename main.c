//
// Created by Omer Koren & Ori Haviv 2017
//

#include "consoleGame.h"
#include "GuiGame.h"

int main(int argc, char** argv) {
    if (argc > 2) {
        printf("Too many arguments\n");
        return 0;
    }
    if (argc == 1 || strcmp(argv[1], "-c") == 0){
        return executeConsoleGame();
    } else if (strcmp(argv[1], "-g") == 0) {
        return executeGuiGame();
    } else {
        printf("The expected arguments are '-c' or '-g'\n");
    }
    return 0;
}
