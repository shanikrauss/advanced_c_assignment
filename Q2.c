#define _CRT_SECURE_NO_WARNINGS
#include "ch.h"
#include "generalStruct.h"
#include "HeaderQ2.h"
#include "HeaderQ1.h"





void printFrameLine()
{
	int i = 0;
	printf("+");
	for (i = 0; i <= COLS; i++)
	{
		printf("-----+");
	}
	printf("\n");
}

void printTheBoard(char board[ROWS][COLS])
{
	int i = 0, j = 0;
	printFrameLine();
	printf("|     ");
	for (i = 0; i < COLS; i++)
	{
		printf("|  %d  ", i + 1);
	}
	printf("|\n");

	for (i = 0; i < ROWS; i++)
	{
		printFrameLine();

		printf("|  %c  ", transNumToLetter(i));

		for (j = 0; j < COLS; j++)
		{
			if ((isStar(board[i][j])) || (isHash(board[i][j])) || (isSpace(board[i][j])))
			{
				printf("|  %2c ", board[i][j]);
			}
			else
			{
				printf("|  %2d ", board[i][j]);
			}
		}
		printf("|\n");
	}
	printFrameLine();
}

moveCell* updateDeleteMoveCell(moveCell* currHead, moveCell* tail)
{
	if (currHead == NULL)
	{
		return tail;
	}
	else
	{
		return currHead->prev;
	}
}

int display(movesList *moves_list, boardPos start, char **board)
{
	char theBoardPrinted[ROWS][COLS];
	int i = 0, j = 0, countValidMoves = 1, countDeleteMoves = 0;
	int newCellRow, newCellCol;
	movesList tmp;
	boardPos currentCell;
	bool isValidMove = true;
	moveCell* deleteMoveCell;
	currentCell[0] = start[0]-'A';
	currentCell[1] = start[1]-1;

	updatePrintedBoard(theBoardPrinted, board, start);

	if (moves_list == NULL)
	{
		printTheBoard(theBoardPrinted);
		return 0;
	}
	
	tmp = *(moves_list);
	
	while (tmp.head != NULL)
	{
		newCellRow = (int)(tmp.head->move.rows + currentCell[0]);
		newCellCol = (int)(tmp.head->move.cols + currentCell[1]);
		if ((outBoard(newCellCol, newCellRow)) || (isStar(board[newCellRow][newCellCol])) || (theBoardPrinted[newCellRow][newCellCol] != ' '))
		{
			isValidMove = false;
		}
		tmp.head = tmp.head->next; //update head
		if (!isValidMove)
		{
			deleteMoveCell = updateDeleteMoveCell(tmp.head, moves_list->tail);
			removeCellfromMovesList(moves_list, deleteMoveCell);
			countDeleteMoves++;
		}
		else
		{
			theBoardPrinted[newCellRow][newCellCol] = countValidMoves;
			countValidMoves++;
			currentCell[0] = newCellRow;
			currentCell[1] = newCellCol;
		}
		isValidMove = true;
	}
	printTheBoard(theBoardPrinted);
	return countDeleteMoves;
}


void updatePrintedBoard(char resBoard[ROWS][COLS], char** board, boardPos start) //ARBEL ADDED
{
	int i = 0, j = 0;

	for (i = 0; i < ROWS; i++) // update the printed board
	{
		for (j = 0; j < COLS; j++)
		{
			resBoard[i][j] = board[i][j];
		}
	}
	resBoard[start[0] - 'A'][start[1] - 1] = '#';
}




void removeCellfromMovesList(movesList* lst, moveCell* node)
{
	if (lst->head == lst->tail) 		// if only one node in the list
	{
		free(node);
	}
	else // more then one node in the list
	{
		if (node == lst->head)
		{
			node->next->prev = NULL;
			lst->head = node->next;
		}
		else if (node == lst->tail)
		{
			node->prev->next = NULL;
			lst->tail = node->prev;
		}
		else
		{
			node->prev->next = node->next;
			node->next->prev = node->prev;
		}
		free(node);
	}
}



