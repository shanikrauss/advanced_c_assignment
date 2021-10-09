#define _CRT_SECURE_NO_WARNINGS
#include "generalStruct.h"
#include "linkListHeader.h"


void insertDataToEndMovesList(movesList* lst, Move ch)
{
	if (lst->head == NULL)
	{
		lst->head = createMoveCellNode(ch, NULL, NULL);
		lst->tail = lst->head;
	}
	else
	{
		moveCell* newTail = createMoveCellNode(ch, lst->tail, NULL);
		insertMoveCellNodeToTail(lst, newTail);
	}
}

void insertMoveCellNodeToTail(movesList* lst, moveCell* newTail)
{
	newTail->next = NULL;

	if (lst->head == NULL) //if the list is empty
	{
		lst->head = lst->tail = newTail;
	}
	else
	{
		newTail->prev = lst->tail;
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

moveCell* createMoveCellNode(Move data, moveCell* prev, moveCell* next)
{
	moveCell* result;

	result = (moveCell*)safeMalloc(sizeof(moveCell));

	result->move = data;
	result->prev = prev;
	result->next = next;
	return result;
}

void makeEmptyMovesList(movesList* lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}

