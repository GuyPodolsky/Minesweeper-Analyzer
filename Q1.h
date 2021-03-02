#ifndef Q1_H
#define Q1_H

///Including

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


///Defining + Board setting

#define ROWS 4 //M
#define COLS 5 //N
#define R 0	//Row
#define C 1 //Column
#define ASTERISK 'a'
#define HASHTAG 'h'
#define SPACE 's'

///Typedefs

//BoardPos
typedef char boardPos[2];

//Move
typedef struct _move
{
	char rows, cols;
} Move;
//Move array
typedef struct _movesArray
{
	unsigned int size;
	Move* moves;
} movesArray;

//Board position

typedef struct _boardPosArray
{
	unsigned int size;
	boardPos* positions;
} boardPosArray;

///Functions

boardPosArray** validMoves(movesArray** moves, char** board);

bool isOutOfBoard(const unsigned int rows, const unsigned int cols, unsigned int rPos, unsigned int cPos);

bool isAsterisk(const char ch);

bool isValid(char** board, unsigned int rows, unsigned int cols, unsigned int rPos, unsigned int cPos);

void removeInvalidMoves(int* invalidMovesIndexArr, unsigned int* size, Move* move);

void generalCheck(const void* pointer, const char flag);

#endif

