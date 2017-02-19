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

#define RESET	0

#define WIN		4
#define STALE_MATE	5

int main(void)
{
/*
 * Value 1 represents the initial condition, any subsequent calls to play() can
 * be made with other values, to enable the storing of variables between games
 * and also to permit the launching of different commands upon the games first
 * launch.
 */
	play(1);
	return EXIT_SUCCESS;
}

/*
 * Oh dear, what a mess this first function turned into, hmm ... One of those
 * 'things to do' that you keep ignoring, the tangled mess that is the
 * beginning of this programs, bears witness to code which has yet to come; that
 * is my excuse, if you are buying.
 */
void play(int firstRun)
{
	int choice;
	int coin;
	int winner;
	int status;
	winner = 0;

	while(!winner)
	{
		while (firstRun)
		{
/*
 * update refreshes the graphical display, the int entered represents the
 * player, 1 for player 1 and 2 for player 2, 0 initiates a total reset.
 */
			update(RESET);
/*
 * keepCount is used to infor the computer how many moves remain, this function
 * has several uses, each defined by the interger value entered.
 *
 * 0 -> return count
 * 1 -> count
 * 2 -> reset
 */
			keepCount(RESET);

			firstRun = 0;
			choice = headsOrTails();
			coin = coinToss();

			if (choice != coin) 
			{
				player2WinsToss(PLAYER2);
				break;
			}

			playet1WinsTheToss(PLAYER1);
		}

		status = yourMove(PLAYER1);
		if(status == WIN) {
			update(PLAYER1);
/*
 * This function is found at the end of draw.c, it is simply a text output to
 * screen, the first int defines the situation and the second the player, 0
 * being anyone and 1 and 2, player one and two consecutivly.
 */
			// You win.
			sysOut(0, 0);
			winner = 1;
		}
		else if (status == STALE_MATE)
		{
			update(PLAYER1);
			// Stale-mate
			sysOut(2, 0);
			winner = 1;
		}

		if(!winner)
			status = computerMove(PLAYER2);
		if(status == WIN && !winner) {
			update(PLAYER2);
			// I win.
			sysOut(1, 0);
			winner = 1;
		} else if (status == STALE_MATE) {
			update(PLAYER1);
			// Stale-mate
			sysOut(2, 0);
			winner = 1;
		}


		if(winner)
		{
			// Play again?
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

