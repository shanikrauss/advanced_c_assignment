#ifndef HEADERQ2_H
#define HEADERQ2_H
#include "generalStruct.h"



//The function gets moves list pointer, start position, and board (array of strings) that contains stars in some of the cells.
//The function prints a board game.
//'#' in the start position.
//'*' in the cells that contains stars.
//digit that presents the serial place of the position in the Movelist, also, position that contain, '*' or '#',
//will skip that move to the next one in the moves list, and delete it.
//The function will return the amount of the moves that we've deleted.
int display(movesList* moves_list, boardPos start, char** board);

//The function gets a moves list pointer,and pointer of the node that need to be deleted.
//the function deletes the input node from the input node list, and free it. it updates the list's head and tail if needed.
void removeCellfromMovesList(movesList* lst, moveCell* node);

//The function gets board[][] that contains in every cell a differenct char:
//'#' in the start position.
//'*' in the cells that contains stars.
//digit that presents the serial place of the position in the Movelist.
//the function prints the game board's frame lines, and the inside lines according to the COLS and ROWS
void printTheBoard(char board[ROWS][COLS]);

//The function prints the game board's frame line according to the COLS
void printFrameLine();
	
//The function gets the resBoard that need to be printed,  start position, and board (array of strings) that contains stars in some of the cells.
// The function updates the content of the input resBoard according the start and board:
//'#' in the start position.
//'*' in the cells that contains stars.
void updatePrintedBoard(char resBoard[ROWS][COLS], char** board, boardPos start);

/*

The function updates the move that needs to be deleted
*/
moveCell* updateDeleteMoveCell(moveCell* currHead, moveCell* tail);


#endif