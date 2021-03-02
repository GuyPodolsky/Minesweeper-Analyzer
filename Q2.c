
#include "Q2.h"

/*This function displays a movement made from a starting position using a move list we get,
it deletes moves that either return to a place we moved to before,
or if the move is invalid by moves definition (Q2)*/
int display(movesList* moves_list, boardPos start, char** board) {
	int  remCount = 0, stepCount = 0;						// Counting how many cells we removed and how many steps we made
	int i = start[R] - 'A', j = start[C] - 1;				// For position on board
	moveCell* head, * toRemove;								// Running on the list
	char** stepsBoard = boardCpy(board, ROWS, COLS);
	stepsBoard[i][j] = HASHTAG;
	if (moves_list == NULL || isAsterisk(board[i][j]))
		return 0;
	head = moves_list->head;
	while (head != NULL) {									//Running on list
		if (!isValid(stepsBoard, ROWS, COLS, i + head->move.rows, j + head->move.cols)) {
			if (head == moves_list->head)
				moves_list->head = head->next;
			if (head == moves_list->tail)
				moves_list->tail = head->prev;
			toRemove = head;
			head = head->next;
			removeFromList(toRemove);
			remCount++;
		} else {
			i += (int)(head->move.rows);
			j += (int)(head->move.cols);
			stepCount++;
			stepsBoard[i][j] = (char)stepCount;
			printBoard(stepsBoard);
			head = head->next;
		}//else
	}
	freeBoard(stepsBoard);
	return remCount;
}//display

/*This function will copy the board*/
char** boardCpy(char** board, unsigned int rows, unsigned int cols) {
	unsigned int i, j;									//Declaring variables
	char** res = (char**)malloc(rows * sizeof(char*)); 	//Creating a copy of board
	generalCheck(res, "a");								//Runs on rows and creates cols for it + copying the variables in the original board
	for (i = 0; i < rows; i++) {
		res[i] = (char*)malloc(cols * sizeof(char));
		generalCheck(res[i], "a");
		for (j = 0; j < cols; j++) {
			res[i][j] = board[i][j];
		}
	}
	return res;
}//boardCpy

/*This function removes moves cells from list, because they are invalid moves*/
void removeFromList(moveCell* toRemove) {
	if (toRemove->next != NULL)					//Checks and remove according to its place
		toRemove->next->prev = toRemove->prev;
	if (toRemove->prev != NULL)
		toRemove->prev->next = toRemove->next;
	free(toRemove);
}//removeFromList

void printBoard(char** board) {
	unsigned int i, j;				//Declaring variables
	char ch;
	printSeparationLine();			//Print what is needed
	printColumnHeaders();
	printSeparationLine();
	for (i = 0; i < ROWS; i++) {	//Print the letters and the board
		printf("| %c ", i + 'A');
		for (j = 0; j < COLS; j++) {
			ch = getCell(board, i, j);
			switch (ch) {
			case SPACE:
				printf("|  %c  ", ' ');
				break;
			case HASHTAG:
				printf("|  %c  ", '#');
				break;
			case ASTERISK:
				printf("|  %c  ", '*');
				break;
			default:
				if ((int)ch > 9)
					printf("| %d  ", (int)ch);
				else
					printf("|  %d  ", (int)ch);
				break;
			}
		}
		printf("|\n");
		printSeparationLine();
	}
}//printBoard

/*This function will print the headers for the columns*/
void printColumnHeaders() {
	unsigned int i;					//Declaring variables
	for (i = 0; i <= COLS; i++) {	//Running on columns and prints what needed
		if (i == 0)
			printf("|   ");
		else
			printf("| %2d  ", i);
	}
	printf("|\n");
}//printColumnHeaders

/*This function will print the separation lines*/
void printSeparationLine() {
	unsigned int i;					//Declaring variables
	for (i = 0; i <= COLS; i++)	{	//Running and prints what needed
		if (i == 0)
			printf("+---");
		else
			printf("+-----");
	}
	printf("+\n");
}//printSeparationLine

char getCell(char** board, int row, int col) {
	return board[row][col];
}//getCell

/*This function will release the board*/
void freeBoard(char** board) {
	unsigned int i, j, k;			//Declaring variables
	for (i = 0; i < ROWS; i++) {	//Running on rows to release the columns
		free(board[i]);
	}
	free(board);					//Releasing the board
}//freeBoard