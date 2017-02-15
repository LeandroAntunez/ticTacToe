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
	{  '\t',' ', ' ', 'a', ' ', ' ', ' ', 'b', ' ', ' ', ' ', 'c', ' ' },
	{  '\t','1', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ' },
	{  '\t',' ', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
	{  '\t','2', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ' },
	{  '\t',' ', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
	{  '\t','3', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ' }
};

void ticTacToe()
{
	puts("\n");
	printf(" ~~~    Tic'Tac'Toe    ~~~\n");
	puts("\n");
}

void writeMoves(int moves[][3])
{
	int x;
	int y;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			x = ((i+1)*2)-1;
			y = ((j+1)*4)-1;

			if (moves[i][j] == 1) {

				grid[x][y] = 'O';
			}
			else if (moves[i][j] == -1) {

				grid[x][y] = 'X';
			}
		}
	}
}

void drawGrid(int player)
{
	clearScreen();
	ticTacToe();
	callWriteMoves();
	calculateStatus(player);

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
	//printf ("lines %d\n", max.ws_row);
	//printf ("columns %d\n", max.ws_col);
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

