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

static int grid[6][13] =
{
	{ '\t', ' ', ' ', 'a', ' ', ' ', ' ', 'b', ' ', ' ', ' ', 'c', ' ' },
	{ '\t', '1', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ' },
	{ '\t', ' ', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
	{ '\t', '2', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ' },
	{ '\t', ' ', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
	{ '\t', '3', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ' }
};

void ticTacToe()
{
	puts(" _   _     _____         _____           ");
	puts("| |_(_) __|_   _|_ _  __|_   _|__   ___  ");
	puts("| __| |/ __|| |/ _` |/ __|| |/ _ \\ / _ \\ ");
	puts("| |_| | (__ | | (_| | (__ | | (_) |  __/ ");
	puts(" \\__|_|\\___||_|\\__,_|\\___||_|\\___/ \\___| ");
	puts("\n");
}

void writeMoves(int *moves)
{
	// map the 3*3 grid into the graphical display
	int map[9] = { 16, 20, 24, 42, 46, 50, 68, 72, 76 };

	for (int i = 0; i < 9; i++) {

		if (*(moves+i) == 1)
		{
			*(*grid+(map[i])) = 'O';
		}
		else if (*(moves+i) == -1)
		{
			*(*grid+(map[i])) = 'X';
		}
		else if (*(moves+i) == 0)
		{
			*(*grid+(map[i])) = ' ';
		}
	}
}

void drawGrid(int player)
{
	clearScreen();
	ticTacToe();

	if (DEBUG)
		printDebugMoves();

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 13; j++)
			printf("%c",grid[i][j]);
		putchar('\n');
	}

	printf("\n\n");
}

void clearScreen()
{
	struct winsize max;
	ioctl(0, TIOCGWINSZ , &max);

	for (int i = 0; i < max.ws_row; i++)
	       puts("\n");
}

void sysOut(int write, int player)
{
	/* 
	 * If player is > 0 remove 1, this corrects the value  of player for
	 * the printf statment. 
	 */
	if (player)
		player = player - 1;

	char* text[8] = {
		"Congratulations, you are the winner!\n",	// 0
		"I am the winner better luck next time ...\n",	// 1
		"Would you like to play again? ",		// 2
		"Please choose, heads or tails h/t ?\n",	// 3
		"You have won the the toss.\n",			// 4		
		"The computer wins the toss.\n",		// 5
		"It is your move, please enter a set of coordinates.\n",//6
		"My turn, now then, let me see ...\n"		// 7
	};

	printf("%s", text[ write + (player) ]);
}
