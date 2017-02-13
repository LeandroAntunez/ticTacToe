/*
 ============================================================================
 Name        : ticTacToe.c
 Author      : Iain Hill
 Version     : 1
 Copyright   : GPL
 Description : naughts and crosses / tic tac toe
 ============================================================================
 */
#include "ticTacToe.h"

int main(void)
{
	start();
	play();
}

void play()
{
	int winner = 0;

	while(!winner)
	{
		drawGrid();
		yourMove();
		drawGrid();
		computerMove();
	}
}

void start()
{
	int choice;
	int coin;

	welcome();
	drawGrid();
	choice = headsOrTails();
	coin = coinToss();

	if (choice != coin) 
	{
		computerWinsToss();
	}
	else
		play();
}

