#define _CRT_SECURE_NO_WARNINGS

#include "test.h"

char** initBoard()
{
	//Creates the rows
	char** res = (char**)malloc(ROWS * sizeof(char*));
	//Decalaring variables
	int i, j;
	//Running on rows
	for (i = 0; i < ROWS; i++)
	{
		//Creating the columns for each row
		res[i] = (char*)malloc(COLS * sizeof(char));
		//Running on columns and putting a space to initiate an empty board
		for (j = 0; j < COLS; j++)
			setCell(res, i, j, SPACE);
	}
	//Return board
	return res;
}//initBoard

void setCell(char** board, int row, int col, char sign)
{
	*(*(board + row) + col) = sign;
}//setCell

void freeMovesArr(movesArray** moves)
{
	//Declaring variables
	unsigned int i, j, k;
	//Checks if not null
	if (moves != NULL)
	{
		//Runs on moves
		for (i = 0; i < ROWS; i++)
		{
			if (moves[i] != NULL)
			{
				for (j = 0; j < COLS; j++)
				{
					//if (moves[i][j].moves != NULL)
					//{
					//	free(moves[i][j].moves);
					//}
				}
				free(moves[i]);
				moves[i] = NULL;
			}
		}
		free(moves);
	}
}//freeMovesArr

void setAsterisks(char** board, unsigned int upperR, unsigned int upperC, unsigned int lower,char flag)
{
	int c, r, amount;
	if (flag == 'm')
	{
		printf("\nHow many asterisks: ");
		scanf("%d", &amount);
	}
	else
	{
		amount = (rand() % ((upperC * upperR) - lower + 1)) + lower;
	}

	while (amount > 0)
	{
		c = (rand() % (upperC - lower + 1)) + lower;
		r = (rand() % (upperR - lower + 1)) + lower;

		if (board[r][c] != ASTERISK)
		{
			board[r][c] = ASTERISK;
			amount--;
		}
	}
}

movesArray** setMovesArr(char **board, char flag) //'s' -Semi-Automatic, 'a' - Automatic, 'm'-Manuel
{
	unsigned int i, j, k;
	char ch;

	movesArray** moves = (movesArray**)malloc(ROWS * sizeof(movesArray*));
	generalCheck(moves,'a');

	for (i = 0; i < ROWS; i++)
	{
		moves[i] = (movesArray*)malloc(COLS * sizeof(movesArray));
		generalCheck(moves[i], 'a');
		for (j = 0; j < COLS; j++)
		{
			ch = board[i][j];
			board[i][j] = 'H';

			if(flag != 'a')
			{
				printBoard(board);
				printf("Enter moves array size: ");
				scanf("%d", &moves[i][j].size);
			}
			else
				moves[i][j].size = (rand() % (255 - 0 + 1)) + 0;
			moves[i][j].moves = (Move*)malloc(moves[i][j].size * sizeof(Move));
			generalCheck(moves[i][j].moves, 'a');

			for (k = 0; k < moves[i][j].size; k++)
			{
				if (flag == 'm')
				{
					printf("Enter rows and cols: ");
					scanf("%d %d", &(moves[i][j].moves[k].rows),&(moves[i][j].moves[k].cols));
					//printf("Enter rows: ");
					//scanf("%d", &(moves[i][j].moves[k].rows));
				}
				else
				{
					moves[i][j].moves[k].cols = rand() % (7 - (-7) + 1) -7;
					moves[i][j].moves[k].rows = rand() % (7 - (-7) + 1) -7;
					//moves[i][j].moves[k].cols = rand() % (10 - (-10) + 1) - 10;
					//moves[i][j].moves[k].rows = rand() % (10 - (-10) + 1) - 10;
					//moves[i][j].moves[k].cols = (char)((rand() % (255 - 0 + 1)) + 0);
					//moves[i][j].moves[k].rows = (char)((rand() % (255 - 0 + 1)) + 0);
				}
			}
			board[i][j] = ch;
		}
	}
	return moves;
}
movesList* setMovesList(char flag) //s - semi , a- auto , m - manual
{
	int i, size, cols, rows;
	movesList* res = NULL;
	moveCell* cell = NULL;

	if (flag != 'a')
	{
		printf("Enter number of moves: ");
		scanf("%d", &size);
	}
	else
		size = (rand() % (255 - 0 + 1)) + 0;

	printf("TEST: size is %d\n", size);
	res = (movesList*)malloc(sizeof(movesList));
	generalCheck(res, 'a');

	res->head = NULL;
	res->tail = NULL;

	for (i = 0; i < size; i++)
	{
		cell = (moveCell*)malloc(sizeof(moveCell));
		generalCheck(cell, 'a');

		cell->prev = res->tail;
		cell->next = NULL;
		if (flag != 'm')
		{
			cell->move.cols = rand() % (10 - (-10) + 1) - 10;
			cell->move.rows = rand() % (10 - (-10) + 1) - 10;
		}
		else
		{
			printf("Enter rows: ");
			scanf("%d", &(cell->move.rows));
			printf("Enter cols: ");
			scanf("%d", &(cell->move.cols));
		}

		if (i == 0)
		{
			res->head = cell;
			res->tail = cell;
		}
		else
		{
			res->tail->next = cell;
			res->tail = cell;
		}
	}
	return res;
}

void printMovesList(movesList* moves, char flag)
{
	unsigned int i;
	moveCell* keepHead = moves->head,*keepTail = moves->tail;


	while (flag == 'i' ? (moves->head != NULL) : (moves->tail != NULL))
	{
		if (flag == 'i')
		{
			printf("rows: %d, cols: %d\n", moves->head->move.rows, moves->head->move.cols);
			moves->head = moves->head->next;
		}
		else
		{
			printf("rows: %d, cols: %d\n", moves->tail->move.rows, moves->tail->move.cols);
			moves->tail = moves->tail->prev;
		}
	}

	moves->head = keepHead;
	moves->tail = keepTail;
}

void printMovesArr(movesArray** moves,char **board)
{
	unsigned int i, j, k;
	char ch;

	for (i = 0; i < ROWS; i++)
	{
		for(j=0;j<COLS;j++)
		{
			ch = board[i][j];
			board[i][j] = HASHTAG;
			printBoard(board);
			printf("Size: %d\n", moves[i][j].size);
			for (k = 0;k < moves[i][j].size;k++)
				printf("Rows: %d ,Cols: %d\n",(int)moves[i][j].moves[k].rows, (int)moves[i][j].moves[k].cols);
			board[i][j] = ch;
		}
	}
}

void printPathTree(pathTree* path)
{
	printPathRec(path->head,0);
}

void printPathRec(treeNode* head)
{
	int i, deg = 0;
	if (head == NULL)
		return;
	treeNodeListCell* keepHead = head->next_possible_positions;
	while (head->next_possible_positions != NULL)
	{
		for (i = 0; i < deg; i++)
		{
			printf("            ");
		}
		printf("(%c,%d) ----> ", head->position[R], head->position[C]);
		deg++;
		printPathRec(head->next_possible_positions->node);
		head->next_possible_positions = head->next_possible_positions->next;
		if(head->next_possible_positions!=NULL)
			printf("\n");
	}
	head->next_possible_positions = keepHead;
}

void printListToBinFileInBinary(char* file_name)
{
	short int size,i;
	char byte;
	FILE* fp = fopen(file_name, "rb");
	generalCheck(fp, 'f');

	fread(&size, sizeof(short int), 1, fp);
	size *= 6;
	if(size%8==0)
		size /= 8;
	else
	{
		size /= 8;
		size++;
	}

	for (i = 0; i < (size); i++)
	{
		fread(&byte, sizeof(char), 1, fp);
		print_binary(byte);
		printf(" ");
	}

	fclose(fp);
}

void print_binary(char c)
{
	int i, mask;
	for (i = 7; i >= 0; i--)
	{
		mask = 1 << i;
		putchar((c & mask) ? '1' : '0');
		if (i % 4 == 0)
			putchar(' ');
	}
}

void printBoardPosArrayCell(boardPosArray* pos)
{
	unsigned int i;

	for(i=0;i<pos->size;i++)
	{
		printf("row: %c, col: %d\n", pos->positions[i][R], pos->positions[i][C]);
	}
}

void printBoardPosArray(boardPosArray ** arr)
{
	unsigned int i,j;

	for(i=0;i<ROWS;i++)
	{
		for(j=0;j<COLS;j++)
		{
			printf("\nRow: %d ,Col: %d\n\n", i, j);
			printBoardPosArrayCell(&arr[i][j]);
		}
	}
}

boardPosArray **setBoardPosArray(char flag)
{
	boardPosArray** res;
	unsigned int i, j,k,posArrSize;

	res = (boardPosArray**)malloc(ROWS * sizeof(boardPosArray*));
	generalCheck(res, 'a');

	for(i=0;i<ROWS;i++)
	{
		res[i] = (boardPosArray*)malloc(COLS * sizeof(boardPosArray));
		generalCheck(res[i], 'a');
		for(j=0;j<COLS;j++)
		{
			if(flag=='a')
				posArrSize = (rand() % (255 - 0 + 1)) + 0;
			else
			{
				printf("Enter position array size: \n");
				scanf("%d", &posArrSize);
			}

			res[i][j].size = posArrSize;
			res[i][j].positions = (boardPos*)malloc(posArrSize * sizeof(boardPos));
			generalCheck(res[i][j].positions, 'a');

			for(k=0;k<posArrSize;k++)
			{
				if(flag!='m')
				{
					res[i][j].positions[k][R] = (rand() % (7 - (-7) + 1)) - 7;
					res[i][j].positions[k][R] += 'A';
					res[i][j].positions[k][C] = (rand() % (7 - (-7) + 1)) - 7;
					res[i][j].positions[k][C] += 1;
				}
				else
				{
					char input[3];
					printf("Enter row and col indexes: ");
					scanf("%s", input);
					res[i][j].positions[k][R] = input[0];
					res[i][j].positions[k][C] = input[1] - '0';
				}
			}
		}
	}
	return res;
}