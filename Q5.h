#ifndef Q5_H
#define Q5_H

///Including

#include "Q1.h"
#include "Q2.h"
#include "Q3.h"
#include "Q4.h"

#include <stdio.h>
#include <stdlib.h>

///Functions

void saveListToBinFile(char* file_name, boardPosArray* pos_array);

unsigned int numOfBytes(unsigned int numOfElements, unsigned int bitsForElement);

unsigned int overFlowedBits(unsigned int posBit, unsigned int objBitSize, unsigned int size_t);

#endif