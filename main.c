

#include "consoleGame.h"
#include "GUI/GuiGame.h"

int main(int argc, char* argv[]) {
    if (argc == 0 || strcmp(argv[0], "-c") == 0){
    return executeConsoleGame();
    } else if (strcmp(argv[0], "-g")) {
        return executeGuiGame();
    }
}
