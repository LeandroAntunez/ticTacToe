/*
 ============================================================================
 Name        : logic.c
 Author      : Iain Hill
 Version     : 1
 Copyright   : GPL
 Description : naughts and crosses / tic tac toe
 ============================================================================
 */
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

static int movesMade;
static int moves[3][3] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
static int horizontal[3];
static int vertical[3];
static int diagonal[2];

int level = 1;


void keepCount()
{
	movesMade++;
}

int getRemainingMoves()
{
	return MATRIX - movesMade;
}

void traslateCharForMove(int x, int y, int player)
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

	// `x` here is `j` and `y` is `i` ...
	moves[y][x] = player;
}

void printDebugMoves()
{
	printf("Moves made = %d\n", movesMade);
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

void refreshMoves(int player)
{
	for (int i = 0; i < M_SQRT; i++) {
		for (int j = 0; j < M_SQRT; j++) {
			if ( (moves[i][j] != 1) && (moves[i][j] != -1) )
					moves[i][j] = 0;
		}
	}
}

void callWriteMoves()
{
	writeMoves(moves);
}

int headsOrTails()
{
	// Instantiate the move counter.
	movesMade = 0;

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
	textWhoWinsToss(player);
	computerMove(player);
}

int yourMove(int player)
{
	/*
	 * Request move from player, x can be either 1, 2 or 3
	 * an y a, b or c
	 */
	refreshMoves(player);
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

	// Inverse the cordinates if reasonable values.
	if ((x > 48 && x < 52) && (y > 96 && y < 100))
	{
		a = x;
		b = y;
		x = b;
		y = a;
	}
	// Repeat untill resonable values are entered ...
	else if ((x < 97 || x > 99) || (y < 49 || y > 51))
	{
		yourMove(player);
		return -1;
	}

	// Write to the moves array
	traslateCharForMove(x, y, player);
	keepCount();

	return calculateStatus(player);
}

int computerMove(int player)
{
	int status;

	refreshMoves(player);
	textPlayersMove(player);
	waitFor(2); 
	switch (level)
	{
		case 1:
			status = randomMove(player);
			break;
		case 2:
			status = calculatedMove(player, 0);
			break;
		case 3:
			status = calculatedMove(player, 1);
			break;
		default:
			break;
	}
	keepCount();
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

	movesLeft = getRemainingMoves();

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
					return calculateStatus(player);
				}
				count++;
			}
		}
	}
	printf("I can not move!\n");
	return -1;
}

int calculatedMove(int player, int level)
{
	int status;
	status = calculateStatus(player);

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
		default:
			break;
	}
	return calculateStatus(player);
}

int calculateStatus(int player)
{
	int state = 0;
	int marker;
	int i;
	int j;
	int x;
	state = x = 0;

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
		marker = writeStatusToCell(i, x, HORIZONTAL);
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
		marker = writeStatusToCell(j, x, VERTICAL);
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
	marker = writeStatusToCell(i, x, DIAGONAL1);
	if (marker > state) {
		state = marker;
	}
	x = 0;

	// Diagonal2
	for (i = 2; i >= 0; i--)
	{
		j = 0;

		if (moves[i][j] == player)
		{
			x = readLineStatus(j, x);
		}
		else if ((moves[i][j] == 1) || (moves[i][j] == -1))
		{
			x = 8;
			break;
		}
		j++;
	}
	diagonal[1] = x;
	marker = writeStatusToCell(i, x, DIAGONAL1);
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
		default:
			return x;
	}
	return -1;
}

int writeStatusToCell(int i, int x, int horizontal)
{
	// Act upon states 0 through 7
	//switch(x)
	//{
	//	case 0:
	//		// Empty row.
	//		return 1;
	//	case 1:
	//		if (horizontal) {
	//			if (moves[i][1] < NEXT) moves[i][1] = NEXT;
	//			if (moves[i][2] < NEXT) moves[i][2] = NEXT;
	//		}
	//		return 2;
	//	case 2:
	//		if (horizontal) {
	//			if (moves[i][0] < NEXT) moves[i][0] = NEXT;
	//			if (moves[i][2] < NEXT) moves[i][2] = NEXT;
	//		}
	//		return 2;
	//	case 3:
	//		if (horizontal) {
	//			if (moves[i][2] < TO_WIN) moves[i][2] = TO_WIN;
	//		}
	//		return 3;
	//	case 4:
	//		if (horizontal) {
	//			if (moves[i][0] < NEXT) moves[i][0] = NEXT;
	//			if (moves[i][1] < NEXT) moves[i][1] = NEXT;
	//		}
	//		return 2;
	//	case 5:
	//		if (horizontal) {
	//			if (moves[i][1] < TO_WIN) moves[i][1] = TO_WIN;
	//		}
	//		return 3;
	//	case 6:
	//		if (horizontal) {
	//			if (moves[i][0] < TO_WIN) moves[i][0] = TO_WIN;
	//		}
	//		return 3;
	//	case 7:
	//		// Player wins!
	//		return 4;
	//	default:
	//		// Opponent present.
	//		return 0;

	//}
	return -1;
}

void waitFor (unsigned int secs)
{
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}

