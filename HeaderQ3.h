#ifndef HEADERQ3_H
#define HEADERQ3_H
#include "generalStruct.h"


//The function gets moves whoch is a two-dimensional array of game board, that every cell has an array of possible moves from the same cell.
//The function gets start position, and board (array of strings) that contains stars in some of the cells.
//The function removes from the input moves array (movesArray**) the moves that are illegal,
//using the function from Q1,(that go outside the board, or a move to cell that contains '*').
//The function builds a tree that presents all the possible and llegal pathes that start from the start position.
//the root will be the the start position (input).
//for every node in the tree, its childern will be all the position that are one move away 
//from the node's position according the moves array (the tree node has a list of its children).
//while the function builds the tree it avoids circles of pathes.
//The function returns the tree of pathes that it creates.
pathTree findAllPossiblePaths(boardPos start, movesArray** moves, char** board);


//The recursive function gets a parents list pointer and a boardPosArray** of valid possitions.
//The function builds a tree that presents all the possible and llegal pathes that start from the start position.
//the root will be the the start position (input).
//for every node in the tree, its childern will be all the position that are one move away 
//from the node's position according the moves array (the tree node has a list of its children).
//while the function builds the tree it avoids circles of pathes by creating a parents list,
//and checking if the new tree node was one of its own parent.
//The function returns the root of the tree.
treeNodeListCell* findAllPossiblePathsRec(ParentList* list, boardPosArray** validPos);



//The function gets Parents list, position, and a bolian element.
//the faunction checks if the input position exist in the input parents list.
//if so the function returns true, else false.
bool isInParentList(ParentList list, boardPos position, bool isBrothers);


//The function gets parents list pointer, a new tail pointer for the list, current cell node and a bolian element. 
//the function the function upadates the new tail pointer to be the new tail of the input parent list.
void changeParentsTail(ParentList* list, ParentListNode* newTail, treeNodeListCell* currNodeCell, bool isFirstChild);


//The function gets a position.
//the function allocates a tree node list cell and updates its position according the input position.
//it returns the allocated node.
treeNodeListCell* createTreeCellNode(boardPos placeInboard);


//The function make an empty Parent List
void makeEmptyParentList(ParentList* lst);

#endif 

