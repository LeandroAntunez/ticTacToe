#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG	0

#define PLAYER1	1
#define PLAYER2	2


// ticTacToe.c
void menu(void);
void play(int);

//logic.c
int  keepCount(int);
void resetMoves(void);
int  setLevel(int);
int  traslateCharForMove(int, int, int);
void printDebugMoves(int);
void refreshMoves(int);
int  updateGame(int);
int  headsOrTails(void);
int  coinToss(int);
void player2WinsToss(int);
void playet1WinsTheToss(int);
int  yourMove(int);
int  computerMove(int);
int  randomMove(int);
int  bestPossibleMove(int);
void clearNextMoves(void);
int  checkStaleMate(void);
void clearStatusArrays(int);
int  calculateStatus(int);
int  readLineStatus(int, int);
int  getStatusValue(int);
int  translateStatus(int, int, int);

// draw.c
void ticTacToe(void);
void writeGlyphToGrid(int*, int);
void writeMoves(int*);
void drawGrid(int);
void clearScreen(void);
void sysOut(int, int);

