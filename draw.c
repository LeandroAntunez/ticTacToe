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
	{ '\t',' ', ' ', 'a', ' ', ' ', ' ', 'b', ' ', ' ', ' ', 'c', ' ' },
	{ '\t','1', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ' },
	{ '\t',' ', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
	{ '\t','2', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ' },
	{ '\t',' ', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
	{ '\t','3', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ' }
};

void ticTacToe()
{
	puts("\n");
	printf(" ~~~    Tic'Tac'Toe    ~~~\n");
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

void textHeadsOrTails()
{
	printf("Please choose, heads or tails h/t ?\n");
}

void textWhoWinsToss(int player)
{
	printf("The computer (player %d) wins the toss.\n", player);
}

void textPlayersMove(int player)
{
	if ( player == 1 )
	{
		printf("It is your move, please enter a set of coordinates.\n");
	}
	else if ( player == -1 )
	{
		printf("My turn, now then, let me see ...\n");
	}
}

