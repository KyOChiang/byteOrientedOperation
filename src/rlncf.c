#include <stdio.h>
#include "CException.h"
#include "ByteCode.h"
#include "rlncf.h"

char FSR[0x1000];


/*  Before rlncf: file reg [7]-[6]-[5]-[4]-[3]-[2]-[1]-[0]
 *    
 *	After rlncf: file reg [6]-[5]-[4]-[3]-[2]-[1]-[0]-[7]
 *
 *	Again rlncf: file reg [5]-[4]-[3]-[2]-[1]-[0]-[7]-[6]
 */

void rlncf(Bytecode *code){
	if(code->operand1 > 0x00 && code->operand1 <= 0xFF){
		//To check that bit 7 is 1 or not, because is a signed char
		//If bit 7 is 1, the value will read as negative value
		if(FSR[code->operand1]<0){
			if(code->operand2 == F||code->operand2 == 1||code->operand2 == -1){
				FSR[code->operand1] = (FSR[code->operand1]<<1) + 0x01;
			}
			else if(code->operand2 == W||code->operand2 == 0)
				FSR[WREG] = (FSR[code->operand1]<<1) + 0x01;
		}
		else{
			if(code->operand2 == F||code->operand2 == 1||code->operand2 == -1){
				FSR[code->operand1] = (FSR[code->operand1]<<1) + 0x00;
			}
			else if(code->operand2 == W||code->operand2 == 0)
				FSR[WREG] = (FSR[code->operand1]<<1) + 0x00;
		}
	}
	else
		Throw(ERR_INVALID_OPERAND1);
}