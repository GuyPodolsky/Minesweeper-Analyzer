
#include "Q3.h"

/*This function will find all possible paths from a start position using the moves array and board (Q3)*/
pathTree findAllPossiblePaths(boardPos start, movesArray** moves, char** board) {
	pathTree res;										//variable declaration
	res.head = findAllPosPathsRec(start, moves, board);	//gets the head of the pathsTree
	return res;											//returns the result
}//findAllPossiblePaths

/*Recursion of find all possible paths*/
treeNode* findAllPosPathsRec(boardPos start, movesArray** moves, char** board) {
	unsigned int i, r = start[R] - 'A', c = start[C] - 1;						//variables declaration and initialization
	boardPos newPos;
	treeNodeListCell* KeepHead = NULL;
	static char** indicatorsBoard = NULL;
	static char** OriginalBoard = NULL;
	if (board != NULL) {														//static variables initialization
		OriginalBoard = board;														//keeps the board
		indicatorsBoard = boardCpy(OriginalBoard, ROWS, COLS);						//creates a copy of the board that will act as board of indicators.
	}//if
	if (!isValid(OriginalBoard, ROWS, COLS, r, c))								//check if the start position is valid;
		return NULL;
	indicatorsBoard[r][c] = ASTERISK;											//signs the current position to prevent a creation of a loop
	treeNode* node = createTreeNode(start, NULL);								//allocates memory to node.
	generalCheck(node, 'a');													//checks if the allocation went well.
	if (moves[r][c].size == 0)													//checks if their is moves.
		return node;
	for (i = 0; i < moves[r][c].size; i++) {
		newPos[R] = r + moves[r][c].moves[i].rows;										//calculates the new position in the board.
		newPos[C] = c + moves[r][c].moves[i].cols;
		if (isValid(indicatorsBoard, ROWS, COLS, newPos[R], newPos[C])) {					//if the new Position is valid;
			indicatorsBoard[newPos[R]][newPos[C]] = ASTERISK;								//signs the current position to prevent a creation of a loop.
			newPos[R] += 'A';
			newPos[C] += 1;
			if (node->next_possible_positions == NULL){										//in case, this is the first possible move, adds this move as the head of the list of possible moves.
				node->next_possible_positions = createTreeListCell(findAllPosPathsRec(newPos, moves, NULL), NULL);
				KeepHead = node->next_possible_positions;
			}//if
			else {																			//in case, this isn't the first possible move, adds the move to the end of the list.
				node->next_possible_positions->next = createTreeListCell(findAllPosPathsRec(newPos, moves, NULL), NULL);
				node->next_possible_positions = node->next_possible_positions->next;
			}//else
		}//if
	}//for
	if (board != NULL)															//if this is the end of the first iteration
		freeBoard(indicatorsBoard);													//releases the memory allocation of indicatorsBoard
	node->next_possible_positions = KeepHead;									//restores the head of the possible moves list
	return node;																//returns the result.
}//findAllPosPathsRec

/*This function will create a tree list node and will link it to the next cell*/
treeNodeListCell* createTreeListCell(treeNode* node, treeNodeListCell* next) {
	//Creating a cell
	treeNodeListCell* res = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	//Checking the allocation
	generalCheck(res, 'a');
	//Linking and putting variables in
	res->node = node;
	res->next = next;
	//Returns the new node
	return res;
}//createTreeListCell

/*This function will create a tree node*/
treeNode* createTreeNode(boardPos pos, treeNodeListCell* nextPPos) {
	treeNode* res = (treeNode*)malloc(sizeof(treeNode));	//allocates memory to res
	generalCheck(res, 'a');									//checks if the allocation went well.
	res->position[R] = pos[R];								//initializes the node's position.
	res->position[C] = pos[C];
	res->next_possible_positions = nextPPos;				//initializes the node's treeNodeListCell.
	return res;												//returns the res.
}//createTreeNode

/*This function releases the memory allocation of a path tree*/
void freePathTree(pathTree* tree) {
	//Free using a recursion
	freePathTreeRec(tree->head);
}//freePathTree

/*This function is the release in recuresion*/
void freePathTreeRec(treeNode* node) {
	treeNodeListCell* tmp;											//Creating a temp
	if (node == NULL)												//Checking if null we either released all or there was nothing to release
		return;
	if (node->next_possible_positions == NULL) {					//Checking if we can release the node
		free(node);
		return;
	}
	do {															//We need to release the others before
		tmp = node->next_possible_positions->next;
		freePathTreeRec(node->next_possible_positions->node);
		node->next_possible_positions = tmp;
	} while (node->next_possible_positions != NULL);
}//freePathTreeRec




