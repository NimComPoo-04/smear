#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "lexer.h"
#include "vm.h"

int main(void)
{
	char prog[] = "10 20 (* 10 10 (+ 32 78))" ;

	uint8_t assembly[] =
	{
		VM_LDX,
		0x01,
		0x00,
		0x00,
		0x00,
		VM_LDY,
		0x01,
		0x00,
		0x00,
		0x00,
		VM_ADD,
		VM_PUSH,
		VM_INT,
		VM_MOV,
		VM_HALT
	} ;

	lexer_t l = lexer_create(prog) ;
	//lexer_debug_prnt(&l) ;
	lexer_reset(&l) ;

	node_t *n = parse(&l) ;
	//parser_debug_prnt(n, 0) ;

	vm_t v = vm_create() ;
	vm_load(&v, assembly, sizeof assembly / sizeof(uint8_t)) ; 

	while(getc(stdin) != 'q')
	{
		vm_step(&v) ;
		vm_dump(&v) ;
	}

	vm_delete(&v) ;
	node_delete(n) ;
	lexer_delete(&l) ;
}
