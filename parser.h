#ifndef _PARSER_H_
#define _PARSER_H_

typedef struct node_t
{
	int type ;
	token_t value ;
	struct node_t *next ;
} node_t;

#endif
