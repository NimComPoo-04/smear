#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "lexer.h"
#include "vm.h"
#include "asm.h"

int main(void)
{
	char prog[] = "(+ 1 2 (* 11 10 1))" ;

	lexer_t l = lexer_create(prog) ;
	//lexer_debug_prnt(&l) ;
	lexer_reset(&l) ;

	node_t *n = parse(&l) ;
	//parser_debug_prnt(n, 0) ;

	asm_t a = assemble(n) ;
	vm_t m = vm_create() ;

	// like i am weird for doing the sizeof thingy but who cares
	memcpy(m.mem, a.value, a.len * sizeof(uint8_t)) ; 

	/* fibonacci very cool 

	m.mem[0] = VM_LDX << 2 ;
	m.mem[1] = 1 ;
	m.mem[2] = 0 ;
	m.mem[3] = 0 ;
	m.mem[4] = 0 ;
	m.mem[5] = VM_LDY << 2 ;
	m.mem[6] = 0 ;
	m.mem[7] = 0 ;
	m.mem[8] = 0 ;
	m.mem[9] = 0 ;
	m.mem[10] = VM_ADD << 2 ;	  // adds x y -> a
	m.mem[11] = (VM_PUSH << 2) | 1 ;  // save a
	m.mem[12] = VM_TAX << 2 ;	  // move x to a
	m.mem[13] = VM_TYA << 2 ;	  // move a to y in effect y to x
	m.mem[14] = (VM_POP << 2) | 1 ;   // move saved a to x
	m.mem[15] = VM_JMP << 2 ;         // jump to the add statement
	m.mem[16] = 10 ;
	m.mem[17] = 0 ;
	m.mem[18] = 0 ;
	m.mem[19] = 0 ;
	m.mem[20] = VM_HALT << 2 ;

	*/

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
