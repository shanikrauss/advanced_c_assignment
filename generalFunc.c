#include "generalStruct.h"
#include "ch.h"

void* safeMalloc(size_t size)
{
	void* tmp = malloc(size);
	if (tmp == NULL)
	{
		exit(1);
	}
	return tmp;
}

void* safeCalloc(size_t num, size_t size)
{
	void* tmp = calloc(num, size);
	if (tmp == NULL)
	{
		exit(1);
	}
	return tmp;
}

void* safeRealloc(void* ptr, size_t size)
{
	void* tmp = realloc(ptr, size);
	if (tmp == NULL)
	{
		exit(1);
	}
	return tmp;
}

bool outBoard(int newCol, int newRow)
{
	return (((0 > newCol) || (newCol >= COLS) || (0 > newRow) || (newRow >= ROWS)));
}

char transNumToLetter(int num)
{
	char resLetter = '0';
	switch (num)
	{
	case 0: resLetter = 'A';
		break;
	case 1: resLetter = 'B';
		break;
	case 2: resLetter = 'C';
		break;
	case 3: resLetter = 'D';
		break;
	case 4: resLetter = 'E';
		break;
	case 5: resLetter = 'F';
		break;
	case 6: resLetter = 'G';
		break;
	case 7: resLetter = 'H';
		break;
	default:
		break;
	}
	return resLetter;
}

void checkOpeningFile(FILE* bf)
{
	if (bf == NULL)
	{
		exit(1);
	}
}



void freeBoardPosArrayP(boardPosArray* posArr)
{
	free(posArr->positions);
	free(posArr);
}

void freeBoardPosArrayPP(boardPosArray** posArr)
{
	int i = 0, j = 0;

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			if ((posArr[i][j].positions) != NULL)
			{
				free(posArr[i][j].positions);
			}
		}
		free(*(posArr + i));
	}
	free(posArr);
}


void freeMovesList(movesList* movesLst)
{
	moveCell* temp;
	int i = 0, j = 0;


	while (movesLst->head != NULL)
	{
		temp = movesLst->head;
		movesLst->head = movesLst->head->next;
		free(temp);
	}
	free(movesLst);
}

int countStarsInBoard(char** board)
{
	int res = 0, i, j;

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			if (isStar(board[i][j]))
			{
				res++;
			}
		}
	}
	return res;
}