#define _CRT_SECURE_NO_WARNINGS
#include "ch.h"
#include "generalStruct.h"
#include "HeaderQ5.h"



void saveListToBinFile(char *file_name, boardPosArray *pos_arr)
{
	int i = 0;
	short int sizeOfArr=0;
	BYTE posAsByte = 0;
	FILE* bf;

	sizeOfArr = (short int)(pos_arr->size);
	bf = fopen(file_name, "wb");
	checkOpeningFile(bf);
	
	fwrite(&sizeOfArr, sizeof(short int), 1, bf);

	for (i = 0; i < sizeOfArr; i++)
	{
		if (i % 4 == 0)
		{
			posAsByte = createByteCase1(transCharToNum(pos_arr->positions[i][0]), transCharToNum(pos_arr->positions[i][1])); 
		}
		if (i % 4 == 1)
		{
			posAsByte = createByteCase2a(transCharToNum(pos_arr->positions[i][0]), posAsByte); 
			fwrite(&posAsByte, sizeof(unsigned char), 1, bf);
			posAsByte = createByteCase2b(transCharToNum(pos_arr->positions[i][0]), transCharToNum(pos_arr->positions[i][1]));
		}
		if (i % 4 == 2)
		{
			posAsByte = createByteCase3a(transCharToNum(pos_arr->positions[i][0]), transCharToNum(pos_arr->positions[i][1]), posAsByte); 
			fwrite(&posAsByte, sizeof(unsigned char), 1, bf);
			posAsByte = createByteCase3b(transCharToNum(pos_arr->positions[i][1])); 
		}
		if (i % 4 == 3)
		{
			posAsByte = createByteCase4(transCharToNum(pos_arr->positions[i][0]), transCharToNum(pos_arr->positions[i][1]), posAsByte); 
			fwrite(&posAsByte, sizeof(unsigned char), 1, bf);
		}
	}

	if ((i - 1) % 4 != 3)
	{
		fwrite(&posAsByte, sizeof(unsigned char), 1, bf);
	}

	fclose(bf);
}


char transCharToNum(char ch)
{
	char res;
	if (isAlpha(ch))
	{
		res = ch - 'A';
	}
	else
	{
		res = ch - 1;
	}
	return res;
}


BYTE createByteCase1(unsigned char num1, unsigned char num2) // i%4 == 0 
{
	unsigned char res=0;
	num1 = num1 << 5;
	num2 = num2 << 2;

	res = (num1 | num2);
	return res;
}

BYTE createByteCase2a(unsigned char num1, BYTE curByte) // i%4 == 1 
{
	unsigned char res = 0;
	num1 = num1 >> 1;

	res = (curByte | num1);
	return res;
}

BYTE createByteCase2b(unsigned char num1, unsigned char num2) // i%4 == 1 
{
	unsigned char res = 0;
	num1 = num1 << 7;
	num2 = num2 << 4;

	res = (num1 | num2);
	return res;
}

BYTE createByteCase3a(unsigned char num1, unsigned char num2, BYTE curByte) // i%4 == 2 
{
	unsigned char res = 0;
	num1 = num1 << 1;
	num2 = num2 >> 2;

	res = (curByte | num1) | num2;
	return res;
}

BYTE createByteCase3b(unsigned char num1) // i%4 == 2 
{
	unsigned char res = 0;
	num1 = num1 << 6;

	res = res | num1;
	return res;
}

BYTE createByteCase4(unsigned char num1, unsigned char num2, BYTE curByte) // i%4 == 3
{
	unsigned char res = 0;
	num1 = num1 << 3;

	res = (curByte | num1) | num2;
	return res;
}



















