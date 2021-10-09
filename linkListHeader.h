#ifndef LINK_LIST_H
#define LINK_LIST_H
#include "generalStruct.h"



//The function makes an empty List 
void makeEmptyMovesList(movesList* lst);

//The function gets a char to insert to the end of the list, it inserts it and updates TAIL in LIST
void insertDataToEndMovesList(movesList* lst, Move ch);

//The function creates a new node
moveCell* createMoveCellNode(Move data, moveCell* prev, moveCell* next);

//The function gets an node to insert to the tail of the list, it inserts it and updates TAIL in LIST
void insertMoveCellNodeToTail(movesList* lst, moveCell* newTail);




#endif 
