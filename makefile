

COMP_FLAG = -std=c99 -Wall -Wextra -Werror -pedantic-errors

OUT_DIR = $(PWD)
EXEC = $(OUT_DIR)/chessprog
GUI_DIR = $(PWD)/gui

VPATH := $(GUI_DIR)

CONSOLE_OBJS = main.o CommandParsing.o GameAux.o GameMoves.o GameRepresentation.o \
GameStates.o MatchManagement.o Matrix.o MinMaxNode.o MinMaxTree.o MovesStack.o \
PieceRules.o Scoring.o XMLLoadParser.o XMLSaveParser.o mainConsole.o

GUI_OBJS = Widget.o GenericWindow.o WindowNode.o WindowsStack.o WelcomeWindow.o \
SettingsWindow.o LoadGamesWindow.o DifficultyWindow.o ColorWindow.o PiecesWidget.o \
GameAuxGUI.o GameWindow.o GuiManager.o mainGUI.o

SDL_COMP_FLAG = -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT
SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main






FLAGS = -c -std=c99 -pedantic-errors -Wall -Werror -g $(CFLAGS) $(SDL_FLAGS) -lm -D_REENTRANT
SDL_FLAGS = -I/usr/local/lib/sdl_2.0.5/include/SDL2

HFILES = chessGame.h chessParser.h consoleGame.h fileHandler.h SPArrayList.h SPMainAux.h SPMiniMax.h SPMiniMaxNode.h GUI/GuiGame.h GUI/SPChessGameWin.h GUI/SPChessGUIManager.h GUI/SPChessLoadWin.h SPChessMainWin.h SPChessSettingsWin.h

OBJECTS = chessGame.o chessParser.o consoleGame.o fileHandler.o SPArrayList.o SPMainAux.o SPMiniMax.o SPMiniMaxNode.o GUI/GuiGame.o GUI/SPChessGameWin.o GUI/SPChessGUIManager.o GUI/SPChessLoadWin.o SPChessMainWin.o SPChessSettingsWin.o

all: chessprog

clean:
	rm -r $(OBJECTS) chessprog

chessprog: $(OBJECTS)
	gcc -o chessprog $(OBJECTS) -lm -std=c99 -Wall -Wextra -Werror -pedantic-errors -g -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main
	
chessGame.o: chessGame.c $(HFILES)
	gcc $(FLAGS) chessGame.c -o chessGame.o

chessParser.o: chessParser.c $(HFILES)
	gcc $(FLAGS) chessParser.c -o chessParser.o

consoleGame.o: consoleGame.c $(HFILES)
	gcc $(FLAGS) consoleGame.c -o consoleGame.o

fileHandler.o: fileHandler.c $(HFILES)
	gcc $(FLAGS) fileHandler.c -o fileHandler.o

SPArrayList.o: SPArrayList.c $(HFILES)
	gcc $(FLAGS) SPArrayList.c -o SPArrayList.o

SPMainAux.o: SPMainAux.c $(HFILES)
	gcc $(FLAGS) SPMainAux.c -o SPMainAux.o

SPMiniMax.o: SPMiniMax.c $(HFILES)
    gcc $(FLAGS) SPMiniMax.c -o SPMiniMax.o

SPMiniMaxNode.o: SPMiniMaxNode.c $(HFILES)
    gcc $(FLAGS) SPMiniMaxNode.c -o SPMiniMaxNode.o

GUI/GuiGame.o: GUI/GuiGame.c $(HFILES)
    gcc $(FLAGS) GUI/GuiGame.c -o GUI/GuiGame.o

GUI/SPChessGameWin.o: GUI/SPChessGameWin.c $(HFILES)
    gcc $(FLAGS) GUI/SPChessGameWin.c -o GUI/SPChessGameWin.o

GUI/SPChessGUIManager.o: GUI/SPChessGUIManager.c $(HFILES)
    gcc $(FLAGS) GUI/SPChessGUIManager.c -o GUI/SPChessGUIManager.o

GUI/SPChessLoadWin.o: GUI/SPChessLoadWin.c $(HFILES)
    gcc $(FLAGS) GUI/SPChessLoadWin.c -o GUI/SPChessLoadWin.o

GUI/SPChessMainWin.o: GUI/SPChessMainWin.c $(HFILES)
    gcc $(FLAGS) GUI/SPChessMainWin.c -o GUI/SPChessMainWin.o

GUI/SPChessSettingsWin.o: GUI/SPChessSettingsWin.c $(HFILES)
    gcc $(FLAGS) GUI/SPChessSettingsWin.c -o GUI/SPChessSettingsWin.o

main.o: main.c $(HFILES)
	gcc $(FLAGS) -lm main.c -o main.o