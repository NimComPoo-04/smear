#include <stdlib.h>
#include "compiler.h"
#include "vm.h"

compiler_t compiler_create(node_t *c)
{
	return (compiler_t){c, NULL, 0} ;
}

void compiler_exec(compiler_t *c)
{
	/*
	 * ;; FIBO
	 *
	 * LDI A 0
	 * LDI B 1
	 *
	 * lb: LOG
	 *
	 * LDR C A
	 * ADD C B
	 * LDR B A
	 * LDR A C
	 *
	 * JMP lb
	 * HALT
	 */

	compiler_add(c, VM_LDI) ;
	compiler_add(c, REG_A) ;
	compiler_add(c, 0) ;
	compiler_add(c, 0) ;

	compiler_add(c, VM_LDI) ;
	compiler_add(c, REG_B) ;
	compiler_add(c, 1) ;
	compiler_add(c, 0) ;

	uint16_t f = c->len ;
	compiler_add(c, VM_LOG) ;

	compiler_add(c, VM_LDR) ;
	compiler_add(c, REG_C | (REG_A << 4)) ;
	compiler_add(c, VM_ADD) ;
	compiler_add(c, REG_C | (REG_B << 4)) ;

	compiler_add(c, VM_LDR) ;
	compiler_add(c, REG_B | (REG_A << 4)) ;
	compiler_add(c, VM_LDR) ;
	compiler_add(c, REG_A | (REG_C << 4)) ;

	compiler_add(c, VM_JMP) ;
	compiler_add(c, f & 0xFF) ;
	compiler_add(c, f >> 8) ;

	compiler_add(c, VM_HALT) ;
}

void compiler_delete(compiler_t *c)
{
	free(c->bin) ;
}

void compiler_add(compiler_t *c, uint8_t val)
{
	if(c->len % 16 == 0)
		c->bin = realloc(c->bin, 16) ;
	c->bin[c->len] = val ;
	c->len++ ;
}
