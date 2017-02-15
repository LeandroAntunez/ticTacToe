#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG		0

// ticTacToe.c
void play(void);
void player1Move(int);
void player2Move(int);
void start(void);

//logic.c
void keepCount(void);
void setMove(int, int, int);
void callWriteMoves(void);
int  headsOrTails(void);
int  coinToss(void);
void computerWinsToss(int);
void yourMove(int);
void computerMove(int);
void randomMove(int);
int  calculateStatus(int, int);
int  readLineStatus(int);
int  writeStatusToCell(int, int);
void waitFor(unsigned int);

// draw.c
void welcome(void);
void writeMoves(int[][3]);
void drawGrid(void);
void clearScreen(void);
void writeHeadsOrTails(void);
void playerWinsToss(int);
void writeYourMove(void);
void writeComputersMove(void);

