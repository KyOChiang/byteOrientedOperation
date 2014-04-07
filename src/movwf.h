#ifndef _MOVWF_H_
#define _MOVWF_H_

extern char FSR[];

#define WREG 0xFE8
#define BSR 0xFE0
#define STATUS 0xFD8

int movwf(Bytecode *code);

#endif // _MOVWF_H_