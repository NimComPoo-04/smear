#ifndef _PARSER_H_
#define _PARSER_H_

#include "lexer.h"
#include "list.h"

typedef struct node_t
{
	element_t value ;
	list_t *sub_node ;
} node_t ;

node_t *parser_create_node(element_t e) ;
void parser_attach_node(node_t *n, element_t e) ;
void parser_delete_node(node_t *n) ;

node_t *parser_create(lexer_t *l) ;
void parser_delete(lexer_t *l) ;

#endif
