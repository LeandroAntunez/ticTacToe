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
void traslateCharForMove(int, int, int);
void printDebugMoves(void);
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
int  writeStatusToCell(int, int, int);
void waitFor(unsigned int);

// draw.c
void ticTacToe(void);
void writeMoves(int[][3]);
void drawGrid(int);
void clearScreen(void);
void textHeadsOrTails(void);
void textWhoWinsToss(int);
void textPlayersMove(int);

