#ifndef Q3_H
#define Q3_H

///Including

#include "Q1.h"
#include "Q2.h"

#include <stdio.h>
#include <stdlib.h>

///Typedefs
//Forward declaration
typedef struct _treeNodeCell treeNodeListCell;

//Tree node
typedef struct _treeNode
{
	boardPos position;
	treeNodeListCell* next_possible_positions;
}treeNode;
//Tree node cell
struct _treeNodeCell
{
	treeNode* node;
	struct _treeNodeListCell* next;
};
//Path tree
typedef struct _pathTree
{
	treeNode* head;
}pathTree;

///Functions

pathTree findAllPossiblePaths(boardPos start, movesArray** moves, char** board);

treeNode* findAllPosPathsRec(boardPos start, movesArray** moves, char** board);

treeNode* createTreeNode(boardPos pos, treeNodeListCell* nextPPos);

treeNodeListCell* createTreeListCell(treeNode* node, treeNodeListCell* next);

void freePathTree(pathTree* tree);

void freePathTreeRec(treeNode* node);

#endif
