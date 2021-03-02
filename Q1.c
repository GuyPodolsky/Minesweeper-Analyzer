#define _CRT_SECURE_NO_WARNINGS
/*This function checks if a move is valid*/
#include "Q1.h"

///Functions
/*This function checks the moves from each position and returns an array with only the allowed positions (Q1)*/
boardPosArray** validMoves(movesArray** moves, char** board) {
	unsigned int i, j, k, writePos;														//variables declaration.
	int* invalidMovesArr;
	boardPosArray** bPosArr = (boardPosArray**)malloc(ROWS * sizeof(boardPosArray*));	//allocates memory to the array of possible moves arrays.
	generalCheck(bPosArr, 'a');															//checks if the allocation went well.
	for (i = 0; i < ROWS; i++) {																//checks all the rows.
		bPosArr[i] = (boardPosArray*)malloc(COLS * sizeof(boardPosArray));					//allocates memory to the array of possible moves.
		generalCheck(bPosArr[i], 'a');														//checks if the allocation went well.
		for (j = 0; j < COLS; j++) {																	//checks all the columns.
			if (isAsterisk(board[i][j])) {															//in case the cell contains asterisk.
				bPosArr[i][j].size = moves[i][j].size = 0;
				free(moves[i][j].moves);																//releases the array of moves
				moves[i][j].moves = NULL;																//initializes the array of moves to NULL.
			} else																				//in case the cell doesn't contain asterisk.
			{
				bPosArr[i][j].positions = (boardPos*)malloc(moves[i][j].size * sizeof(boardPos));		//allocates memory to the array of positions.
				generalCheck(bPosArr[i][j].positions, 'a');												//checks if the allocation went well.
				invalidMovesArr = (int*)calloc(moves[i][j].size, sizeof(int));
				generalCheck(invalidMovesArr, 'a');
				for (k = 0, writePos = 0, bPosArr[i][j].size = 0; k < moves[i][j].size; k++)
				{																				    		//in case that the move is invalid it removes this move.
					if (!isValid(board, ROWS, COLS, i + moves[i][j].moves[k].rows, j + moves[i][j].moves[k].cols))
						invalidMovesArr[k] = 1;
					else																					//in case it is a valid move, it saves it into the array of positions.
					{
						bPosArr[i][j].size++;
						bPosArr[i][j].positions[writePos][R] = (char)i + moves[i][j].moves[k].rows + 'A';
						bPosArr[i][j].positions[writePos++][C] = (char)j + moves[i][j].moves[k].cols + 1;
					}//else
				}//for
				removeInvalidMoves(invalidMovesArr, &(moves[i][j].size), moves[i][j].moves);			//removes the invalid moves using grade sort method.
				free(invalidMovesArr);																	//releases the memory initialization of the array of invalid moves indexes.
				if (moves[i][j].size <= 0)																//in case the array of moves is empty.
				{
					free(moves[i][j].moves);																//releases the array of moves
					free(bPosArr[i][j].positions);															//releases the array of positions.
					bPosArr[i][j].positions = moves[i][j].moves = NULL;										//initializes the array of positions and moves to NULL.
				}//if
				else
				{
					bPosArr[i][j].positions = (boardPos*)realloc(bPosArr[i][j].positions, moves[i][j].size * sizeof(boardPos)); //shrink the size of the array of positions.
					generalCheck(bPosArr[i][j].positions, 'a');																	//checks if the re-allocation went well.
					moves[i][j].moves = (Move*)realloc(moves[i][j].moves, moves[i][j].size * sizeof(Move));						//shrink the size of the array of moves.
					generalCheck(moves[i][j].moves, 'a');																		//checks if the re-allocation went well.
				}//else
			}//else
		}//for
	}//for
	return  bPosArr;																	//returns the array of possible moves arrays. 
}//validMoves

bool isValid(char** board, unsigned int rows, unsigned int cols, unsigned int rPos, unsigned int cPos)
{
	if (isOutOfBoard(rows, cols, rPos, cPos))
		return false;
	if (isAsterisk(board[rPos][cPos]))
		return false;
	if ((board[rPos][cPos]) != SPACE)
		return false;
	return true;
}//isValid

/*This function checks if the move goes out of the board*/
bool isOutOfBoard(const unsigned int rows, const unsigned int cols, unsigned int rPos, unsigned int cPos)  //TODO: add description.
{
	if (rPos < 0 || rPos >= rows)			//checks if the row position is out of the board.
		return true;
	if (cPos < 0 || cPos >= cols)			//checks if the column position is out of the board.
		return true;
	return false;
}//isOutOfBoard

/*This function checks if the given char is an asterisk*/
bool isAsterisk(const char ch) //TODO: add description.
{
	if (ch == ASTERISK)		//if the char is equal to asterisk
		return true;
	return false;
}//isAsterisk

/*This function removes invalid moves from an array*/
void removeInvalidMoves(int* invalidMovesIndexArr, unsigned int* size, Move* move) //TODO: add description.
{
	unsigned read, write, count;											//variables declaration.
	for (read = 0, write = 0, count = 0; read < *size; read++)				//rewrites the array of moves with out the removed move.
	{
		if (invalidMovesIndexArr[read] != 1)
			move[write++] = move[read];
		else
			count++;
	}//for
	*size -= count;														//updates the logical size of the array.
}//removeMove

/*This function is general check whether its allocations, files, etc*/
void generalCheck(const void* pointer, const char flag) //TODO: add description.
{
	if (pointer == NULL)										//in case that the pointer value is NULL it indicates that there is an error.
	{
		switch (flag)											//prints a suitable error message.
		{
		case 'a':													//memory allocation.
			printf("ERROR! - Memory Allocation Failed!\n");
			break;
		case 'f':													//file opening.
			printf("ERROR! - File Opening Failed!\n");
			break;
		default:													//any other check that made by comparing the pointer value to NULL.
			printf("ERROR! - General NULL Pointer ERROR!\n");
			break;
		}//switch
		exit(EXIT_FAILURE);									//terminates the program.
	}//if
}//generalCheck
