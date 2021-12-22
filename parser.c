#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

node_t *parse(lexer_t *l)
{
	element_t null = {TOKEN_ATOM, "PROG", 4} ;
	element_t e = lexer_advance(l) ;
	node_t *n = node_create(null) ; 

	while(e.type != TOKEN_EOF)
	{
		if(e.type == TOKEN_LPAREN)
			node_attach_child(n, parse_list(l)) ;
		else if(e.type == TOKEN_HASH || e.type == TOKEN_QUOTE)
			node_attach_child(n, parse_one_ele_list(l, e.type)) ;
		else
			node_attach_child(n, node_create(e)) ;

		e = lexer_advance(l) ;
	}

	return n ;
}


node_t *parse_one_ele_list(lexer_t *l, int t)
{
	element_t e = lexer_advance(l) ;

	element_t f = {t, (t == TOKEN_QUOTE ? "QUOTE":"HASH"), (t == TOKEN_QUOTE ? 5 : 4)} ;
	node_t *n = node_create(f) ;

	if(e.type == TOKEN_LPAREN)
		node_attach_child(n, parse_list(l)) ;
	else if(e.type == TOKEN_HASH || e.type == TOKEN_QUOTE)
		node_attach_child(n, parse_one_ele_list(l, e.type)) ;
	else
		node_attach_child(n, node_create(e)) ;

	return n ;
}

node_t *parse_list(lexer_t *l)
{
	element_t e = lexer_advance(l) ;

	element_t list = {TOKEN_LPAREN, "LIST", 4} ;
	node_t *n = node_create(list) ;

	while(e.type != TOKEN_EOF)
	{
		if(e.type == TOKEN_LPAREN) node_attach_child(n, parse_list(l)) ;
		else if(e.type == TOKEN_HASH || e.type == TOKEN_QUOTE)
			node_attach_child(n, parse_one_ele_list(l, e.type)) ;
		else if(e.type == TOKEN_RPAREN) return n ;
		else node_attach_child(n, node_create(e)) ;

		e = lexer_advance(l) ;
	}

	return n ;
}

node_t *node_create(element_t value)
{
	node_t *n = calloc(sizeof(node_t), 1) ;
	n->value = value ;
	n->first = 0 ;
	n->last = 0 ;
	n->next = 0 ;

	return n ;
}

void node_attach_child(node_t *n, node_t *x)
{
	if(n->first == NULL)
	{
		n->first = x ;
		n->last = x ;
	}
	else
	{
		n->last->next = x ;
		n->last = x ;
	}
	n->len_sub_nodes++ ;
}

void node_attach_next(node_t *n, node_t *x)
{
	if(n->next == NULL)
		n->next = x ;
	else
		node_attach_next(n->next, x) ;
}

void node_delete(node_t *n)
{
	if(n == NULL) return ;

	node_t *x = n->next ;
	node_t *d = n->first ;
	free(n) ;

	node_delete(x) ;
	node_delete(d) ;
}

void parser_debug_prnt(node_t *n, int x)
{
	if(n == NULL) return ;
	char st[] = "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t" ;
	st[x] = 0 ;
	printf("%s", st) ;
	lexer_debug_element_prnt(n->value) ;
	printf("\n") ;
	parser_debug_prnt(n->first, x+1) ;
	parser_debug_prnt(n->next, x) ;
}
