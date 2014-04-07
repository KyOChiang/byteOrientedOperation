#include <stdio.h>
#include "CException.h"
#include "ByteCode.h"
#include "subfwb.h"

char FSR[0x1000];

int subfwb(Bytecode *code){
	
	if(FSR[BSR] < 0x00 || FSR[BSR] > 0x0F)
		Throw(ERR_INVALID_BSR);
		
	if(code->operand2 == BANKED||code->operand2 == ACCESS||code->operand2 == -4||code->operand2 == -5){
		if(code->operand3 == BANKED||code->operand3 == ACCESS||code->operand3 == -4||code->operand3 == -5)
			Throw(ERR_INVALID_OPERAND3);
	}
			
	if(code->operand2 == F||code->operand2 == W||code->operand2 == -2||code->operand2 == -3){
		if(code->operand3 == F||code->operand3 == W||code->operand3 == -2||code->operand3 == -3)
			Throw(ERR_INVALID_OPERAND2);
	}
	
	return (code->absoluteAddress = code->absoluteAddress + 1);
}