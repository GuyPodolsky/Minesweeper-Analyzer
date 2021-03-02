#define _CRT_SECURE_NO_WARNINGS
///Including

#include "Q6.h"

///Functions
/*This function will open a file, will read a path from it using a decoding from bits code we used in Q5,
will convert it to a list if its not an empty file, and will check if its: legal move list,
covering the entire board, or if its just movees on board but not covering it*/
int checkAndDisplayPathFromFile(char* file_name, movesArray** moves, char** board) {
	int res, occupiedPositions;							//Declaring variables
	movesList* movesLst = NULL;							//Initializng variables
	if (!isFileExists(file_name) || isFileEmpty(file_name))		//Checks if file is empty or not exist
		return -1;
	boardPosArray* bPosArr = boardPosBinaryFileToBoardPosArr(file_name); 
	generalCheck(bPosArr, 'a');
	if (bPosArr == NULL || bPosArr->size <= 1)		//In case there were no moves made
		res = 2;
	else {											//Made a move
		movesLst = isPositionsConnected(bPosArr, moves, board);
		if (movesLst == NULL)
			res = 1;
		else
			res = 2;
	} if (res == 1) {							//Checks for release
		free(bPosArr->positions);
		free(bPosArr);
		return res;
	} else {									//Check for print
		if (movesLst == NULL)
			printBoard(board);
		else {									//Display
			display(movesLst, bPosArr->positions[0], board);
			occupiedPositions = getMoveListLen(movesLst) + countAsterisks(board) + 1;
			if (occupiedPositions == ROWS * COLS)
				res = 3;
		}
		free(bPosArr->positions);				//Release allocations
		free(bPosArr);
		if (movesLst != NULL);
			freeMovesList(movesLst);
		return res;
	}
}

/*This function will decode a binary file from Q5 to a board position array*/
boardPosArray* boardPosBinaryFileToBoardPosArr(char* file_name)
{
	short int i, j, size, curBit;								//Declaring variables
	unsigned char byte, tmpByte, mask, tmpMask;
	boardPosArray* res;
	FILE* fp;
	fp = fopen(file_name, "rb");								//Initializing variables
	generalCheck(fp, 'f');
	res = (boardPosArray*)malloc(sizeof(boardPosArray));
	generalCheck(res, 'a');
	fread(&size, sizeof(short int), 1, fp);
	res->size = (unsigned int)size;
	if (res->size > 0) {
		res->positions = (boardPos*)malloc((int)size * sizeof(boardPos));
		generalCheck(res->positions, 'a');
	} else {
		free(res);
		return NULL;
	}
	for (i = 0, curBit = 0, byte = 0; i < size; i++) {	//Doing the decoding
		for (j = 0, mask = 7; j < 2; j++,mask=7)
		{
			if (curBit == 8 || curBit == 0) {
				fread(&byte, sizeof(char), 1, fp);
				curBit = 0;
			} if (8 - curBit >= 3) {
				mask = mask << curBit;
				tmpByte = byte & mask;
				tmpByte = tmpByte >> curBit;
				res->positions[i][j] = tmpByte + (j == 0 ? 'A' : 1);
				curBit += 3;
			} else {
				tmpMask = mask;
				tmpMask = tmpMask << curBit;
				tmpByte = byte & tmpMask;
				tmpByte = tmpByte >> curBit;
				res->positions[i][j] = tmpByte;
				fread(&byte, sizeof(char), 1, fp);
				mask = 7;
				curBit = overFlowedBits(curBit, 3, sizeof(char));
				mask = mask >> (3 - curBit);
				tmpByte = byte & mask;
				tmpByte = tmpByte << (3 - curBit);
				res->positions[i][j] = res->positions[i][j] | tmpByte;
				res->positions[i][j] += (j == 0 ? 'A' : 1);
			}
		}
	}
	fclose(fp);
	return res;
}//boardPosBinaryFileToBoardPosArr

/*This function will check if the file is empty*/
bool isFileEmpty(char* file_name) {
	short int numOfElements;							//Declaring variables
	bool res;
	FILE* fp = fopen(file_name, "rb");
	generalCheck(fp, 'f');
	fread(&numOfElements, sizeof(short int), 1, fp);	//Read to check	
	fclose(fp);
	if (numOfElements > 0)								//See if empty
		return false;
	return true;
}//isFileEmpty

/*This function will check if the file exists*/
bool isFileExists(char* file_name) {
	bool res;								//Declaring variables
	FILE* fp = fopen(file_name, "rb");
	generalCheck(fp, 'f');
	if (fp == NULL)							//Check
		res = false;
	else
		res = true;
	fclose(fp);
	return res;
}//isFileExists

/*This function will check if the position is in the positions array*/
bool isPosInPosArr(boardPos pos, boardPos* posArr, unsigned int size) {
	unsigned int i;								//Declaring variables
	for (i = 0; i < size; i++) {				//Running on array
	 	if (pos[R] == posArr[i][R]) {
			if (pos[C] == posArr[i][C])
				return true;
		}
	}
	return false;
}//isPosInPosArr

/*This function will check if the positions are connected*/
movesList* isPositionsConnected(boardPosArray* posArr, movesArray** moves, char** board) {
	unsigned int i, j;											//Declaring variables
	Move move;
	boardPos pos1, pos2;
	boardPosArray** boardPosArr = validMoves(moves, board);		//Initializing variables
	movesList* res = (movesList*)malloc(sizeof(movesList));
	generalCheck(res, 'a');
	res->tail = NULL;
	res->head = NULL;
	if (boardPosArr == NULL)
		return NULL;
	for (i = 0; i < (posArr->size - 1); i++) {					//Checks
		pos1[R] = posArr->positions[i][R];
		pos1[C] = posArr->positions[i][C];
		pos2[R] = posArr->positions[i + 1][R];
		pos2[C] = posArr->positions[i + 1][C];
		if (!isValid(board, ROWS, COLS, pos1[R]-'A', pos1[C]-1) || !isValid(board, ROWS, COLS, pos2[R]-'A', pos2[C]-1))
			return NULL;
		if (!isPosInPosArr(pos2, boardPosArr[pos1[R] - 'A'][pos1[C] - 1].positions, boardPosArr[pos1[R] - 'A'][pos1[C] - 1].size))
			return NULL;
		move.rows = (pos2[R] - 'A') - (pos1[R] - 'A');
		move.cols = (pos2[C] - 1) - (pos1[C] - 1);
		if (res->head == NULL) {
			res->head = createMoveCell(NULL, move, NULL);
			res->tail = res->head;
		} else {
			res->tail->next = createMoveCell(res->tail, move, NULL);
			res->tail = res->tail->next;
		}
	}
	freeBoradPosArr(boardPosArr);							//Release the array as we made a list
	return res;
}//isPositionsConnected

/*This function will get the list length*/
int getMoveListLen(movesList* list) {
	return getMoveListLenRec(list->head);
}//getMoveListLen

/*This function will get the length in recursion*/
int getMoveListLenRec(moveCell* head) {
	if (head == NULL)
		return 0;
	return (getMoveListLenRec(head->next) + 1);
}//getMoveListLenRec

/*This function will create a move cell*/
moveCell* createMoveCell(moveCell* prev, Move move, moveCell* next) {
 	moveCell* res = (moveCell*)malloc(sizeof(moveCell));		//Decalring the cell
	generalCheck(res, 'a');
	res->move = move;											//Setting the cell
	res->prev = prev;
	res->next = next;
	return res;
}//createMoveCell

/*This function releases moves list*/
void freeMovesList(movesList* lst)
{
	moveCell* tmp;														 //Creating a temp to save and release 
	while (lst != NULL && lst->head != NULL && lst->head->next != NULL) {//Runs on the list
		tmp = lst->head;															//Save what to release
		lst->head = lst->head->next;												//Move foward on the list
		free(tmp);																	//Release the saved placed
	}if (lst != NULL)
		free(lst);
}//freeMovesList

/*This function will release a board position array*/
void freeBoradPosArr(boardPosArray** arr) {
	unsigned int i, j;							//Declaring variables
	for (i = 0; i < ROWS; i++) {					//Running on the array and releasing
		for (j = 0; j < COLS; j++) {
			if (arr[i][j].size != 0)
				free(arr[i][j].positions);
		}
		free(arr[i]);
	}
	free(arr);
}//freeBoardPosArr