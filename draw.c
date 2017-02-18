/*
 ============================================================================
 Name        : draw.c
 Author      : Iain Hill
 Version     : 1
 Copyright   : GPL
 Description : naughts and crosses / tic tac toe
 ============================================================================
 */
#include <stdio.h>
#include <sys/ioctl.h>
#include "ticTacToe.h"

#define OFFSET		35

/*
 * The grid, quoi ...
 */
static int grid[6][13] =
{
	{ '\t', ' ', ' ', 'a', ' ', ' ', ' ', 'b', ' ', ' ', ' ', 'c', ' ' },
	{ '\t', '1', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ' },
	{ '\t', ' ', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
	{ '\t', '2', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ' },
	{ '\t', ' ', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
	{ '\t', '3', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ' }
};

/*
 * The headding what!
 */
void ticTacToe()
{
	puts(" _   _     _____         _____           ");
	puts("| |_(_) __|_   _|_ _  __|_   _|__   ___  ");
	puts("| __| |/ __|| |/ _` |/ __|| |/ _ \\ / _ \\ ");
	puts("| |_| | (__ | | (_| | (__ | | (_) |  __/ ");
	puts(" \\__|_|\\___||_|\\__,_|\\___||_|\\___/ \\___| ");
	puts("\n");
}

/*
 * Translates the store moves which are recorded in the moves array in the file
 * logic.c into the values displayed on screen in the grid array, found above.
 */
void writeMoves(int *moves)
{
	// map the 3*3 grid into the graphical display
	int map[9] = { 16, 20, 24, 42, 46, 50, 68, 72, 76 };

	for (int i = 0; i < 9; i++) {

		if (*(moves+i) == 1)
		{
			*(*grid+*(map+i)) = 'O';
		}
		else if (*(moves+i) == 2)
		{
			*(*grid+*(map+i)) = 'X';
		}
		else if (*(moves+i) == 0)
		{
			*(*grid+*(map+i)) = ' ';
		}
	}
}

/*
 * Write the grid array to screen.
 */
void drawGrid(int player)
{
	clearScreen();
	ticTacToe();

	if (DEBUG)
		printDebugMoves(player);

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 13; j++)
			printf("%c",grid[i][j]);
		puts("");
	}
	puts("\n");
}

/*
 * As its name sudgests, this function clears the screen between player moves.
 */
void clearScreen()
{
	struct winsize max;
	ioctl(0, TIOCGWINSZ , &max);

	for (int i = 0; i < max.ws_row; i++)
	       puts("\n");
}

/*
 * The wordy part, this function sends all the programs text phrases to the
 * screen, just at the approprate moment in the code, at times creating the
 * illusion of an opponet, whan ther is not realy anyone there, other than the
 * poor NSA operative, who has had the misfortune of being asigned to your sad
 * dilluded arse. Clever stuff this programming thingy, you could get your self
 * in to hot water with this stuff, it is that civilised.
 */
void sysOut(int write, int player) {
	/* 
	 * If player is > 0 then -1, this corrects the value of 'player' for
	 * use in the printf statment, when the output is player dependant. 
	 */
	if (player) player = player - 1;

	char* text[9] = {
		"Congratulations, you are the winner!\n",	// 0
		"I am the winner, better luck next time ...\n",	// 1
		"Stalemate, nobody wins ...\n",			// 2
		"Would you like to play again? ",		// 3
		"Please choose, heads or tails 'h' or 't' ?\n",	// 4
		"You have won the the toss.\n",			// 5		
		"The computer wins the toss.\n",		// 6
		"It is your move ...\n",			// 7
		"My turn, now then, let me see ...\n"		// 8
	};

	printf("%s", text[ write + (player) ]);
}
