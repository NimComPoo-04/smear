#include <stdlib.h>
#include <stdio.h>

#include "parser.h"

node_t *parser_create_node(element_t e)
{
}

void parser_attach_node(node_t *n, element_t e)
{
}

void parser_delete_node(node_t *n)
{
}

node_t *parser_create(lexer_t *st)
{
	(void) st ;
	return NULL ;
}

void parser_delete(lexer_t *l)
{
	(void)l ;
}
