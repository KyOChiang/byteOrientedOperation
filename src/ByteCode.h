#ifndef __BYTECODE_H__
#define __BYTECODE_H__

typedef enum {
				ACCESS = -5,
				BANKED,
				F,
				W
			 }Operand;
			 
typedef enum { NO_ERROR,
			   ERR_INVALID_OPERAND1,
			   ERR_INVALID_OPERAND2,
			   ERR_INVALID_OPERAND3,
			   ERR_INVALID_BSR
} ExceptionError;

typedef enum { MOVWF,
			   RLNCF,
			   SUBFWB
} Mnemonic;

typedef struct {
	Mnemonic	mnemonic;
	char *name;
} Instruction;

typedef struct {
	Instruction instruction;
	int operand1;
	int operand2;
	int operand3;
	int absoluteAddress;
} Bytecode;

#endif // __BYTECODE_H__