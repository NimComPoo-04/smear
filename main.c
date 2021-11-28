#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "lexer.h"
#include "vm.h"

int main(void)
{
#if 0
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

	node_delete(n) ;
	lexer_delete(&l) ;
#endif
	vm_t v = vm_create() ;

	v.mem[0] = VM_LDI ;
	v.mem[1] = REG_A ;
	v.mem[2] = 3 ;
	v.mem[3] = 0 ;
	v.mem[4] = VM_LDI ;
	v.mem[5] = REG_B ;
	v.mem[6] = 2 ;
	v.mem[7] = 0 ;
	v.mem[8] = VM_JMP ;
	v.mem[9] = 32 ;
	v.mem[10] = 0 ;

	v.mem[32] = VM_ADD ;
	v.mem[33] = (REG_A) | (REG_B << 4) ;
	v.mem[34] = VM_ADDI ;
	v.mem[35] = REG_B ;
	v.mem[36] = 4 ;
	v.mem[37] = 0 ;
	v.mem[38] = VM_LOG ;
	v.mem[39] = VM_HALT ;

	vm_exec(&v) ;
	vm_delete(&v) ;
}
