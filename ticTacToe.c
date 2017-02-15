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

#define PLAYER 	 	1
#define COMPUTER	-1

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
		/* */
		player1Move(PLAYER);
		callWriteMoves();
		drawGrid();
		/* */
		player2Move(COMPUTER);
		callWriteMoves();
	}
}

void player1Move(int player)
{
	yourMove(player);
}

void player2Move(int player)
{
	computerMove(player);
}

void start()
{
	int choice;
	int coin;
	int player = COMPUTER;

	welcome();
	drawGrid();
	choice = headsOrTails();
	coin = coinToss();

	if (choice != coin) 
	{
		computerWinsToss(player);
	}
	else
		play();
}

