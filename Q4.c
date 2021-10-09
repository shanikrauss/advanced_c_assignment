#define _CRT_SECURE_NO_WARNINGS
#include "generalStruct.h"
#include "ch.h"
#include "HeaderQ3.h"
#include "HeaderQ4.h"



movesList* findPathCoveringAllBoard(boardPos start, movesArray** moves, char** board)
{
	int starsAmount = countStarsInBoard(board);
	int maxPathLen = (COLS * ROWS) - starsAmount - 1;
	int listLenRes = 0;
	movesList* list = (movesList*)safeMalloc(sizeof(movesList));
	pathTree root;


	root = findAllPossiblePaths(start, moves, board);

	list->head = findPathCoveringAllBoardRec(root.head, list, maxPathLen, &listLenRes);

	if (listLenRes != maxPathLen)
	{
		free(list);
		return NULL;
	}
	else
	{
		list->head->prev = NULL; // update prev of head
	}

	freeTree(root.head);

	return list;
}



moveCell* findPathCoveringAllBoardRec(treeNode* node, movesList* list, int maxPathLen, int* resLen)
{
	bool static flag = false;
	int static len = 0;
	moveCell* newMoveCell = NULL;

	if (node->next_possible_positions == NULL)
	{
		return NULL;
	}
	else
	{
		newMoveCell = (moveCell*)safeMalloc(sizeof(moveCell)); // new child gen
		len++; // new generation

		while ((node->next_possible_positions != NULL) && (!flag))
		{
			updateMoveCell(node, newMoveCell);
			newMoveCell->next = findPathCoveringAllBoardRec(node->next_possible_positions->node, list, maxPathLen, resLen);

			if ((newMoveCell->next == NULL) && (len == maxPathLen)) //found valid path 
			{
				updateTailMovesList(list, newMoveCell); //update the last child to be the tail of list
				flag = true;
			}

			if ((newMoveCell->next != NULL) && (flag)) // update prev if found a valid path
			{
				newMoveCell->next->prev = newMoveCell;
			}
			node->next_possible_positions = node->next_possible_positions->next; //did not find a valid path,looking for a path in the next possible position (my brother)
		}//while

		if (!flag) // didnt find a valid path in this generation
		{
			len--;
			free(newMoveCell);
		}

		*resLen = len; //update the tree high
		if (len == 0)
		{
			return NULL;
		}
		return newMoveCell;
	}
}

void updateTailMovesList(movesList* list, moveCell* newMoveCell)
{
	list->tail = newMoveCell;
}



void updateMoveCell(treeNode* node, moveCell* newMoveCell)
{
	newMoveCell->move.rows = ((node->next_possible_positions->node->position)[0] - 'A') - ((node->position)[0] - 'A');
	newMoveCell->move.cols = ((node->next_possible_positions->node->position)[1]) - ((node->position)[1]);
}



void freeTreeRec(treeNodeListCell* cellNode)
{
	treeNodeListCell* temp;

	if (cellNode == NULL)
	{
		return;
	}
	if (cellNode->node->next_possible_positions == NULL)
	{
		if (cellNode->next == NULL)
		{
			free(cellNode->node);
			free(cellNode);
		}
		else
		{
			temp = cellNode->next;
			free(cellNode->node);
			free(cellNode);
			freeTreeRec(temp);
		}
	}
	else
	{
		freeTreeRec(cellNode->node->next_possible_positions);

		temp = cellNode->next;
		free(cellNode->node);
		free(cellNode);
		freeTreeRec(temp);
	}
}


void freeTree(treeNode* head)
{
	freeTreeRec(head->next_possible_positions);
	free(head);
}




