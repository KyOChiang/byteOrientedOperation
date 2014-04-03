#ifndef _SUBFWB_H_
#define _SUBFWB_H_

extern char FSR[];

#define WREG 0xFE8
#define BSR 0xFE0
#define STATUS 0xFD8

void subfwb(Bytecode *code);

#endif // _SUBFWB_H_