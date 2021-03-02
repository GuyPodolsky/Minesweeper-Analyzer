#ifndef Q6_H
#define Q6_H

///Including

#include "Q1.h"
#include "Q2.h"
#include "Q3.h"
#include "Q4.h"
#include "Q5.h"

#include <stdio.h>
#include <stdlib.h>


int checkAndDisplayPathFromFile(char* file_name, movesArray** moves, char** board);

boardPosArray* boardPosBinaryFileToBoardPosArr(char* file_name);

bool isFileEmpty(char* file_name);

bool isFileExists(char* file_name);

bool isPosInPosArr(boardPos pos, boardPos* posArr, unsigned int size);

movesList* isPositionsConnected(boardPosArray* posArr, movesArray** moves, char** board);

int getMoveListLen(movesList* moves);

int getMoveListLenRec(moveCell* head);

moveCell* createMoveCell(moveCell* prev, Move move, moveCell* next);

void freeMovesList(movesList* lst);

void freeBoradPosArr(boardPosArray** arr);

#endif
