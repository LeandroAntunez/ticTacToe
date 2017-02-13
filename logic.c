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
	int coin = coinToss();

	writeComputerWinsToss();
	waitFor(2); 

	if (coin == 1) {
		setMoves('b', '2', COMPUTER);
		keepCount();
	}
	else
		computerMove();

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
		if (i == 0)
			x = c;
		if (i == 1)
			y = c;
		i++;
	}
	putchar('\n');

	// Write to the moves array
	setMoves(x, y, PLAYER);
	keepCount();
}

void computerMove()
{
	writeComputersMove();
	waitFor(2); 
	randomMove();
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
	writeRandomMove(choice);
}	

void waitFor (unsigned int secs)
{
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}

