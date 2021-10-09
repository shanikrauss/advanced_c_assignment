#ifndef HEADERQ6_H
#define HEADERQ6_H
#include "generalStruct.h"

#define FILE_NOT_EXIST -1
#define PATH_NOT_VALID 1
#define MAX_VALID_PATH 2
#define VALID_PATH 3



/*
The function gets boardPosArray array
And creates a linked list of movesList according to the locations in the array.*/
movesList* createMovesList(boardPosArray* posArr);

/*
The function gets:
name_file - The name of a binary file that contains a list of locations in the format specified in section 5.
moves is a two-dimensional array of game board. In any given cell an array of possible moves from the same cell.
board is a game board of the same size as moves

The function creates an array with the locations from the binary file in accordance with the format of Section 5.
If the array size is 0 - that is, the file had an empty set of locations (which is valid) then the function returns that the set is valid ie 3.
Otherwise, the function narrows the array so that each location appears only once (the duplicate is erased from the array end,the position reamain in the same order).
Then the function checks with the function from section 1 whether the positions in the array are valid.
If not, the function returns 1.
Otherwise, the function prints the board with the function from Section 2.
 If the board is full the function returns 2, otherwise 3
*/
int checkAndDisplayPathFromFile(char* file_name, movesArray** moves, char** board);

/*
The function gets an array of boardPosArray
The function returns a reduce array so that each location appears exactly once.
The twice-appearing locations are deleted from the end, so the locations still remain in the same order as they were at the beginning*/
void reduceBoardPosArray(boardPosArray* arr);

/*
The function accepts an array of boardPosArray
The function checks if there is a location that appears more than once, if so it updates that location in array to a space - ' ' */
void putSpaceInDuplicatePos(boardPosArray* arr);


/*
The function gets an array of boardPosArray
The function returns a reduce array that only shows positions without spaces*/
void reducePosArray(boardPosArray* arr);

/*
The function gets a binary file name,
The function reads the file and creates an array of locations according to the locations in the file
(the file is read according to the format specified in section 5)*/
boardPosArray* decodePosFromFile(FILE* file);

/*
The function gets byte and boardPos *
the function decodes byte according to the format defined in Q5 and updates boardPos* accordingly.*/
void case1(BYTE byte, boardPos* arr);

/*
The function gets byte and boardPos *
the function decodes byte according to the format defined in Q5 and updates boardPos* accordingly.*/
void case2(BYTE byte1, BYTE byte2, boardPos* arr);

/*
The function gets byte and boardPos *
the function decodes byte according to the format defined in Q5 and updates boardPos* accordingly.*/
void case3(BYTE byte1, BYTE byte2, boardPos* arr);

/*
The function gets byte and boardPos *
the function decodes byte according to the format defined in Q5 and updates boardPos* accordingly.*/
void case4(BYTE byte, boardPos* arr);

/*
The function checks whether the locations in the array - boardPostArray * are valid according to the array boardPosArray **.
is they are valid return true, else false*/
bool checkIfPosArrPathIsValid(boardPosArray* posArrFromFile, boardPosArray** validPosArr, char** starsBoard);

/*
The function gets a location, and an array of location  and checks if the location appears in there.
if so returns true, else false*/
bool isCellInPosArr(boardPosArray arr, boardPos cell);


/*
The function frees the dynamically allocated memory*/
void freeMemory(boardPosArray* posArrFromFile, boardPosArray** validPosArr, movesList* movesLst);



#endif