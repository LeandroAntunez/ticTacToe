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

static int moveCounter;
static int oponentSkill = 1;

void keepCount()
{
	moveCounter++;
}

int getRemainingMoves()
{
	return MATRIX - moveCounter;
}

int headsOrTails()
{
	// Instantiate the move counter.
	moveCounter = 0;

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

void computerWinsToss()
{
	int coin;
	writeComputerWinsToss();
	waitFor(2); 

	switch (oponentSkill)
	{
		case 1:
			// Random move
			computerMove();
			break;
		case 2:
			// 50/50 chance that he takes the middle, else random.
			coin = coinToss();
			if (coin == 1) {
				setMove('b', '2', COMPUTER);
				keepCount();
			}
			else
				computerMove();
			break;
		case 3:
			// Will take the middle evey time.
			setMove('b', '2', COMPUTER);
			break;
		default :
			break;
	}
	play();
}

void yourMove()
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
	putchar('\n');

	int a;
	int b;

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
		yourMove();
		return;
	}

	// Write to the moves array
	setMove(x, y, PLAYER);
	keepCount();
}

void computerMove()
{
	writeComputersMove();
	waitFor(2); 
	switch (oponentSkill)
	{
		case 1:
			randomMove();
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
	}
	keepCount();
}

void randomMove()
{
	/*
	 * Generate randomly the number of the next move.
	 */
	int movesLeft;
	movesLeft = getRemainingMoves();
	if (DEBUG) printf("moves left ---> %d\n", movesLeft);

	int choice;
	srand(time(NULL));
	if (movesLeft > 1) {
		choice = rand()%(movesLeft-1);
		choice++;
	}
	else 
		choice = 1;

	if (DEBUG) printf("Choice     ---> %d\n\n", choice);
	makeRandomMove(choice);
}	

void calculatedMove()
{
	int *ptr;
	ptr = getMoves();
	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			
			ptr++;
		}
		putchar('\n');
	}
	putchar('\n');

	//checkWinningMove();
}

void waitFor (unsigned int secs)
{
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}

