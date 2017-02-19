/*
 ============================================================================
 Name        : draw.c
 Author      : Iain Hill
 Version     : 1
 Copyright   : GPL
 Description : naughts and crosses / tic tac toe
 ============================================================================
     _   _     _____         _____           
    | |_(_) __|_   _|_ _  __|_   _|__   ___  
    | __| |/ __|| |/ _` |/ __|| |/ _ \ / _ \ 
    | |_| | (__ | | (_| | (__ | | (_) |  __/ 
     \__|_|\___||_|\__,_|\___||_|\___/ \___| 
    
 */
#include <stdio.h>
#include <sys/ioctl.h>
#include "ticTacToe.h"

#define OFFSET		35

/*
 * The grid, quoi ...
 */
static int grid[6][13] =
{
	{ '\t', ' ', ' ', 'a', ' ', ' ', ' ', 'b', ' ', ' ', ' ', 'c', ' ' },
	{ '\t', '1', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ' },
	{ '\t', ' ', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
	{ '\t', '2', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ' },
	{ '\t', ' ', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
	{ '\t', '3', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ' }
};

// 46 + 
//	
//	int map2[9] = { 46, 56, 67, 280, 290, 301, 514, 524, 535 };
static int bigScreen[19][39] =
{
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'a', ' ', ' ', ' ', ' ', ' ', '_', ' ', ' ', ' ', ' ', 'b', ' ', ' ', ' ', ' ', ' ', '_', ' ', ' ', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', '_', '_', '_', '_', '_', '_', '_', '_', '|', ' ', '|', '_', '_', '_', '_', '_', '_', '_', '_', '|', ' ', '|', '_', '_', '_', '_', '_', '_', '_', '_', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', '|', '_', '_', '_', '_', '_', '_', '_', '_', ' ', ' ', ' ', '_', '_', '_', '_', '_', '_', '_', '_', ' ', ' ', ' ', '_', '_', '_', '_', '_', '_', '_', '_', '|', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', '2', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', '_', '_', '_', '_', '_', '_', '_', '_', '|', ' ', '|', '_', '_', '_', '_', '_', '_', '_', '_', '|', ' ', '|', '_', '_', '_', '_', '_', '_', '_', '_', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', '|', '_', '_', '_', '_', '_', '_', '_', '_', ' ', ' ', ' ', '_', '_', '_', '_', '_', '_', '_', '_', ' ', ' ', ' ', '_', '_', '_', '_', '_', '_', '_', '_', '|', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', '3', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', '_', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', '_', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }
};

static int glyphX[4][7] =
{
	{ ' ', '_', '_', ' ', ' ', '_', '_'  },
	{ ' ', '\\',' ', '\\','/', ' ', '/'  },
	{ ' ', ' ', '>', ' ', ' ', '<', ' '  },
	{ ' ', '/', '_', '/', '\\','_', '\\' }
};

static int glyphO[4][7] =
{
	{ ' ', ' ', '_', '_', '_', ' ', ' ', },
	{ ' ', '/', ' ', '_', ' ', '\\',' ', },
	{ '|', ' ', '(', '_', ')', ' ', '|', },
	{ ' ', '\\','_', '_', '_', '/', ' ', }
};

static int glyphBlank[4][7] =
{
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', }
};

/*
 * The heading what!
 */
void ticTacToe()
{
	puts(" _   _     _____         _____ ");
	puts("| |_(_) __|_   _|_ _  __|_   _|__   ___");
	puts("| __| |/ __|| |/ _` |/ __|| |/ _ \\ / _ \\");
	puts("| |_| | (__ | | (_| | (__ | | (_) |  __/ ");
	puts(" \\__|_|\\___||_|\\__,_|\\___||_|\\___/ \\___|");
	puts("\n");
}

/*
 * Translates the stored moves which are recorded in the moves array in the file
 * logic.c into the values displayed on screen in the grid array, found above.
 */
void writeMoves(int *moves)
{
	// map the 3*3 grid into the graphical display
	int map1[9] = { 16, 20, 24, 42, 46, 50, 68, 72, 76 };
	int map2[9] = { 44, 55, 66, 278, 289, 300, 512, 523, 534 };

	for (int i = 0; i < 9; i++) {

		if (*(moves+i) == 1)
		{
			*(*grid+*(map1+i)) = 'O';
			writeGlyphToGrid(*glyphO, *(map2+i));
		}
		else if (*(moves+i) == 2)
		{
			*(*grid+*(map1+i)) = 'X';
			writeGlyphToGrid(*glyphX, *(map2+i));
		}
		else if (*(moves+i) == 0)
		{
			*(*grid+*(map1+i)) = ' ';
			writeGlyphToGrid(*glyphBlank, *(map2+i));
		}
	}
}

void writeGlyphToGrid(int* glyph, int j)
{
	//*(*bigScreen+s) = 'X';

	// Scroll through the glyph.
	for (int i = 0; i < 28; i++)
	{
		// If i is devisable exactly by 7, go to the next row.
		if (i % 7 == 0 && i != 0) {
			j = j + 32;
		}
		*(*bigScreen+j) = *(glyph+i);
		j++;
	}
}

/*
 * Write the grid array to screen.
 */
//void drawGrid(int player)
//{
//	clearScreen();
//	ticTacToe();
//
//	if (DEBUG)
//		printDebugMoves(player);
//
//	for (int i = 0; i < 6; i++) {
//		for (int j = 0; j < 13; j++)
//			printf("%c",grid[i][j]);
//		puts("");
//	}
//	puts("\n");
//}

/*
 * Write the grid array to screen.
 */
void drawGrid(int player)
{
	clearScreen();
	ticTacToe();

	if (DEBUG)
		printDebugMoves(player);

	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 39; j++)
			printf("%c",bigScreen[i][j]);
		puts("");
	}
	puts("\n");
}
/*
 * As its name suggests, this function clears the screen between player moves.
 */
void clearScreen()
{
	struct winsize max;
	ioctl(0, TIOCGWINSZ , &max);

	for (int i = 0; i < max.ws_row; i++)
	       puts("\n");
}

/*
 * The wordy part, this function sends all the programs text phrases to the
 * screen, just at the appropriate moment in the code, at times creating the
 * illusion of an opponent, when there is really no one there, other than the
 * poor NSA operative, who has had the misfortune of being assigned to your sad
 * deluded arse. Clever stuff this programming thingy, could get your self
 * in to hot water with it, it is that civilised.
 */
void sysOut(int write, int player) {
	/* 
	 * If player is > 0 then -1, this corrects the value of 'player' for
	 * use in the printf statement, when the output is player dependant. 
	 */
	if (player) player = player - 1;

	char* text[9] = {
		"Congratulations, you are the winner!\n",	// 0
		"I am the winner, better luck next time ...\n",	// 1
		"Stalemate, nobody wins ...\n",			// 2
		"Would you like to play again? ",		// 3
		"Please choose, heads or tails 'h' or 't' ?\n",	// 4
		"You have won the toss.\n",			// 5		
		"The computer wins the toss.\n",		// 6
		"It is your move ...\n",			// 7
		"My turn, now then, let me see ...\n"		// 8
	};

	printf("%s", text[ write + (player) ]);
}
