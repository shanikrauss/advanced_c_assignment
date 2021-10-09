#define _CRT_SECURE_NO_WARNINGS
#include "ch.h"
#include "generalStruct.h"
#include "HeaderQ1.h"
#include "HeaderQ2.h"
#include "HeaderQ6.h"



/*
!!! PLEASE NOTE !!!
we did not know if we needed to print a board only with the stars 
We asked in the forum but there was no clear and unambiguous answer.
In addition, we did not see any reference to the topic in the project guidelines.
An empty series of locations is valid, but the function from section 2 cannot be used as written in the project (because the series is empty and there is no start and in section 2 we were told that there is a start).
So we assumed that as stated in the project guidelines, "otherwise the function will return 3"
 

If we had to write a function that prints the board with only the '*' , it would be written here:
line 46
if (posArrFromFile == NULL) // the positions' list in the file is empty, meaning size in file is 0
	{
	   func	print stars board
		return VALID_PATH;
	}
*/
int checkAndDisplayPathFromFile(char* file_name, movesArray** moves, char** board)
{
	FILE* file;
	boardPosArray* posArrFromFile;
	boardPosArray** validPosArr;
	movesList* movesLst;
	int resDisplayFunc=0, starsInBoard=0, sizePosArrFromFile=0;
	boardPos start;

	file = fopen(file_name, "r");
	if (file == NULL)
	{
		return FILE_NOT_EXIST;
	}

	posArrFromFile = decodePosFromFile(file); //decoding the binary file into boardPosArray
	fclose(file);

	if (posArrFromFile == NULL) // the positions' list in the file is empty, meaning size in file is 0
	{
		return VALID_PATH;
	}

	reduceBoardPosArray(posArrFromFile); // if a position appears more than 1 delete the dup pos from arr
	validPosArr = validMoves(moves, board); // use func Q1

	if (!checkIfPosArrPathIsValid(posArrFromFile, validPosArr, board)) //check if the path from file is valid compere to arr from Q1
	{
		freeBoardPosArrayP(posArrFromFile);
		freeBoardPosArrayPP(validPosArr);
		return PATH_NOT_VALID;
	}
	movesLst = createMovesList(posArrFromFile);

	start[0] = posArrFromFile->positions[0][0];// update start
	start[1] = posArrFromFile->positions[0][1];

	resDisplayFunc = display(movesLst, start, board);

	starsInBoard = countStarsInBoard(board);

	sizePosArrFromFile = posArrFromFile->size;
	freeMemory(posArrFromFile, validPosArr, movesLst);

	if (starsInBoard + sizePosArrFromFile == ROWS * COLS) // if the number of stars + the moves made in the game is equal to the board size --> meaning the board is full
	{
		return MAX_VALID_PATH;
	}

	return VALID_PATH;
}



movesList* createMovesList(boardPosArray* posArr)
{
	int i = 0;
	movesList* resList;
	Move currMove;

	resList = (movesList*)safeMalloc(sizeof(movesList));
	makeEmptyMovesList(resList);

	if (posArr->size== 1)
	{
		return resList;			
	}

	for (i = 0; i + 1 < posArr->size; i++)
	{
		currMove.rows = posArr->positions[i + 1][0] - posArr->positions[i][0];
		currMove.cols = posArr->positions[i + 1][1] - posArr->positions[i][1];
		insertDataToEndMovesList(resList, currMove);

	}
	return resList;
}


void reduceBoardPosArray(boardPosArray* arr)
{
	putSpaceInDuplicatePos(arr);
	reducePosArray(arr);

}


void putSpaceInDuplicatePos(boardPosArray* arr)
{
	char posExistInArr[ROWS][COLS];
	int i = 0, j = 0;

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			posExistInArr[i][j] = 0;
		}
	}

	for (i = 0; i < arr->size; i++)
	{
		if ((posExistInArr[(arr->positions)[i][0] - 'A'][(arr->positions)[i][1] - 1]) == 0)
		{
			posExistInArr[(arr->positions)[i][0] - 'A'][(arr->positions)[i][1] - 1] = 1;
		}
		else
		{
			(arr->positions)[i][0] = ' ';
			(arr->positions)[i][1] = ' ';
		}
	}
}


void reducePosArray(boardPosArray* arr)
{
	int write = 0, read = 1;

	if ((write < arr->size) && (read < arr->size) && (write < read))
	{
		while ((write < arr->size) && ((arr->positions)[write][0] != ' '))
		{
			write++;
		}
		if ((write + 1) < arr->size)
		{
			read = write + 1;
			while ((read < arr->size) && ((arr->positions)[read][0] == ' '))
			{
				read++;
			}
		}
		if ((write < arr->size) && (read < arr->size) && (write<read))
		{
			(arr->positions)[write][0] = (arr->positions)[read][0];
			(arr->positions)[write][1] = (arr->positions)[read][1];
			(arr->positions)[read][0] = ' ';
			(arr->positions)[read][1] = ' ';
		}
	}
	arr->positions = (boardPos*)safeRealloc(arr->positions, write * sizeof(boardPos));
	arr->size = write;
}


boardPosArray* decodePosFromFile(FILE* file)
{
	BYTE byte1, byte2;
	boardPos* arr;
	boardPosArray* resArr;
	short int arrSize;
	int i = 0;

	fread(&arrSize, sizeof(short int), 1, file); //reading the posArr size from file
	if (arrSize == 0)
	{
		return NULL;
	}
	resArr = (boardPosArray*)safeMalloc(sizeof(boardPosArray));
	arr = (boardPos*)safeMalloc(arrSize * sizeof(boardPos));

	for (i = 0; i < arrSize; i++)
	{
		if (i % 4 == 0)
		{
			fread(&byte1, sizeof(BYTE), 1, file);
			case1(byte1, arr + i);
		}
		else if (i % 4 == 1)
		{
			fread(&byte2, sizeof(BYTE), 1, file);
			case2(byte1, byte2, arr + i);
		}
		else if (i % 4 == 2)
		{
			fread(&byte1, sizeof(BYTE), 1, file);
			case3(byte2, byte1, arr + i);
		}
		else if (i % 4 == 3)
		{
			case4(byte1, arr + i);
		}
	}

	resArr->positions = arr;
	resArr->size = arrSize;

	
	return resArr;
}

void case1(BYTE byte, boardPos* arr)
{
	BYTE mask = 0x07; //0000 0111

	arr[0][1] = ((byte >> 2)& mask) + 1;
	arr[0][0] = (byte >> 5) + 'A';
}

void case2(BYTE byte1, BYTE byte2, boardPos* arr)
{
	BYTE mask = 0x07; //0000 0111

	arr[0][1] = ((byte2 >> 4)& mask) + 1;
	arr[0][0] = ((byte2 >> 7) | ((byte1 << 1) & mask)) + 'A';
}

void case3(BYTE byte1, BYTE byte2, boardPos* arr)
{
	BYTE mask = 0x07; //0000 0111

	arr[0][1] = (((byte1 << 2) & mask) | (byte2 >> 6)) + 1;
	arr[0][0] = ((byte1 >> 1)& mask) + 'A';
}

void case4(BYTE byte, boardPos* arr)
{
	BYTE mask = 0x07; //0000 0111

	arr[0][1] = (byte & mask) + 1;
	arr[0][0] = ((byte >> 3)& mask) + 'A';
}


bool checkIfPosArrPathIsValid(boardPosArray* posArrFromFile, boardPosArray** validPosArr, char** starsBoard)
{
	int i = 0;
	boardPos currCell, nextCell;
	if (posArrFromFile->size == 1) // check if start is valid (not * in start)
	{
		currCell[0] = posArrFromFile->positions[i][0];
		currCell[1] = posArrFromFile->positions[i][1];
		if (isStar(starsBoard[currCell[0] - 'A'][currCell[1] - 1]))
		{
			return false;
		}
	}
	for (i = 0; i + 1 < posArrFromFile->size; i++) // check if the next position is one of the current positions' moves
	{
		currCell[0] = posArrFromFile->positions[i][0];
		currCell[1] = posArrFromFile->positions[i][1];

		nextCell[0] = posArrFromFile->positions[i + 1][0];
		nextCell[1] = posArrFromFile->positions[i + 1][1];
		if (!isCellInPosArr(validPosArr[currCell[0] - 'A'][currCell[1] - 1], nextCell))
		{
			return	false;
		}
	}
	return true;
}

bool isCellInPosArr(boardPosArray arr, boardPos cell)
{
	int i = 0;
	for (i = 0; i < arr.size; i++)
	{
		if (arr.positions[i][0] == cell[0] && arr.positions[i][1] == cell[1])
		{
			return true;
		}
	}
	return false;
}



void freeMemory(boardPosArray* posArr1, boardPosArray** posArr2, movesList* movesLst)
{
	freeBoardPosArrayP(posArr1);
	freeBoardPosArrayPP(posArr2);
	freeMovesList(movesLst);
}

