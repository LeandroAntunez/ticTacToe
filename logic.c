/*
 ============================================================================
 Name        : logic.c
 Author      : Iain Hill
 Version     : 1
 Copyright   : GPL
 Description : naughts and crosses / tic tac toe
 ============================================================================
 */
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "ticTacToe.h"

// The size of the playing board, the 'hash'.
#define MATRIX	9
#define M_SQRT	3

#define NEXT	2
#define TO_WIN	3

#define HORIZONTAL	1
#define VERTICAL	0
#define DIAGONAL1	0
#define DIAGONAL2	0

static int moves[3][3] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
static int horizontal[3];
static int vertical[3];
static int diagonal[2];
static int player1status;
static int player2status;

int level = 1;


int keepCount(int option)
{
	static int movesMade = 0;
	if (option == 1) {
		movesMade++;
		return 0;
	} else if (option == 2) {
		movesMade = 0;
		return 0;
	} else {
		return movesMade;
	}
}

void resetMoves()
{
	for (int i = 0; i < MATRIX; i++)
		*(*moves+i) = 0;
	writeMoves(*moves);
}

int traslateCharForMove(int x, int y, int player)
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

	// !!! `x` here is `j` and `y` is `i` !!!
	if (moves[y][x] == 1 || moves[y][x] == -1)
		return 0;
	else {
		moves[y][x] = player;
		return 1;
	}
}

void printDebugMoves()
{
	printf("Moves made = %d\n", keepCount(0));
	printf("Player 1 status -> %d\n", player1status);
	printf("Player 2 status -> %d\n\n", player2status);
	for (int i = 0; i < M_SQRT; i++) {
		printf(" |");
		for (int j = 0; j < M_SQRT; j++) {
			printf("%2d", moves[i][j]);
		}
		printf("|%2d", horizontal[i]);
		puts("");
	}
	printf("  ------\n");
	printf("%d ", diagonal[1]);
	for (int i = 0; i < 3; i++)
		printf("%2d", vertical[i]);
	printf(" %2d", diagonal[0]);
	puts("\n");
}

int update(int player)
{
	int status;

	if (player) {
		status = calculateStatus(player);
		writeMoves(*moves);
	} else {
		clearStatusArrays();
		resetMoves();
	}
	drawGrid(player);

	return status;
}

int headsOrTails()
{
	for(;;)
	{
		int c;
		int choice;
		textHeadsOrTails();
		while ((c = getchar()) != '\n')
			choice = c;
		putchar('\n');

		if (choice == 'h')
			return 0;
		else if (choice == 't')
			return 1;
	}
	return -1;
}

int coinToss()
{
	int coin;
	srand(time(NULL));
	coin = rand()%2;
	return coin;
}

void computerWinsToss(int player)
{
	computerMove(player);
	update(player);
	textWhoWinsToss(player);
}

int yourMove(int player)
{
	/*
	 * Request move from player, x can be either 1, 2 or 3
	 * an y a, b or c
	 */
	int status;
	status = update(player);
	player1status = status;
	textPlayersMove(player);

	int x;
	int y;
	int c;
	int i = 0;

	int a;
	int b;

	while ((c = getchar()) != '\n') {
		if (i == 0 && c != '\n')
			x = c;
		if (i == 1 && c != '\n')
			y = c;
		i++;
	}

	// Inverse the coordinates if reasonable values.
	if ((x > 48 && x < 52) && (y > 96 && y < 100))
	{
		a = x;
		b = y;
		x = b;
		y = a;
	}
	// Repeat until reasonable values are entered ...
	else if ((x < 97 || x > 99) || (y < 49 || y > 51))
	{
		yourMove(player);
		return 0;
	}

	// Write to the moves array
	if (!traslateCharForMove(x, y, player)) {
		yourMove(player);
		return 0;
	}

	keepCount(1);
	
	status = calculateStatus(player);
	player1status = status;
	return status;
}

int computerMove(int player)
{
	int status;
	status = update(player);
	player2status = status;
	textPlayersMove(player);
	sleep(2);

	switch (status)
	{
		case 0: if (level == 0)
				randomMove(player);
			if (level == 1)
				randomMove(player);
			break;
		case 1: if (level == 0)
				randomMove(player);
			if (level == 1)
				randomMove(player);
			break;
		case 2: if (level == 0)
				randomMove(player);
			if (level == 1)
				randomMove(player);
			break;
		case 3: if (level == 0)
				randomMove(player);
			if (level == 1)
				randomMove(player);
			break;
		case 4:
			printf("Congratulations you are the winner!\n");
			break;
		default:
			break;
	}
	keepCount(1);

	status = calculateStatus(player);
	player2status = status;
	return status;
}

int randomMove(int player)
{
	/*
	 * Generate randomly the choice of the next move.
	 */
	int movesLeft;
	int choice;
	srand(time(NULL));

	// Get the quatity of spaces left remaining.
	movesLeft = MATRIX - keepCount(0);

	if (movesLeft > 1) {
		choice = rand()%(movesLeft-1);
		choice++;
	}
	else 
	{
		choice = 1;
	}

	/*
	 * Count empty squares untill move selection is reached.
	 */
	int count = 1;

	for (int i = 0; i < M_SQRT; i++) {
		for (int j = 0; j < M_SQRT; j++)
		{
			if ( (moves[i][j] != 1) && (moves[i][j] != -1) )
			{
				if (count == choice) {
					moves[i][j] = player;
				}
				count++;
			}
		}
	}
	return 0;
}

void clearStatusArrays()
{
	for (int i = 0; i < M_SQRT; i++) {
		*(horizontal+i) = 0;
		*(vertical+i) = 0;
	}

	for (int i = 0; i < 2; i++)
		*(diagonal+i) = 0;
}

int calculateStatus(int player)
{
	int state;
	int marker;
	int i;
	int j;
	int x;
	state = x = 0;

	clearStatusArrays();

	// Horizontal status
	for (i = 0; i < M_SQRT; i++) {
		for (j = 0; j < M_SQRT; j++)
		{
			if (moves[i][j] == player)
			{
				x = readLineStatus(j, x);
			}
			else if ((moves[i][j] == 1) || (moves[i][j] == -1))
			{
				x = 8;
				break;
			}
		}
		horizontal[i] = x;
		marker = writeStatus(x);
		if (marker > state) {
			state = marker;
		}
		x = 0;
	}

	// Vertical status
	for (j = 0; j < M_SQRT; j++) {
		for (i = 0; i < M_SQRT; i++)
		{
			if (moves[i][j] == player)
			{
				x = readLineStatus(i, x);
			}
			else if ((moves[i][j] == 1) || (moves[i][j] == -1))
			{
				x = 8;
				break;
			}
		}
		vertical[j] = x;
		marker = writeStatus(x);
		if (marker > state) {
			state = marker;
		}
		x = 0;
	}

	// Diagonal1
	for (i = 0; i < 3; i++)
	{
		if (moves[i][i] == player)
		{
			x = readLineStatus(i, x);
		}
		else if ((moves[i][i] == 1) || (moves[i][i] == -1))
		{
			x = 8;
			break;
		}
	}
	diagonal[0] = x;
	marker = writeStatus(x);
	if (marker > state) {
		state = marker;
	}

	x = 0;
	j = 0;

	// Diagonal2
	for (i = 2; i >= 0; i--)
	{
		if (moves[i][j] == player)
		{
			x = readLineStatus(i, x);
		}
		else if ((moves[i][j] == 1) || (moves[i][j] == -1))
		{
			x = 8;
			break;
		}
		j++;
	}
	diagonal[1] = x;
	marker = writeStatus(x);
	if (marker > state) {
		state = marker;
	}
	x = 0;
	return state;
}

int readLineStatus(int j, int x)
{
	/*
	 * Use 3 bit binary pattern to read row state.
	 * 000 -> 0
	 * 100 -> 1
	 * 010 -> 2
	 * ...
	 */
	switch(j)
	{
		case 0:
			x = x + 4;
			return x;
		case 1:
			x = x + 2;
			return x;
		case 2:
			x = x + 1;
			return x;
		default:
			return x;
	}
	return -1;
}

int writeStatus(int x)
{
	// Act upon states 0 through 7
	switch(x)
	{
		case 0:
			// Anyone's
			return 1;
		case 1:
			// Good move
			return 2;
		case 2:
			// Good move
			return 2;
		case 3:
			// Move to win
			return 3;
		case 4:
			// Good move
			return 2;
		case 5:
			// Move to win
			return 3;
		case 6:
			// Move to win
			return 3;
		case 7:
			// Player wins!
			return 4;
		case 8:
			// Opponent present.
			return 0;
		default:
			return 0;

	}
	return -1;
}

