#ifndef HEADERQ5_H
#define HEADERQ5_H

#define isAlpha(c) (((((c) >= 'a') && ((c) <= 'z')) || (((c) >= 'A') && ((c) <= 'Z'))) ? true : false)

/*The function receives a character and converts it to a integer*/
char transCharToNum(char ch);

/*
The function gets a binary file name and an array of position and saves the position in the file as described in the format of the project.
every positions in the array (row or column) is saved in 3 bits
*/
void saveListToBinFile(char* file_name, boardPosArray* pos_arr);

/*The function encodes the values it receives according to the format specified in the project, and returns a coded byte*/
BYTE createByteCase1(unsigned char num1, unsigned char num2);

/*The function encodes the values it receives according to the format specified in the project, and returns a coded byte*/
BYTE createByteCase2a(unsigned char num1, BYTE curByte);

/*The function encodes the values it receives according to the format specified in the project, and returns a coded byte*/
BYTE createByteCase2b(unsigned char num1, unsigned char num2);

/*The function encodes the values it receives according to the format specified in the project, and returns a coded byte*/
BYTE createByteCase3a(unsigned char num1, unsigned char num2, BYTE curByte);

/*The function encodes the values it receives according to the format specified in the project, and returns a coded byte*/
BYTE createByteCase3b(unsigned char num1);

/*The function encodes the values it receives according to the format specified in the project, and returns a coded byte*/
BYTE createByteCase4(unsigned char num1, unsigned char num2, BYTE curByte);


#endif 
