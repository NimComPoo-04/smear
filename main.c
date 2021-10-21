#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "lexer.h"

int main(void)
{
	char prog[] = "(define *x* (cons \"Hello, World!!\" 10 '(10 11 12 42)))" ;

	lexer_t l = lexer_create(prog) ;
	lexer_debug_prnt(&l) ;
	lexer_reset(&l) ;

	list_t *x = list_create(&(l.list[0])) ;

	for(int i = 1; i < l.list_len; i++)
	{
		list_insert(x, &(l.list[i]), i) ;
	}

	for(int i = 0 ; i < l.list_len; i++)
	{
		element_t *e = list_get(x, i) ;
		lexer_debug_element_prnt(*e) ;
		printf(" ") ;
	}

	list_delete(x, NULL) ;
	lexer_delete(&l) ;

	printf("\n") ;
}
