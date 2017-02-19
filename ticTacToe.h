#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG	1

#define PLAYER1	1
#define PLAYER2	2


// ticTacToe.c
void play(int);

//logic.c
int  keepCount(int);
void resetMoves(void);
int  traslateCharForMove(int, int, int);
void printDebugMoves(int);
void refreshMoves(int);
int  update(int);
int  headsOrTails(void);
int  coinToss(void);
void player2WinsToss(int);
void playet1WinsTheToss(int);
int  yourMove(int);
int  computerMove(int);
int  randomMove(int);
int bestPossibleMove(int);
int checkStaleMate(void);
void clearStatusArrays(int);
int  calculateStatus(int);
int  readLineStatus(int, int);
int  getStatusValue(int);

// draw.c
void ticTacToe(void);
void writeGlyphToGrid(int*, int);
void writeMoves(int*);
void drawGrid(int);
void clearScreen(void);
void sysOut(int, int);

