CC = gcc
OBJS = main.o chessParser.o SPArrayList.o fileHandler.o chessGame.o \
SPMiniMaxNode.o SPMiniMax.o SPMainAux.o consoleGame.o \
SPChessMainWin.o SPChessLoadWin.o SPChessSettingsWin.o \
SPChessGameWin.o SPChessGUIManager.o GuiGame.o

EXEC = chessprog
COMP_FLAG = -std=c99 -Wall -Wextra -Werror -pedantic-errors
SDL_COMP_FLAG = -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT
SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main -lm


all: $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o $(EXEC)
clean:
	rm -f *.o $(EXEC)
$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o $@

chessParser.o: chessParser.c chessParser.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

SPArrayList.o: SPArrayList.c SPArrayList.h chessParser.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

chessGame.o: chessGame.c chessGame.h SPArrayList.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

fileHandler.o: fileHandler.c fileHandler.h chessGame.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

SPMiniMaxNode.o: SPMiniMaxNode.c SPMiniMaxNode.h chessGame.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

SPMiniMax.o: SPMiniMax.c SPMiniMax.h SPMiniMaxNode.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

SPMainAux.o: SPMainAux.c SPMainAux.h SPMiniMax.h fileHandler.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

consoleGame.o: consoleGame.c consoleGame.h SPMainAux.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

SPChessMainWin.o: SPChessMainWin.c SPChessMainWin.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

SPChessLoadWin.o: SPChessLoadWin.c SPChessLoadWin.h SPMainAux.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

SPChessSettingsWin.o: SPChessSettingsWin.c SPChessSettingsWin.h SPMainAux.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

SPChessGameWin.o: SPChessGameWin.c SPChessGameWin.h SPMainAux.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

SPChessGUIManager.o: SPChessGUIManager.c SPChessGUIManager.h SPChessGameWin.h SPChessMainWin.h SPChessLoadWin.h SPChessSettingsWin.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

GuiGame.o: GuiGame.c GuiGame.h SPChessGUIManager.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

main.o: main.c GuiGame.h consoleGame.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c