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
static int horizontal[2][3];
static int vertical[2][3];
static int diagonal[2][2];
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
	if (moves[y][x] == 1 || moves[y][x] == 2)
		return 0;
	else {
		moves[y][x] = player;
		return 1;
	}
}

void printDebugMoves(int player)
{
	int player1 = PLAYER1 - 1;
	int player2 = PLAYER2 - 1;

	/* Above the debug squares */
	printf("Moves made = %d\n", keepCount(0));
	printf("Player 1 status -> %d\n", player1status);
	printf("Player 2 status -> %d\n\n", player2status);
	/* The two matrices */
	for (int i = 0; i < M_SQRT; i++) {
		/* Player one */
		printf(" |");
		for (int j = 0; j < M_SQRT; j++) {
			printf("%2d", moves[i][j]);
		}
		printf("|%2d\t", horizontal[player1][i]);
		/* Player two */
		printf(" |");
		for (int j = 0; j < M_SQRT; j++) {
			printf("%2d", moves[i][j]);
		}
		printf("|%2d", horizontal[player2][i]);
		puts("");
	}
	/* Beneath the two matrices */
	printf("  ------   \t  ------ \n");
	/* P1 status array */
	printf("%d ", diagonal[player1][1]);
	for (int i = 0; i < 3; i++)
		printf("%2d", vertical[player1][i]);
	printf(" %2d\t", diagonal[player1][0]);
	/* P1 status array */
	printf("%d ", diagonal[player2][1]);
	for (int i = 0; i < 3; i++)
		printf("%2d", vertical[player2][i]);
	printf(" %2d\t", diagonal[player2][0]);
	/* End of the line */
	puts("\n");
}

/*
 * Refresh recalculate redraw the grid, wash rinse and hang out to dry.
 */
int update(int player)
{
	int status;

	if (player) {
		status = calculateStatus(player);
		writeMoves(*moves);
	} else {
		clearStatusArrays(player);
		resetMoves();
	}
	drawGrid(player);

	return status;
}

/*
 * Ask player to input heads or tails.
 */
int headsOrTails()
{
	for(;;)
	{
		int c;
		int choice;
		sysOut(4, 0);
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

/*
 * Returns a 50 / 50 result, a virtual coin toss if you will humour me that,
 * about as random as a dice in space ...
 */
int coinToss()
{
	int coin;
	srand(time(NULL));
	coin = rand()%2;
	return coin;
}

/*
 * The Computer or player two starts the game.
 */
void computerWinsToss(int player)
{
	computerMove(player);
	update(player);
	sysOut(4, player);
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
	sysOut(7, player);

	int x;
	int y;
	int c;
	int i = 0;

	int a;
	int b;

	// Do not accept '\n' until two char are entered.
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

	// Write to the moves array.
	if (!traslateCharForMove(x, y, player)) {
		yourMove(player);
		return 0;
	}

	keepCount(1);
	
	status = update(player);
	player1status = status;
	return status;
}

/*
 * The twisted logic of my first ever AI, call me 'Frankenstein' if you will
 * but I shall have the last laugh yet. [Evil laughter ensues, scene fades to
 * black]
 */ 
int computerMove(int player)
{
	int status;
	status = update(player);
	player2status = status;
	sysOut(7, player);
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
		default:
			break;
	}
	keepCount(1);

	status = update(player);
	player2status = status;
	return status;
}

/*
 * A totally random move which uses no logic other than how many spaces remain
 * after how many moves, the square is chosen on a 1..n random basis where n
 * is the number of empty squares remaining.
 */
int randomMove(int player)
{
	/*
	 * Generate randomly the choice of the next move.
	 */
	int movesLeft;
	int choice;
	srand(time(NULL));

	// Get the quantity of spaces left remaining.
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
	 * Count empty squares until move selection is reached.
	 */
	int count = 1;

	for (int i = 0; i < M_SQRT; i++) {
		for (int j = 0; j < M_SQRT; j++)
		{
			if ( (moves[i][j] != 1) && (moves[i][j] != 2) )
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

/*
 * Erases the arrays which store each players game status; Called between 
 * games.
 */
void clearStatusArrays(int whichArraySet)
{
	for (int i = 0; i < 2*M_SQRT; i++) {
		*(*horizontal+i) = 0;
		*(*vertical+i) = 0;
	}

	for (int i = 0; i < 4; i++)
		*(*diagonal+i) = 0;
}

/*
 * Fills the status arrays which are then in turn used to calculate the AI's
 * next move, first scanning the status of each horizontal row, then the
 * vertical column and finally the two diagonals. 
 */
int calculateStatus(int player)
{
	int playerMod;
	int state;
	int marker;
	int i;
	int j;
	int x;
	state = marker = x = 0;

	// Player indices rectified for array index.
	playerMod = player - 1;

	// Horizontal status
	for (i = 0; i < M_SQRT; i++) {
		for (j = 0; j < M_SQRT; j++)
		{
			if (moves[i][j] == player)
			{
				x = readLineStatus(j, x);
			}
			else if ((moves[i][j] == 1) || (moves[i][j] == 2))
			{
				x = 8;
				break;
			}
		}
		horizontal[playerMod][i] = x;
		marker = getStatusValue(x);
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
			else if ((moves[i][j] == 1) || (moves[i][j] == 2))
			{
				x = 8;
				break;
			}
		}
		vertical[playerMod][j] = x;
		marker = getStatusValue(x);
		if (marker > state) {
			state = marker;
		}
		x = 0;
	}

	// Diagonal one
	for (i = 0; i < 3; i++)
	{
		if (moves[i][i] == player)
		{
			x = readLineStatus(i, x);
		}
		else if ((moves[i][i] == 1) || (moves[i][i] == 2))
		{
			x = 8;
			break;
		}
	}
	diagonal[playerMod][0] = x;
	marker = getStatusValue(x);
	if (marker > state) {
		state = marker;
	}

	x = 0;
	j = 0;

	// Diagonal two
	for (i = 2; i >= 0; i--)
	{
		if (moves[i][j] == player)
		{
			x = readLineStatus(i, x);
		}
		else if ((moves[i][j] == 1) || (moves[i][j] == 2))
		{
			x = 8;
			break;
		}
		j++;
	}
	diagonal[playerMod][1] = x;
	marker = getStatusValue(x);
	if (marker > state) {
		state = marker;
	}
	x = 0;
	return state;
}

/*
 * This function is used by the previous one to count this places filled by each
 * opponents moves. A value is ascribed to x dependant upon the 'geometry' of
 * the move, that is to say it position in a binary row, the value returned is
 * defined by this position, in the same manor that a value is ascribed to a
 * bit in binary notation.
 */
int readLineStatus(int j, int x)
{
	/*
	 * Use 3 bit binary pattern to read row state.
	 * 000 -> 0
	 * 001 -> 1
	 * 010 -> 2
	 *  ...
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

/*
 * The final count of each rows logic is given here, this value allows the
 * computer to understand the state of each row. This value is used in the
 * computation of the computers next move when the difficulty is set to the
 * higher or the intermediate value.
 */
int getStatusValue(int x)
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

