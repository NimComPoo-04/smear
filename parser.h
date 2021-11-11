#ifndef _PARSER_H_
#define _PARSER_H_

#include "lexer.h"

typedef struct node_t
{
	element_t value ; // very cool
	struct node_t *first ; // sub node first
	struct node_t *last ; // sub node second
	struct node_t *next ; // the next subnode
	unsigned int len_sub_nodes ; // number of subnodes
} node_t;

node_t *node_create(element_t value) ;
void node_attach_child(node_t *n, node_t *x) ;
void node_attach_next(node_t *n, node_t *x) ;
void node_delete(node_t *n) ;

node_t *parse(lexer_t *l) ;
node_t *parse_list(lexer_t *l) ;

void parser_debug_prnt(node_t *n, int x) ;

#endif
