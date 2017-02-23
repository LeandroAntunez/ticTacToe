#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG	0

#define PLAYER1	1
#define PLAYER2	2


// ticTacToe.c
void menu(void);
void play(int firstRun);

//logic.c
int  keepCount(int option);
void keepScore(int player, int inc);
void resetMoves(void);
int  setLevel(int newLevel);
void winningLine(void);
int  traslateCharForMove(int x, int y, int player);
void printDebugMoves(int player);
void refreshMoves(int);
int  updateGame(int player);
int  headsOrTails(void);
int  coinToss(int howManySides);
void player2WinsToss(int player);
void playet1WinsTheToss(int player);
int  yourMove(int player);
int  computerMove(int player);
int  randomMove(int player);
int  bestPossibleMove(int player);
void clearNextMoves(void);
int  checkStaleMate(void);
void clearStatusArrays(int whichArraySet);
int  calculateStatus(int player);
int  readLineStatus(int j, int x);
int  getStatusValue(int x);
int  translateStatus(int state, int line, int player);

// draw.c
void ticTacToe(void);
void writeMoves(int *moves);
void writeGlyphToGrid(int* glyph, int j);
void scoreBarCharts(int score1, int score2);
void drawWinningLine(int line);
void drawGrid(int player);
void redrawGrid(int line);
void clearScreen(void);
void sysOutMenu(void);
void sysOut(int write, int player);

