#ifndef TEST_H
#define TEST_H

#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Q1.h"
#include "Q2.h"
#include "Q3.h"
#include "Q4.h"
#include "Q5.h"
#include "Q6.h"

char** initBoard();

void setCell(char** board, int row, int col, char sign);

void freeMovesArr(movesArray** moves);

void setAsterisks(char** board, unsigned int upperR, unsigned int upperC, unsigned int lower, char flag);

movesArray** setMovesArr(char** board,char flag);

void printMovesArr(movesArray** moves, char** board);

movesList* setMovesList(char flag);

void printMovesList(movesList* moves, char flag);

void printPathRec(treeNode* head,int degree);

void printPathTree(pathTree* path);

void print_binary(char c);

void printListToBinFileInBinary(char* file_name);

void printBoardPosArrayCell(boardPosArray* pos);

boardPosArray** setBoardPosArray(char flag);

void printBoardPosArray(boardPosArray** arr);

#endif
