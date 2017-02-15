#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG	1

// ticTacToe.c
void play(void);
void player1Move(int);
void player2Move(int);
void start(void);

//logic.c
void keepCount(void);
int  getRemainingMoves(void);
void setMove(int, int, int);
void printMoves(void);
void refreshMoves(int);
void callWriteMoves(void);
int  headsOrTails(void);
int  coinToss(void);
void computerWinsToss(int);
int  yourMove(int);
int  computerMove(int);
int  randomMove(int);
int  calculatedMove(int, int);
int  calculateStatus(int);
int  readLineStatus(int, int);
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

