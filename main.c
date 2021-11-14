#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "lexer.h"
#include "vm.h"
#include "asm.h"

int main(void)
{
	char prog[] = "(rep (+ 1) (+ 3 4))" ;

	printf("+---------------------------------------+\n") ;
	printf("%s\n", prog) ;
	printf("\n+---------------------------------------+\n") ;
	lexer_t l = lexer_create(prog) ;
	lexer_debug_prnt(&l) ;
	lexer_reset(&l) ;

	printf("\n+---------------------------------------+\n") ;
	node_t *n = parse(&l) ;
	parser_debug_prnt(n, 0) ;

	asm_t a = assemble(n) ;
	vm_t m = vm_create() ;

	// like i am weird for doing the sizeof thingy but who cares
	memcpy(m.mem, a.value, a.len * sizeof(uint8_t)) ; 

	printf("\n+---------------------------------------+\n") ;
	disassemble(&m) ;

	while(getc(stdin) != EOF)
	{
		printf("\033[2J");
		printf("\033[0;0H") ;
		vm_step(&m) ;
		vm_log(&m) ;
	}
	vm_delete(&m) ;

	node_delete(n) ;
	lexer_delete(&l) ;
	asm_delete(&a) ;
}
