#include <stdlib.h>
#include <stdio.h>
#include "compiler.h"

static FILE *wf = NULL ;

static const element_t IF = {TOKEN_ATOM, "if", 2} ;
static const element_t REP= {TOKEN_ATOM, "rep", 3} ;
static const element_t LET= {TOKEN_ATOM, "let", 3} ;
static const element_t FN = {TOKEN_ATOM, "fn", 2} ;

static const element_t ADD = {TOKEN_ATOM, "+", 1} ;
static const element_t SUB = {TOKEN_ATOM, "-", 1} ;
static const element_t MUL = {TOKEN_ATOM, "*", 1} ;
static const element_t DIV = {TOKEN_ATOM, "/", 1} ;
static const element_t IDIV = {TOKEN_ATOM, "//", 2} ;
static const element_t MOD = {TOKEN_ATOM, "%", 1} ;
static const element_t GT = {TOKEN_ATOM, ">", 1} ;
static const element_t LT = {TOKEN_ATOM, "<", 1} ;
static const element_t EQ = {TOKEN_ATOM, "=", 1} ;
static const element_t AND = {TOKEN_ATOM, "&", 1} ;

static int fn_ret = 0 ;

int ele_equ(element_t x, element_t f)
{
	if(f.len != x.len) return 0 ;
	for(int i = 0; i < f.len; i++)
		if(x.value[i] != f.value[i])
			return 0 ;
	return 1 ;
}

void com_arg(node_t *x, const char *c)
{
	fprintf(wf, "(") ;
	while(x)
	{
		com_select(x) ;
		if(x->next != NULL)
		{
			fprintf(wf, "%s ", c) ;
		}
		x = x->next ;
	}
	fprintf(wf, ")") ;
}

void com_list(node_t *x)
{
	if(ele_equ(x->value, IF))
	{
		int d = fn_ret ;
		fn_ret = 0 ;

		com_select(x) ;
		if(x == NULL)
		{
			fprintf(stderr, "SYNTAX ERROR\n") ;
			exit(0) ;
		}
		x = x->next ;
		com_select(x) ;

		fprintf(wf, " then\n") ;


		if(x == NULL)
		{
			fprintf(stderr, "SYNTAX ERROR\n") ;
			exit(0) ;
		}
		x = x->next ;

		if(d && x->value.type != TOKEN_LPAREN)
			fprintf(wf, "return ") ;
		else
			fn_ret = d ;

		com_select(x) ;

		fprintf(wf, "\nelse\n") ;

		if(x == NULL)
		{
			fprintf(stderr, "SYNTAX ERROR\n") ;
			exit(0) ;
		}
		x = x->next ;

		if(d && x->value.type != TOKEN_LPAREN)
			fprintf(wf, "return ") ;
		else
			fn_ret = d ;

		com_select(x) ;

		fprintf(wf, "\nend\n") ;

		if(x->next != NULL)
		{
			fprintf(stderr, "SYNTAX ERROR\n") ;
			exit(0) ;
		}
	}
	else if(ele_equ(x->value, REP))
	{
		fn_ret = 0 ;

		fprintf(wf, " while ") ;
		if(x == NULL)
		{
			fprintf(stderr, "SYNTAX ERROR\n") ;
			exit(0) ;
		}
		x = x->next ;
		com_select(x) ;

		fprintf(wf, " do\n") ;
		if(x == NULL)
		{
			fprintf(stderr, "SYNTAX ERROR\n") ;
			exit(0) ;
		}
		x = x->next ;
		com_select(x) ;

		fprintf(wf, "\nend\n") ;

		if(x->next != NULL)
		{
			fprintf(stderr, "SYNTAX ERROR\n") ;
			exit(0) ;
		}
	}
	else if(ele_equ(x->value, LET))
	{
		//printf("local ") ; 

		if(x == NULL)
		{
			fprintf(stderr, "SYNTAX ERROR\n") ;
			exit(0) ;
		}
		x = x->next ;
		com_select(x) ;

		fprintf(wf, " = ") ; 

		if(x == NULL)
		{
			fprintf(stderr, "SYNTAX ERROR\n") ;
			exit(0) ;
		}
		x = x->next ;
		com_select(x) ;

		fprintf(wf, "\n");
	}
	else if(ele_equ(x->value, FN))
	{
		fprintf(wf, "function ") ;

		if(x == NULL)
		{
			fprintf(stderr, "SYNTAX ERROR\n") ;
			exit(0) ;
		}
		x = x->next ;
		com_arg(x->first, ",") ;

		fprintf(wf, "\n") ;

		x = x->next ;
		while(x)
		{
			if(x->next == NULL)
				fn_ret = 1 ;
			com_select(x) ;
			x = x->next ;
			fprintf(wf, "\n") ;
		}
		fn_ret = 0 ;

		fprintf(wf, "end\n") ;
	}
	else if(ele_equ(x->value, ADD))
	{
		x = x->next ;
		com_arg(x, "+") ;
	}
	else if(ele_equ(x->value, SUB))
	{
		x = x->next ;
		com_arg(x, "-") ;
	}
	else if(ele_equ(x->value, MUL))
	{
		x = x->next ;
		com_arg(x, "*") ;
	}
	else if(ele_equ(x->value, DIV))
	{
		x = x->next ;
		com_arg(x, "/") ;
	}
	else if(ele_equ(x->value, IDIV))
	{
		x = x->next ;
		com_arg(x, "//") ;
	}
	else if(ele_equ(x->value, MOD))
	{
		x = x->next ;
		com_arg(x, "%") ;
	}
	else if(ele_equ(x->value, AND))
	{
		x = x->next ;
		com_arg(x, "and") ;
	}
	else if(ele_equ(x->value, GT))
	{
		x = x->next ;
		com_arg(x, ">") ;
	}
	else if(ele_equ(x->value, LT))
	{
		x = x->next ;
		com_arg(x, "<") ;
	}
	else if(ele_equ(x->value, EQ))
	{
		x = x->next ;
		com_arg(x, "==") ;
	}
	else 
	{
		com_select(x) ;
		x = x->next ;
		com_arg(x, ",") ;
	}
}

void com_atom(node_t *x)
{
	if(fn_ret)
	{
		fprintf(wf, "return ") ;
		fn_ret = 0 ;
	}

	for(int i = 0; i < x->value.len; i++)
	{
		fprintf(wf, "%c", x->value.value[i]) ;
	}

	fprintf(wf, " ") ;
}

void com_quote(node_t *x)
{
	fprintf(wf, " {") ;
	while(x)
	{
		com_select(x) ;
		if(x->next != NULL)
			fprintf(wf, ", ") ;
		x = x->next ;
	}
	fprintf(wf, "} ") ;
}

void com_hash(node_t *x)
{
	com_select(x) ;
	x = x->next ;
	fprintf(wf, " [") ;
	com_select(x) ;
	fprintf(wf, "] ") ;
}

void com_select(node_t *x)
{
	if(x->value.type == TOKEN_LPAREN)
	{
		if(x->first != NULL)
			com_list(x->first) ;
	}
	else if(x->value.type == TOKEN_HASH)
	{
		if(x->len_sub_nodes < 2)
			com_hash(x->first->first) ;
	}
	else if(x->value.type == TOKEN_QUOTE)
	{
		com_quote(x->first->first) ;
	}
	else
	{
		com_atom(x) ;
	}
}

void compile(node_t *n, FILE *fx)
{	
	wf = fx ;
	node_t *x = n->first ;

	while(x)
	{
		com_select(x) ;
		x = x->next ;
	}
}
