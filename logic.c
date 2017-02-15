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

static int movesMade;
static int moves[3][3] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };

int level = 1;


void keepCount()
{
	movesMade++;
}

int getRemainingMoves()
{
	return MATRIX - movesMade;
}

void setMove(int x, int y, int marker)
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

void printMoves()
{
	for (int i = 0; i < M_SQRT; i++) {
		for (int j = 0; j < M_SQRT; j++) {
			printf("%2d", moves[i][j]);
		}
		puts("");
	}
	puts("");
}

void refreshMoves(int player)
{
	for (int i = 0; i < M_SQRT; i++) {
		for (int j = 0; j < M_SQRT; j++) {
			if ( (moves[i][j] != 1) && (moves[i][j] != -1) )
					moves[i][j] = 0;
		}
	}
	calculateStatus(player);
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
		writeHeadsOrTails();
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
	int coin;
	playerWinsToss(player);
	waitFor(2); 

	switch (level)
	{
		case 1:
			// Random move
			computerMove(player);
			break;
		case 2:
			// 50/50 chance that he takes the middle, else random.
			coin = coinToss();
			if (coin == 1) {
				setMove('b', '2', player);
				keepCount();
			}
			else
				computerMove(player);
			break;
		case 3:
			// Will take the middle evey time.
			setMove('b', '2', player);
			keepCount();
			break;
		default :
			break;
	}
	play();
}

int yourMove(int player)
{
	/*
	 * Request move from player, x can be either 1, 2 or 3
	 * an y a, b or c
	 */
	refreshMoves(player);
	writeYourMove();

	int x;
	int y;
	int c;
	int i = 0;

	while ((c = getchar()) != '\n') {
		if (i == 0 && c != '\n')
			x = c;
		if (i == 1 && c != '\n')
			y = c;
		i++;
	}
	puts("\n\n");

	int a;
	int b;
	int again = 0;

	do {
		// Inverse the cordinates if reasonable values.
		if ((x > 48 && x < 52) && (y > 96 && y < 100))
		{
			a = x;
			b = y;
			x = b;
			y = a;

			again = 0;
		}
		// Repeat untill resonable values are entered ...
		else if ((x < 97 || x > 99) || (y < 49 || y > 51))
		{
			yourMove(player);
			again = 1;
		}
		else
		{
			again = 0;
		}
	} while (again);

	// Write to the moves array
	setMove(x, y, player);
	keepCount();

	return calculateStatus(player);
}

int computerMove(int player)
{
	int status;

	refreshMoves(player);
	writeComputersMove();
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
	int x;
	state = x = 0;

	for (int i = 0; i < M_SQRT; i++) {
		for (int j = 0; j < M_SQRT; j++)
		{
			if (moves[i][j] == player)
			{
				/*
				 * Go get the line state ...
				 * Set the next move status markers.
				 */
				x = readLineStatus(j, x);
			}
		}
		/* 
		 * Pass value of the above read (x) to set markers and retreive
		 * the current state of the line.
		 */
		marker = writeStatusToCell(i, x);
		if (marker > state) {
			// keep track of the highest state reached.
			state = marker;
		}
		// Reset x for the next lines values
		x = 0;
	}

	for (int j = 0; j < M_SQRT; j++) {
		for (int i = 0; i < M_SQRT; i++)
		{
			if (moves[i][j] == player)
			{
				/*
				 * Go get the line state ...
				 * Set the next move status markers.
				 */
				x = readLineStatus(j, x);
			}
		}
		/* 
		 * Pass value of the above read (x) to set markers and retreive
		 * the current state of the line.
		 */
		marker = writeStatusToCell(j, x);
		if (marker > state) {
			// keep track of the highest state reached.
			state = marker;
		}
		// Reset x for the next lines values
		x = 0;
	}
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
			x = x + 1;
			return x;
		case 1:
			x = x + 2;
			return x;
		case 2:
			x = x + 4;
		default:
			return x;
	}
	return -1;
}

int writeStatusToCell(int i, int x)
{
	// Act upon states 0 through 7 (Yes, just like unix file permissions).
	switch(x)
	{
		case 0:
			// Empty row.
			return 1;
		case 1:
			if (moves[i][1] < NEXT) moves[i][1] = NEXT;
			if (moves[i][2] < NEXT) moves[i][2] = NEXT;
			return 2;
		case 2:
			if (moves[i][0] < NEXT) moves[i][0] = NEXT;
			if (moves[i][2] < NEXT) moves[i][2] = NEXT;
			return 2;
		case 3:
			if (moves[i][2] < TO_WIN) moves[i][2] = TO_WIN;
			return 3;
		case 4:
			if (moves[i][0] < NEXT) moves[i][0] = NEXT;
			if (moves[i][1] < NEXT) moves[i][1] = NEXT;
			return 2;
		case 5:
			if (moves[i][1] < TO_WIN) moves[i][1] = TO_WIN;
			return 3;
		case 6:
			if (moves[i][0] < TO_WIN) moves[i][0] = TO_WIN;
			return 3;
		case 7:
			// Player wins!
			return 4;
	}
	return -1;
}

void waitFor (unsigned int secs)
{
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}

