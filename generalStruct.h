#ifndef GENERAL_H
#define GENERAL_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define COLS 5
#define ROWS 4

typedef unsigned char BYTE;

typedef struct _move {
	char rows, cols;
} Move;

typedef struct _moveCell {
	Move move;
	struct _moveCell* next, * prev;
} moveCell;

typedef struct _movesList {
	moveCell* head;
	moveCell* tail;
} movesList;

typedef char boardPos[2];

typedef struct _movesArray {
	unsigned int  size;
	Move* moves;
} movesArray;

typedef struct _boardPosArray {
	unsigned int  size;
	boardPos* positions;
} boardPosArray;

typedef struct  _treeNodeListCell treeNodeListCell;

typedef struct _treeNode {
	boardPos    position;
	treeNodeListCell* next_possible_positions;
} treeNode;

typedef  struct  _treeNodeListCell {
	treeNode* node;
	struct _treeNodeListCell* next;
} treeNodeListCell;

typedef  struct  _pathTree {
	treeNode* head;
} pathTree;


typedef  struct  _ParentListNode {
	treeNodeListCell* CurrNode; // "list node"
	struct _ParentListNode* child; //" *next " 
} ParentListNode;

//The struct ParentsList holds the parents list of every node in the tree
typedef  struct  ParentList {
	ParentListNode* head;
	ParentListNode* tail;
} ParentList;

/*The function checks memory allocation of the malloc function and return the pointer*/
void* safeMalloc(size_t size);
/*
/*The function checks memory allocation of the calloc function and return the pointer*/
void* safeCalloc(size_t num, size_t size);

/*The function checks memory allocation of the realloc function and return the pointer*/
void* safeRealloc(void* ptr, size_t size);

/*The function receives a numberand returns it as a letter*/
char transNumToLetter(int num);

/*
The function receives a row and column
and returns true if the position is out of board
else false */
bool outBoard(int newCol, int newRow);

//The function free the input boardPosArray* 
void freeBoardPosArrayP(boardPosArray* posArr);

//The function free the input boardPosArray**
void freeBoardPosArrayPP(boardPosArray** posArr);

//The function free the input moves list
void freeMovesList(movesList* movesLst);

/*The function gets a file pointer and open it. if the openning fail it exit the project*/
void checkOpeningFile(FILE* bf);

/*
The function returns how much stars (*) there is in the board*/
int countStarsInBoard(char** board);



#endif 