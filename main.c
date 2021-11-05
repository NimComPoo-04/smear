#include <stdlib.h>
#include <stdio.h>
// #include "parser.h"
// #include "lexer.h"
#include "vm.h"

int main(void)
{
/*
	char prog[] = "10 20 (* 10 10 (+ 32 78)) (define x (fn (a b c) (+ a b c)))" ;

	lexer_t l = lexer_create(prog) ;
	lexer_debug_prnt(&l) ;
	lexer_reset(&l) ;

	node_t *n = parse(&l) ;
	parser_debug_prnt(n, 0) ;

	node_delete(n) ;
	lexer_delete(&l) ;
*/
	vm_t m = vm_create(2048) ;

	m.mem[0] = VM_LDX ;
	m.mem[1] = 0 ;
	m.mem[2] = 0 ;
	m.mem[3] = 0 ;
	m.mem[4] = 0 ;
	m.mem[5] = VM_LDI ;
	m.mem[6] = 12 ;
	m.mem[7] = 0 ;
	m.mem[8] = 0 ;
	m.mem[9] = 0 ;
	m.mem[10] = VM_INT ;
	m.mem[11] = VM_HALT ;
	m.mem[12] = 'H' ;
	m.mem[13] = 'i' ;
	m.mem[14] = '!' ;
	m.mem[15] = '\n' ;
	m.mem[16] = '\0' ;

	while((getc(stdin), !feof(stdin)))
	{
		vm_step(&m) ;
		vm_log(&m) ;
	}

	vm_delete(&m) ;
}
