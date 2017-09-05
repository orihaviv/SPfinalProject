#include <stdio.h>
#include "chessParser.h"

int main() {
    SPCommand cmd;
    cmd = spParserParseLine("game_mode 0");
    if(cmd.cmd != INVALID){ printf("Error 1"); }
	
    cmd = spParserParseLine("game_mode 1");
    if(cmd.cmd != GAME_MODE || cmd.arg != 1){ printf("Error 2"); }
	
	cmd = spParserParseLine("difficulty 5");
	if(cmd.cmd != INVALID){ printf("Error 3"); }
	
	cmd = spParserParseLine("difficulty 0");
	if(cmd.cmd != INVALID){ printf("Error 4"); }
	
	cmd = spParserParseLine("difficulty 3");
	if(cmd.cmd != DIFFICULTY || cmd.arg != 3){ printf("Error 5"); }
	
	cmd = spParserParseLine("user_color 3");
	if(cmd.cmd != INVALID){ printf("Error 6"); }
	
	cmd = spParserParseLine("user_color 1");
    if(cmd.cmd != USER_COLOR || cmd.arg != 1){ printf("Error 7"); }
	
	cmd = spParserParseLine("default 1");
    if(cmd.cmd != INVALID){ printf("Error 8"); }
	
	cmd = spParserParseLine("default");
    if(cmd.cmd != DEFAULT_GAME){ printf("Error 9"); }
	
	cmd = spParserParseLine("quit 1");
    if(cmd.cmd != INVALID){ printf("Error 10"); }
	
	cmd = spParserParseLine("quit");
    if(cmd.cmd != QUIT){ printf("Error 11"); }
	
	cmd = spParserParseLine("start 1");
    if(cmd.cmd != INVALID){ printf("Error 12"); }
	
	cmd = spParserParseLine("start");
    if(cmd.cmd != QUIT){ printf("Error 13"); }
	
	cmd = spParserParseLine("move <8,A> <4,B>");
	if(cmd.cmd != INVALID){ printf("Error 14"); }
	
	cmd = spParserParseLine("move <9,A> to <4,B>");
	if(cmd.cmd != INVALID){ printf("Error 15"); }
	
	cmd = spParserParseLine("move <8,I> to <4,B>");
	if(cmd.cmd != INVALID){ printf("Error 16"); }
	
	cmd = spParserParseLine("move <8,A> to <9,B>");
	if(cmd.cmd != INVALID){ printf("Error 17"); }
	
	cmd = spParserParseLine("move <8,A> to <5,K>");
	if(cmd.cmd != INVALID){ printf("Error 18"); }
	
	cmd = spParserParseLine("move <8,A> to <5,A)");
	if(cmd.cmd != INVALID){ printf("Error 19"); }
	
	cmd = spParserParseLine("move <8,A> to <5.A>");
	if(cmd.cmd != INVALID){ printf("Error 20"); }
	
	cmd = spParserParseLine("move <8,A> to <5,C>");
	if(cmd.cmd != MOVE || cmd.source.row != 8 || cmd.destination.row != 5
	|| cmd.source.column != '!' || cmd.destination.column != 'C'){ printf("Error 22"); }
	
	cmd = spParserParseLine("move <5,H> to <5,A>");
	if(cmd.cmd != MOVE || cmd.source.row != 5 || cmd.destination.row != 5
	|| cmd.source.column != 'H' || cmd.destination.column != 'A'){ printf("Error 22"); }
	
	cmd = spParserParseLine("reset 1");
    if(cmd.cmd != INVALID){ printf("Error 23"); }
	
	cmd = spParserParseLine("reset");
    if(cmd.cmd != RESET){ printf("Error 24"); }                        
}
