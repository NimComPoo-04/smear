#ifndef _LEXER_H_
#define _LEXER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum
{
	TOKEN_NOP,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_FQUOTE,
	TOKEN_BQUOTE,
	TOKEN_COMMA,
	TOKEN_COMMA_AT,
	TOKEN_STRING,
	TOKEN_HASH,
	TOKEN_ATOM,
	TOKEN_EOF
} ;

typedef struct
{
	int type ;
	char *value ;
	int len ;
} token_t ;

token_t *tokenize(char *str) ;
void token_str(token_t *t, char *str) ;
void token_dump(FILE *f, token_t *t) ;

#endif
