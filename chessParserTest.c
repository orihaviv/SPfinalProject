//
// Created by אורי חביב on 05/09/2017.
//
#include "chessParser.h"

void testerForParser() {
    SPCommand cmd;
    cmd = spParserParseLine("game_mode 0");
    if (cmd.cmd != INVALID) { printf("Error 1\n"); }

    cmd = spParserParseLine("game_mode 1");
    if (cmd.cmd != GAME_MODE || cmd.arg != 1) { printf("Error 2\n"); }

    cmd = spParserParseLine("difficulty 5");
    if (cmd.cmd != INVALID) { printf("Error 3\n"); }

    cmd = spParserParseLine("difficulty 0");
    if (cmd.cmd != INVALID) { printf("Error 4\n"); }

    cmd = spParserParseLine("difficulty 3");
    if (cmd.cmd != DIFFICULTY || cmd.arg != 3) { printf("Error 5\n"); }

    cmd = spParserParseLine("user_color 3");
    if (cmd.cmd != INVALID) { printf("Error 6\n"); }

    cmd = spParserParseLine("user_color 1");
    if (cmd.cmd != USER_COLOR || cmd.arg != 1) { printf("Error 7\n"); }

    cmd = spParserParseLine("default 1");
    if (cmd.cmd != INVALID) { printf("Error 8\n"); }

    cmd = spParserParseLine("default");
    if (cmd.cmd != DEFAULT_GAME) { printf("Error 9\n"); }

    cmd = spParserParseLine("quit 1");
    if (cmd.cmd != INVALID) { printf("Error 10\n"); }

    cmd = spParserParseLine("quit");
    if (cmd.cmd != QUIT) { printf("Error 11\n"); }

    cmd = spParserParseLine("start 1");
    if (cmd.cmd != INVALID) { printf("Error 12\n"); }

    cmd = spParserParseLine("start");
    if (cmd.cmd != START) { printf("Error 13\n"); }

    cmd = spParserParseLine("move <8,A> <4,B>");
    if (cmd.cmd != INVALID) { printf("Error 14\n"); }

    cmd = spParserParseLine("move <9,A> to <4,B>");
    if (cmd.cmd != INVALID) { printf("Error 15\n"); }

    cmd = spParserParseLine("move <8,I> to <4,B>");
    if (cmd.cmd != INVALID) { printf("Error 16\n"); }

    cmd = spParserParseLine("move <8,A> to <9,B>");
    if (cmd.cmd != INVALID) { printf("Error 17\n"); }

    cmd = spParserParseLine("move <8,A> to <5,K>");
    if (cmd.cmd != INVALID) { printf("Error 18\n"); }

    cmd = spParserParseLine("move <8,A> to <5,A)");
    if (cmd.cmd != INVALID) { printf("Error 19\n"); }

    cmd = spParserParseLine("move <8,A> to <5.A>");
    if (cmd.cmd != INVALID) { printf("Error 20\n"); }

    cmd = spParserParseLine("move <8,A> to <5,C>");
    if (cmd.cmd != MOVE || cmd.source.row != 8 || cmd.destination.row != 5
        || cmd.source.column != 'A' || cmd.destination.column != 'C') { printf("Error 21\n"); }

    cmd = spParserParseLine("move <5,H> to <5,A>");
    if (cmd.cmd != MOVE || cmd.source.row != 5 || cmd.destination.row != 5
        || cmd.source.column != 'H' || cmd.destination.column != 'A') { printf("Error 22\n"); }

    cmd = spParserParseLine("reset 1");
    if (cmd.cmd != INVALID) { printf("Error 23\n"); }

    cmd = spParserParseLine("reset");
    if (cmd.cmd != RESET) { printf("Error 24\n"); }
}