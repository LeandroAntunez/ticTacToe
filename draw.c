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

#define GRID_HEIGHT	11

static int grid[6][13] =
{
	{  '\t',' ', ' ', 'a', ' ', ' ', ' ', 'b', ' ', ' ', ' ', 'c', ' ' },
	{  '\t','1', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ' },
	{  '\t',' ', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
	{  '\t','2', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ' },
	{  '\t',' ', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
	{  '\t','3', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ' }
};

static int moves[3][3] = {{0}};

void welcome()
{
	puts("\n");
	printf(" ~~~ Welcome to Tic'Tac'Toe ~~~\n");
	puts("\n");
}

/* TODO rename to setMove */
void setMoves(int x, int y, int marker)
{
	if 	(x == 97)
		x = 0;
	else if (x == 98)
		x = 1;
	else if (x == 99)
		x = 2;

	if	(y == 49)
		y = 0;
	else if (y == 50)
		y = 1;
	else if (y == 51)
		y = 2;

	moves[y][x] = marker;
}

void setComputerMove(int x, int y, int marker)
{
	moves[x][y] = marker;
}

void writeMovesToGrid()
{
	int x;
	int y;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			x = ((i+1)*2)-1;
			y = ((j+1)*4)-1;

			if (moves[i][j] == 1)
			{
				grid[x][y] = 'O';
			}
			else if (moves[i][j] == 2)
			{
				grid[x][y] = 'X';
			}
		}
}

void drawGrid()
{
	writeMovesToGrid();
	clearScreen();

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
	//printf ("lines %d\n", max.ws_row);
	//printf ("columns %d\n", max.ws_col);

	for (int i = 0; i < max.ws_row; i++)
	       puts("\n");
}

void writeRandomMove(int choice)
{
	int count = 1;

	for (int i = 0; i < MATRIX_SQRT; i++) {
		for (int j = 0; j < MATRIX_SQRT; j++) {
			if (moves[i][j] == 0) {
				if (DEBUG) printf("empty square %d %d\n", i, j);
				if (count == choice) {
					setComputerMove(i, j, COMPUTER);
					return;
				}	
				count++;
			}
		}
	}
}

void writeHeadsOrTails()
{
	printf("Please choose between 'h' for heads or 't' for tails: ");
}

void writeComputerWinsToss()
{
	printf("The computer wins the toss and will go first.\n");
	puts("\n");
}

void writeYourMove()
{
	printf("It is your move, please enter an a, b or c,\n");
	printf("followed by 1, 2, or 3: ");
}

void writeComputersMove()
{
	printf("My turn, now then, let me see ...\n");
	puts("\n");
}

