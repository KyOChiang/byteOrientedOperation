#include <stdio.h>
#include "CException.h"
#include "ByteCode.h"
#include "movwf.h"

char FSR[0x1000];

void movwf(Bytecode *code){

	if((code->operand2 == F)||(code->operand2 == W)||(code->operand2 == -2)||(code->operand2 == -3))
		Throw(ERR_INVALID_OPERAND2);
	if((code->operand2 == ACCESS)||(code->operand2 == BANKED)||(code->operand2 == 0)||(code->operand2 == 1))
		if((code->operand2 == ACCESS)||(code->operand2 == BANKED)||(code->operand2 == 1)||(code->operand2 == 0)){
			Throw(ERR_INVALID_OPERAND3);
		}
	
	if(code->operand1 > 0x00 && code->operand1 <= 0xFF){
		if(code->operand1>=0x80)
			FSR[code->operand1+0xF00] = FSR[WREG];
		if(code->operand1<0x80)
			FSR[code->operand1] = FSR[WREG];
	}
	else
		Throw(ERR_INVALID_OPERAND1);
}