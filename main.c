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
	/*
	 * Value 1 represents the initial condition, any subsequent calls to
	 * play() can be made with other values, to enable the storing of
	 * variables between games and also to permit the launching of different
	 * commands upon the games first launch.
	 */
	play(1);
	return EXIT_SUCCESS;
}

/*
 * Oh dear, what a mess this first function turned into, hmm ... One of those
 * things to do that you keep ignoring, the tangled mess of a beginning of this
 * programs bears witness to code which has yet to appear, that is my excuse if
 * you are buying.
 */
void play(int firstRun)
{
	int choice;
	int coin;
	int winner;
	int player1;
	int player2;
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
				computerWinsToss(PLAYER2);
			}
		}

		player1 = yourMove(PLAYER1);
		if(player1 == 4) {
			update(PLAYER1);
			sysOut(0, 0);
			winner = 1;
		}

		if(!winner)
			player2 = computerMove(PLAYER2);
		if(player2 == 4 && !winner) {
			update(PLAYER2);
			sysOut(1, 0);
			winner = 1;
		}

		if(winner)
		{
			sysOut(3, 0);
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

