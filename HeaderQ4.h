#ifndef HEADERQ4_H
#define HEADERQ4_H
#include "generalStruct.h"





//The function finds the a path of positions the covers all th borad, but the stars.
//if the function found a path it  creates and returns a link list of moves from start , else it returns NULL
moveCell* findPathCoveringAllBoardRec(treeNode* node, movesList* list, int maxPathLen, int* resLen);

//The function gets moves which is a two-dimensional array of game board, that every cell has an array of possible moves from the same cell.
//The function gets start position, and board (array of strings) that contains stars in some of the cells.
//Using Q1, checkValidCell() checks whether the new move is valid,
//If the move is valid it calculates the position by move and enters it to an array.
//If not, checkValidCell() deletes this cell from the array.checkValidCell() returns the array of valid position.
//The function finds the a path of positions the covers all th borad, but the stars.
//if the function found a path it  creates and returns a link list of moves from start , else it returns NULL
movesList* findPathCoveringAllBoard(boardPos start, movesArray** moves, char** board);

/*
The function updates the Tail to be newMoveCell */
void updateTailMovesList(movesList* list, moveCell* newMoveCell);

/*
The function updates the value at newMoveCell accordingly to node*/
void updateMoveCell(treeNode* node, moveCell* newMoveCell);



//The recursive function free the tree, start from the cellNode root
void freeTreeRec(treeNodeListCell* cellNode);

//The function free the tree, start from the cellNode root
void freeTree(treeNode* head);


#endif