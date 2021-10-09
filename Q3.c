#define _CRT_SECURE_NO_WARNINGS
#include "ch.h"
#include "generalStruct.h"
#include "HeaderQ1.h"
#include "HeaderQ3.h"






pathTree findAllPossiblePaths(boardPos  start, movesArray** moves, char** board)
{
	boardPosArray** validPosition = validMoves(moves, board);
	pathTree res;

	ParentList parentList;
	makeEmptyParentList(&parentList);

	//creating and updating the root tree node
	treeNodeListCell* resListCell;
	resListCell = createTreeCellNode(start);
	
	//creating and updating the parents list node
	ParentListNode* parent;
	parent = (ParentListNode*)safeMalloc(sizeof(ParentListNode));
	parent->child = NULL;
	parent->CurrNode = resListCell;

	parentList.head = parentList.tail = parent;

	resListCell->node->next_possible_positions = findAllPossiblePathsRec(&parentList, validPosition);

	res.head = resListCell->node;//updating the head of the list

	free(resListCell);
	freeBoardPosArrayPP(validPosition);
	return res;
}


treeNodeListCell* findAllPossiblePathsRec(ParentList* list, boardPosArray** validPos)
{
	int i = 0;
	char fatherRow = (list->tail->CurrNode->node->position[0]) - 'A';
	char fatherCol = list->tail->CurrNode->node->position[1] - 1;
	treeNodeListCell* currNodeCell, * firstChild = NULL;
	treeNode* currNode, * oldFather;
	ParentListNode* newFather, * oldFatherPList = list->tail;
	bool isNotFirstChild = false;

	oldFather = list->tail->CurrNode->node;

	if (validPos[fatherRow][fatherCol].size == 0) // the father has no child 
	{
		return NULL;
	}
	else
	{
		newFather = (ParentListNode*)safeMalloc(sizeof(ParentListNode)); //allocate new father for father list
		for (i = 0; i < validPos[fatherRow][fatherCol].size; i++)
		{
			if (!isInParentList(*list, validPos[fatherRow][fatherCol].positions[i], isNotFirstChild)) //if next child not in ParentList , avoid circle
			{
				currNodeCell = createTreeCellNode(validPos[fatherRow][fatherCol].positions[i]);
				currNode = currNodeCell->node;

				if (isNotFirstChild) //the new father is not the first child of old father
				{
					list->tail->CurrNode->next = currNodeCell; // connect between the brothers
				}
				else // its the first child // the newFather IS the first child of oldFather
				{
					firstChild = currNodeCell;
				}
				changeParentsTail(list, newFather, currNodeCell, !isNotFirstChild);
				isNotFirstChild = true; // its the first child // the newFather IS the first child of oldFather

				currNode->next_possible_positions = findAllPossiblePathsRec(list, validPos);
			}
		}
		oldFatherPList->child = NULL;
		list->tail = oldFatherPList;

		free(newFather); //free the Parents list node
		return firstChild;
	}
}


bool isInParentList(ParentList list, boardPos position, bool isBrothers)
{
	bool res = false;
	boardPos headPos;

	if (!isBrothers) // if list tail is the father
	{
		while (list.head != NULL)
		{
			headPos[0] = ((list.head)->CurrNode->node->position)[0];
			headPos[1] = ((list.head)->CurrNode->node->position)[1];
			
			if ((headPos[0] == position[0]) && (headPos[1] == position[1]))
			{
				return true;
			}
			list.head = list.head->child;
		}
	}
	else // list tail is the brother
	{
		while (list.head->child != NULL)
		{
			headPos[0] = ((list.head)->CurrNode->node->position)[0];
			headPos[1] = ((list.head)->CurrNode->node->position)[1];
			
			if ((headPos[0] == position[0]) && (headPos[1] == position[1]))
			{
				return true;
			}
			list.head = list.head->child;
		}
	}
	return res;
}


void changeParentsTail(ParentList* list, ParentListNode* newTail, treeNodeListCell* currNodeCell, bool isFirstChild)
{
	newTail->CurrNode = currNodeCell;
	newTail->child = NULL; // newTail->next=NULL

	if (isFirstChild)
	{
		list->tail->child = newTail;
		list->tail = newTail;
	}
}


treeNodeListCell* createTreeCellNode(boardPos placeInboard)
{
	treeNodeListCell* res;

	res = (treeNodeListCell*)safeMalloc(sizeof(treeNodeListCell));
	res->node = (treeNode*)safeMalloc(sizeof(treeNode));

	(res->node->position)[0] = placeInboard[0];
	(res->node->position)[1] = placeInboard[1];
	res->node->next_possible_positions = NULL;
	res->next = NULL;
	
	return res;
}


void makeEmptyParentList(ParentList* lst)
{
	lst->head = lst->tail = NULL;
}
















