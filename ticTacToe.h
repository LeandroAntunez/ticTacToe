#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG		0

#define PLAYER 	 	1
#define COMPUTER	2

// The size of the playing board, the 'hash'.
#define MATRIX		9
#define MATRIX_SQRT	3

// ticTacToe.c
void play(void);
void start(void);

// draw.c
void welcome(void);
void setMoves(int, int, int);
void setComputerMove(int, int, int);
void writeMovesToGrid(void);
void drawGrid(void);
void clearScreen(void);
void writeRandomMove(int);
void writeHeadsOrTails(void);
void writeComputerWinsToss(void);
void writeYourMove(void);
void writeComputersMove(void);

//logic.c
void keepCount(void);
int getCount(void);
void yourMove(void);
void computerMove(void);
int headsOrTails(void);
int coinToss(void);
void computerWinsToss(void);
void randomMove(void);
void waitFor(unsigned int);

