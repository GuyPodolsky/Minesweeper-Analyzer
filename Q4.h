#ifndef Q4_H
#define Q4_H

///Including

#include "Q1.h"
#include "Q2.h"
#include "Q3.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

///Functions

movesList* findPathCoveringAllBoard(boardPos start, movesArray** moves, char** board);

moveCell* findthePathREC(int i_pos, int j_pos, moveCell* prev, movesArray** moves, char** board, int asterisks, int* isFine);

moveCell* getTail(moveCell* curr);

int countAsterisks(char** board);

void updateMoveCell(char row, char col, moveCell* curr, moveCell* next, moveCell* prev);

#endif
