#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "lexer.h"

int main(void)
{
	char prog[] = "(define *f* (cons 10 '(1 2 3 4))) '10 (+ 10 (* 10 2) (/ 23 21))" ;

	lexer_t l = lexer_create(prog) ;
	lexer_debug_prnt(&l) ;
	lexer_reset(&l) ;

	node_t *n = parse(&l) ;
	parser_debug_prnt(n, 0) ;

	node_delete(n) ;
	lexer_delete(&l) ;
}
