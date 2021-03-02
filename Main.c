///Defining
#define _CRT_SECURE_NO_WARNINGS

///Includes
#include  <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Q6.h"
#include "test.h"


/*TODO:
 *		1).Make the functions more generic by adding rows and columns input.
 *		2).Fix the 'freeMovesArr', i should try to free the 'pathTree' first and then maybe it will fix the issue.
 *		3).Add a check that prevent a loop circle by creation a board of indicators.
 *		4).Create free function to the 'pathTree'.
 *		4).Go through the project's forum and check that I am addressing all the new requirements.
*/
///Main
void main()
{
    //must//
    srand(time(NULL));
    char** board;
    movesArray** moves = NULL, ** moves1 = NULL;
    movesList* moveList;
    boardPosArray** bPosArr;
    boardPos start = { 'A',1 };
    pathTree path;

    board = initBoard();


    //checks//
    /*
    //Q1 //!checked
    setAsterisks(board, ROWS - 1, COLS - 1, 0, 'a'); //test
    printBoard(board);					     //test
    moves = setMovesArr(board, 'a');		 //test
    printf("Original Moves Array:\n\n:");
    printMovesArr(moves, board);			 //test
    bPosArr = validMoves(moves, board);
    printf("Checked Moves Array:\n\n:");
    printMovesArr(moves, board);			 //test
    printf("The Result: BoardPos Array:\n\n:");
    printBoardPosArray(bPosArr);			 //test
    freeMovesArr(moves);					 //test
    freeBoradPosArr(bPosArr);				 //test
    //*/
    /*
    //Q2//!checked
    setAsterisks(board, ROWS - 1, COLS - 1, 0, 'a'); //test
    printBoard(board);								 //test
    moveList = setMovesList('a');					 //test
    printMovesList(moveList,'i');					 //test
    printf("%d", display(moveList, start, board));
    freeMovesList(moveList);						 //test
    //*/
    /*
    //Q3//!checked
    setAsterisks(board, ROWS - 1, COLS - 1, 0, 'a'); //test
    printBoard(board);								 //test
    moves = setMovesArr(board, 'a');				 //test
    printf("Moves Array:\n\n:");					 //test
    validMoves(moves, board);						 //test
    printMovesArr(moves, board);					 //test
    path = findAllPossiblePaths(start, moves, board);
    printf("Path Tree:\n\n");						 //test
    printPathTree(&path);							 //test
    freePathTree(&path);							 //test
    freeMovesArr(moves);							 //test
    //*/
    /*
    //Q4 //!checked
    setAsterisks(board, ROWS - 1, COLS - 1, 0, 'a'); //test
    printBoard(board);								 //test
    moves = setMovesArr(board, 'm');				 //test
    printMovesArr(moves, board);					 //test
        //ver2	//path = findAllPossiblePaths(start, moves, board);
        //ver2	//printPathTree(&path);
    moveList = findPathCoveringAllBoard(start, moves, board);
    display(moveList, start, board);				 //test
    freeMovesArr(moves);
    //*/
    /*
    //Q5 //!checked
    setAsterisks(board, ROWS - 1, COLS - 1, 0, 'a');					//test
    printBoard(board);													//test
    //bPosArr = setBoardPosArray('s');									//test
    moves = setMovesArr(board, 'a');
    bPosArr = validMoves(moves, board);
    printBoardPosArrayCell(*bPosArr);									//test
    saveListToBinFile("ex5.bin", *bPosArr);
    printListToBinFileInBinary("ex5.bin");								//test
    printf("\n");														//test
    if(boardPosBinaryFileToBoardPosArr("ex5.bin") !=NULL)
        printBoardPosArrayCell(boardPosBinaryFileToBoardPosArr("ex5.bin"));	//test
    //*/
    /*
    //Q6 */
    setAsterisks(board, ROWS - 1, COLS - 1, 0, 'a');					//test
    moves = setMovesArr(board, 'm');									//test
    //moves1 = setMovesArr(board,'a');
    printBoard(board);													//test
    bPosArr = setBoardPosArray('m');
    //bPosArr = validMoves(moves1, board);								//test
    saveListToBinFile("ex5.bin", *bPosArr);								//test
    bPosArr = boardPosBinaryFileToBoardPosArr("ex5.bin");
    printListToBinFileInBinary("ex5.bin");
    printBoardPosArrayCell(bPosArr);
    printf("%d",checkAndDisplayPathFromFile("ex5.bin", moves, board));
    free(bPosArr);
    freeMovesArr(moves);
    //*/
    //must
    freeBoard(board);
}