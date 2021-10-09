#ifndef HEADERQ1_H
#define HEADERQ1_H
#include "generalStruct.h"



/*
The function receives an array of locations and spaces char- ' '  and their size.
The function narrows the array and returns an array only with the position without spaces- ' '
And updates the new size*/
void reduceArray(movesArray* PosMoves, int newSize);


/*The function gets:
moves is a two-dimensional array of game board size. In eac  cell there is an array of possible moves from the cell.
board is a game board the same size as moves.
The function removes from each cell in the array the moves which are invalid.
The function returns an array so that each cell in the returned array is an array
Of the valid position that can be moved from this cell.*/
boardPosArray** validMoves(movesArray** moves, char** board);


/*The function gets the board a two-dimensional array that contains the stars positions,
an array of moves from a cellAnd columnand row value
The function checks whether the new move is valid,
If the move is valid it calculates the position by move and enters it to an array.
If not, the function deletes this cell from the array.
The function returns the array of valid position*/
boardPosArray checkValidCell(char** board, movesArray* PosMoves, int cellRow, int cellCol);




#endif