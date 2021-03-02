
#include "Q4.h"

/*This function will find a path covering the entire board (Q4)*/
movesList* findPathCoveringAllBoard(boardPos start, movesArray** moves, char** board) {
	int i, j, asterisksCount, isFine;													//Declaring variables
	i = start[R] - 'A';																	//Initializing variables
	j = start[C] - 1;
	asterisksCount = countAsterisks(board);												//Numbers of asterisks on board
	if (asterisksCount == ROWS * COLS)
		return NULL;
	isFine = 0;																			//to see if its the right path //1 = good 0 = bad
	validMoves(moves, board); 															//Deleting illegal moves
	movesList* lst = (movesList*)malloc(sizeof(movesList));								//Setting list
	//Checking
	generalCheck(lst, 'a');
	lst->head = findthePathREC(i, j, NULL, moves, board, asterisksCount + 1, &isFine); //sending to recursion to find the right path
	lst->tail = getTail(lst->head);
	return lst;
}//findPathCoveringAllBoard

/*This function will find the path that covers the entire board in recursion*/
moveCell* findthePathREC(int i_pos, int j_pos, moveCell* prev, movesArray** moves, char** board, int asterisks, int* isFine)
{
	int k /*k represents the index*/, nextDirecionRow, nextDirecionCol; //Setting for next 
	moveCell* temp, * nextStep;
	if (asterisks == ROWS * COLS) {																							//Checks if we found a path
		*isFine = 1;
		return NULL;
	} else if ((board[i_pos][j_pos] == ASTERISK) || (moves[i_pos][j_pos].size == 0)) {											//Checks if the path is bad
		*isFine = 0;
		return NULL;
	}
	for (k = 0; k < moves[i_pos][j_pos].size; k++) {																			//Run on the moves array sets the next move and send to recursion
		board[i_pos][j_pos] = ASTERISK;
		nextDirecionRow = (int)moves[i_pos][j_pos].moves[k].rows;
		nextDirecionCol = (int)moves[i_pos][j_pos].moves[k].cols;
		nextStep = (moveCell*)malloc(sizeof(moveCell));
		generalCheck(nextStep, 'a');
		temp = findthePathREC(i_pos + nextDirecionRow, j_pos + nextDirecionCol, nextStep, moves, board, asterisks + 1, isFine);
		board[i_pos][j_pos] = SPACE;
		if (*isFine == 1) {																									//Checks if its a fine path
			updateMoveCell(nextDirecionRow, nextDirecionCol, nextStep, temp, prev);
			return nextStep;
		} else {
			free(nextStep);
			return NULL;
		}
	}
}//findthePathREC

/*This function gets the tail of a list*/
moveCell* getTail(moveCell* curr) {
	if (curr == NULL)
		return NULL;
	if (curr->next == NULL)
		return curr;
	return getTail(curr->next);
}//getTail

/*This function counts the amount of asterisks*/
int countAsterisks(char** board) {
	//Declaring variables
	int i, j, count;
	//Initialzing variables
	count = 0;
	//Counting the amount of asterisks
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {
			if (board[i][j] == ASTERISK) {
				count++;
			}
		}
	}
	return count; //How many asterisks
}//countUnavailablePos

/*This function updates the move cell*/
void updateMoveCell(char row, char col, moveCell* curr, moveCell* next, moveCell* prev) {
	curr->move.rows = row;
	curr->move.cols = col;
	curr->next = next;
	curr->prev = prev;
}//updateMoveCell
