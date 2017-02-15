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
static int oponentSkill = 1;
static int moves[3][3] = {{0}};


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

	switch (oponentSkill)
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

	do
	{
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

	return calculateStatus();
}

int computerMove(int player)
{
	int status;

	writeComputersMove();
	waitFor(2); 
	switch (oponentSkill)
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

	int state;
	int marker;
	int x;
	state = 0;

	for (int i = 0; i < M_SQRT; i++) {
		for (int j = 0; j < M_SQRT; j++)
		{
			if ((moves[i][j] != 1) && (moves[i][j] != -1)) {
				if (count == choice) {
					moves[i][j] = player;
					return calculateStatus(player);
				}
				count++;
			}
		}
	}
}

int calculatedMove(int player, int level)
{
	int status;
	status = calculateStatus();

	switch (status)
	{
		case 0: if (level == 0)
				randomMove();
			if (level == 1)
				randomMove();
			break;
		case 1: if (level == 0)
				randomMove();
			if (level == 1)
				randomMove();
			break;
		case 2: if (level == 0)
				randomMove();
			if (level == 1)
				randomMove();
			break;
		default:
			break;
	}
	return calculateStatus();
}

int calculateStatus(int player)
{
	int state;
	int marker;
	int x;
	state = 0;

	for (int i = 0; i < M_SQRT; i++) {
		for (int j = 0; j < M_SQRT; j++) {
			if (moves[i][j] == player )
			{
				/*
				 * Go get the line state ...
				 * Set the next move status markers.
				 */
				x = readLineStatus(j);
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
	}
	return status;
}

int readLineStatus(int j)
{
	int x;

	// Use 3 bit binary pattern to read row state.
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
}

int writeStatusToCell(int i, int x)
{
	// Act upon states 0 through 7 (Yes, just like unix file permissions).
	switch(x)
	{
		case 0:
			// Empty row.
			return 0;
		case 1:
			moves[i][1] = NEXT;
			moves[i][2] = NEXT;
			return 1;
		case 2:
			moves[i][0] = NEXT;
			moves[i][2] = NEXT;
			return 1;
		case 3:
			moves[i][2] = TO_WIN;
			return 2;
		case 4:
			moves[i][0] = NEXT;
			moves[i][1] = NEXT;
			return 1;
		case 5:
			moves[i][1] = TO_WIN;
			return 2;
		case 6:
			moves[1][0] = TO_WIN;
			return 2;
		case 7:
			// Player wins!
			return 3;
	}
}

void waitFor (unsigned int secs)
{
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}

