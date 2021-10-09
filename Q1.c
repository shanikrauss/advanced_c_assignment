#define _CRT_SECURE_NO_WARNINGS
#include "generalStruct.h"
#include "ch.h"
#include "HeaderQ1.h"





void reduceArray(movesArray* PosMoves, int newSize)
{
	int read = PosMoves->size - 1, write = 0;

	if (newSize == 0)
	{
		free(PosMoves->moves);
		return;
	}

	while (read > write)
	{
		while (write < PosMoves->size && PosMoves->moves[write].cols != ' ')
		{
			write++;
		}
		while (read >= 0 && PosMoves->moves[read].cols == ' ')
		{
			read--;
		}
		if (read > write)
		{
			PosMoves->moves[write].cols = PosMoves->moves[read].cols;
			PosMoves->moves[write].rows = PosMoves->moves[read].rows;
			read--;
		}
	}
	PosMoves->moves = (Move*)safeRealloc(PosMoves->moves, newSize * sizeof(Move));

	PosMoves->size = newSize;
}




boardPosArray checkValidCell(char** board, movesArray* PosMoves, int cellRow, int cellCol)
{
	boardPosArray res;
	int write = 0, i = 0;
	boardPos* position;

	position = (boardPos*)safeCalloc(PosMoves->size, sizeof(boardPos));

	for (i = 0; i < PosMoves->size; i++)
	{
		//if not valid move update char to space
		if ((outBoard((int)((PosMoves->moves) + i)->cols + cellCol, (int)((PosMoves->moves) + i)->rows + cellRow)) ||
			(isStar(board[(int)((PosMoves->moves) + i)->rows + cellRow][(int)((PosMoves->moves) + i)->cols + cellCol])))
		{
			((PosMoves->moves) + i)->cols = ((PosMoves->moves) + i)->rows = ' ';
		}
		else//if the move is valid
		{
			position[write][0] = transNumToLetter((int)((PosMoves->moves) + i)->rows + cellRow); //rows, transNumToLetter returns char
			position[write][1] = (char)((int)((PosMoves->moves) + i)->cols + cellCol + 1); //cols
			write++;
		}
	}

	if (PosMoves->size != 0)
	{
		reduceArray(PosMoves, write);//void , read write func
	}

	if (write == 0)
	{
		free(position);
		res.positions = NULL;
	}
	else
	{
		res.positions = position;
		res.positions = (boardPos*)safeRealloc(res.positions, write * sizeof(boardPos));
	}
	res.size = write;
	return res;
}


boardPosArray** validMoves(movesArray** moves, char** board)
{
	int i = 0, j = 0;

	boardPosArray** resValidPos;
	resValidPos = (boardPosArray**)safeMalloc(ROWS * sizeof(boardPosArray*));
	for (i = 0; i < ROWS; i++)
	{
		*(resValidPos + i) = (boardPosArray*)safeMalloc(COLS * sizeof(boardPosArray));
	}
	
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{

			resValidPos[i][j] = checkValidCell(board, &(moves[i][j]), i, j);
		}
	}
	return resValidPos;
}







