#ifndef Q2_H
#define Q2_H

///Including

#include "Q1.h"
#include <stdio.h>
#include <stdlib.h>

///Typedefs

//ovecell
typedef struct _moveCell {
	Move move;
	struct _moveCell* next, * prev;
} moveCell;
//Move list
typedef struct _movesList {
	moveCell* head;
	moveCell* tail;
} movesList;

///Functions

int display(movesList* moves_list, boardPos start, char** board);

char** boardCpy(char** board, unsigned int rows, unsigned int cols);

void removeFromList(moveCell* toRemove);

void printBoard(char** board);

void printSeparationLine();

void printColumnHeaders();

char getCell(char** board, int row, int col);

void freeBoard(char** board);

#endif



















