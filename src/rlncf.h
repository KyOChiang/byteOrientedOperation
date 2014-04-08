#ifndef _RLNCF_H_
#define _RLNCF_H_

extern char FSR[];

#define WREG 0xFE8
#define BSR 0xFE0
#define STATUS 0xFD8

int rlncf(Bytecode *code);

#endif // RLNCF_H_