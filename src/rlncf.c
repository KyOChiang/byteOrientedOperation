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
	
	if(code->operand1 > 0x00 && code->operand1 <= 0xFF){
		//To check that bit 7 is 1 or not, because is a signed char
		//If bit 7 is 1, the value will read as negative value
		if(FSR[code->operand1]<0){
			if(code->operand2 == F||code->operand2 == 1||code->operand2 == -1){
				if(code->operand3 == BANKED||code->operand3 == -4||code->operand3 == -1){
					FSR[code->operand1+(FSR[BSR]<<8)] = (FSR[code->operand1]<<1) + 0x01;
					if(FSR[code->operand1+(FSR[BSR]<<8)] < 0)
						FSR[STATUS] = 0x10;
					else if(FSR[code->operand1+(FSR[BSR]<<8)] == 0)
						FSR[STATUS] = 0x04;
				}
				else if(code->operand3 == ACCESS||code->operand3 == -5){
					if(code->operand1>=0x80){
						FSR[code->operand1+0xF00] = (FSR[code->operand1]<<1) + 0x01;
						if(FSR[code->operand1+0xF00] < 0)
							FSR[STATUS] = 0x10;
						else if(FSR[code->operand1+0xF00] == 0)
							FSR[STATUS] = 0x04;
					}
					if(code->operand1<0x80){
						FSR[code->operand1] = (FSR[code->operand1]<<1) + 0x01;
						if(FSR[code->operand1] < 0)
							FSR[STATUS] = 0x10;
						else if(FSR[code->operand1] == 0)
							FSR[STATUS] = 0x04;
					}
				}
			}
			else if(code->operand2 == W||code->operand2 == 0){
				FSR[WREG] = (FSR[code->operand1]<<1) + 0x01;
				if(FSR[WREG] < 0)
					FSR[STATUS] = 0x10;
				else if(FSR[WREG] == 0)
					FSR[STATUS] = 0x04;
			}
			else if(code->operand2 == ACCESS){
				FSR[WREG] = (FSR[code->operand1]<<1) + 0x01;
				if(FSR[WREG] < 0)
					FSR[STATUS] = 0x10;
				else if(FSR[WREG] == 0)
					FSR[STATUS] = 0x04;
			}
			else if(code->operand2 == BANKED){
				FSR[code->operand1] = (FSR[code->operand1]<<1) + 0x01;
				if(FSR[code->operand1] < 0)
					FSR[STATUS] = 0x10;
				else if(FSR[code->operand1] == 0)
					FSR[STATUS] = 0x04;
			}
		}
		else{
			if(code->operand2 == F||code->operand2 == 1||code->operand2 == -1){
				if(code->operand3 == BANKED||code->operand3 == -4||code->operand3 == -1){
					FSR[code->operand1+(FSR[BSR]<<8)] = (FSR[code->operand1]<<1) + 0x00;
					if(FSR[code->operand1+(FSR[BSR]<<8)] < 0)
						FSR[STATUS] = 0x10;
					else if(FSR[code->operand1+(FSR[BSR]<<8)] == 0)
						FSR[STATUS] = 0x04;
				}
				else if(code->operand3 == ACCESS||code->operand3 == -5){
					if(code->operand1>=0x80){
						FSR[code->operand1+0xF00] = (FSR[code->operand1]<<1) + 0x00;
						if(FSR[code->operand1+0xF00] < 0)
							FSR[STATUS] = 0x10;
						else if(FSR[code->operand1+0xF00] == 0)
							FSR[STATUS] = 0x04;
					}
					if(code->operand1<0x80){
						FSR[code->operand1] = (FSR[code->operand1]<<1) + 0x00;
						if(FSR[code->operand1] < 0)
							FSR[STATUS] = 0x10;
						else if(FSR[code->operand1] == 0)
							FSR[STATUS] = 0x04;
					}
				}
			}
			else if(code->operand2 == W||code->operand2 == 0){
				FSR[WREG] = (FSR[code->operand1]<<1) + 0x00;
				if(FSR[WREG] < 0)
					FSR[STATUS] = 0x10;
				else if(FSR[WREG] == 0)
					FSR[STATUS] = 0x04;
			}
			else if(code->operand2 == ACCESS){
				FSR[WREG] = (FSR[code->operand1]<<1) + 0x00;
				if(FSR[WREG] < 0)
					FSR[STATUS] = 0x10;
				else if(FSR[WREG] == 0)
					FSR[STATUS] = 0x04;
			}
			else if(code->operand2 == BANKED){
				FSR[code->operand1] = (FSR[code->operand1]<<1) + 0x00;
				if(FSR[code->operand1] < 0)
					FSR[STATUS] = 0x10;
				else if(FSR[code->operand1] == 0)
					FSR[STATUS] = 0x04;
			}
		}
		
	}
	else
		Throw(ERR_INVALID_OPERAND1);
}