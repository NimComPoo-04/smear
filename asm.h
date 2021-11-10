#ifndef _ASM_H_
#define _ASM_H_

#include <stdio.h>
#include <stdint.h>

uint8_t *assemble(FILE *f) ;
void disassemble(const uint8_t *val) ;

#endif
