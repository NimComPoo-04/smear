#ifndef _ASM_H_
#define _ASM_H_

#include <stdint.h>

#include "vm.h"
#include "parser.h"

/*
	send in values from back to front
	first one is the function itself
	return value would be pushed onto the stack
*/

enum
{
	KW_NONE,
	KW_IF,
	KW_REP,
	KW_DEF
} ;

typedef struct
{
	uint8_t *value ;
	uint32_t len ;
} asm_t ;

asm_t asm_create(void) ;
void asm_add(asm_t *a, uint8_t x) ;
void asm_rem(asm_t *a) ;
void asm_delete(asm_t *a) ;

asm_t assemble(node_t *n) ;
void disassemble(vm_t *m) ;

void asm_lst(asm_t *x, node_t *n) ;

#endif
