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
	play(1);

	return EXIT_SUCCESS;
}

void play(int firstRun)
{
	int choice;
	int coin;
	int winner;
	int player1 = PLAYER;
	int player2 = COMPUTER;
	player1 = player2 = winner = 0;

	while(!winner)
	{
		while (firstRun)
		{
			update(0);
			keepCount(2);

			firstRun = 0;
			choice = headsOrTails();
			coin = coinToss();

			if (choice != coin) 
			{
				computerWinsToss(COMPUTER);
			}
		}

		player1 = yourMove(PLAYER);
		if(player1 == 4) {
			update(PLAYER);
			sysOut(0, 0);
			winner = 1;
		}

		if(!winner)
			player2 = computerMove(COMPUTER);
		if(player2 == 4 && !winner) {
			update(COMPUTER);
			sysOut(1, 0);
			winner = 1;
		}

		if(winner)
		{
			sysOut(2, 0);
			int c;
			while ((c = getchar()) != '\n')
			{
				if(c == 'y') {
					winner = 0;
					firstRun = 1;
				}
				else if (c == 'n') {
					break;
				}
			}
			puts("");
		}
	}
}

