#define _CRT_SECURE_NO_WARNINGS
#include "Q5.h"

/*This function will save a list of moves to a binary file in a compressed way (Q5)*/
void saveListToBinFile(char* file_name, boardPosArray* pos_array) {
	unsigned int i, j, write, curBit, bytesNum;									//Decalring variables
	char* res, byte, tmpByte, mask, tmpMask;
	FILE* fp;
	bytesNum = numOfBytes(pos_array->size, 6);									//Initializing variables
	res = (char*)calloc(bytesNum, sizeof(char));
	generalCheck(res, 'a');
	fp = fopen(file_name, "wb");
	generalCheck(fp, 'f');
	fwrite(&pos_array->size, sizeof(short int), 1, fp);							//Starts writing to the file
	for (i = 0, curBit = 0, write = 0, byte = 0; i < pos_array->size; i++) {	//Running on the array to compress it
		for (j = 0; j < 2; j++) {
			if (curBit == 8) {
				res[write++] = byte;
				byte = 0;
				curBit = 0;
			} if (8 - curBit >= 3) {
				mask = pos_array->positions[i][j] - (j == 0 ? 'A' : 1);
				mask = mask << curBit;
				tmpByte = byte | mask;
				byte = tmpByte;
				curBit += 3;
			} else {
				mask = pos_array->positions[i][j] - (j == 0 ? 'A' : 1);
				tmpMask = mask;
				tmpMask = tmpMask << curBit;
				tmpByte = byte | tmpMask;
				byte = tmpByte;
				res[write++] = byte;
				byte = 0;
				curBit = overFlowedBits(curBit, 3, sizeof(char));
				mask = mask >> (3 - curBit);
				tmpByte = byte | mask;
				byte = tmpByte;
			}
		}
	}
	if (curBit != 0)
		res[write++] = byte;
	fwrite(res, sizeof(char), write, fp);
	fclose(fp);
}//saveListToBinFile

/*This function will see if we overflowed from a byte*/
unsigned int overFlowedBits(unsigned int posBit, unsigned int objBitSize, unsigned int size_t) {
	int res; 									//Declaring variables
	res = posBit + objBitSize - (size_t * 8);
	if (res <= 0)
		return 0;
	else
		return (unsigned int)res;
}//overFlowedBits

/*This function will calculate the amount of bytes*/
unsigned int numOfBytes(unsigned int numOfElements, unsigned int bitsForElement) {
	//Declaring variables
	unsigned int res;
	res = numOfElements * bitsForElement;
	//Calculating
	if (res % 8 == 0)
		res /= 8;
	else {
		res /= 8;
		res++;
	}
	return res;
}//numOfBytes


