#ifndef _LEXER_H_
#define _LEXER_H_

enum
{
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_QUOTE,
	TOKEN_HASH,
	TOKEN_COLON,
	TOKEN_NUMBER,
	TOKEN_STRING,
	TOKEN_ATOM,
	TOKEN_EOF
} ;

typedef struct
{
	int type ;
	char *value ;
	int len ;
} element_t ;

typedef struct
{
	char *buffer ;
	int buff_len ;

	element_t *list ;
	int list_len ;
	int current ;
} lexer_t ;

lexer_t lexer_create(const char *buffer) ;
void lexer_delete(lexer_t *l) ;

element_t lexer_advance(lexer_t *l) ;
void lexer_reset(lexer_t *l) ;

void lexer_debug_prnt(lexer_t *l) ;
void lexer_debug_element_prnt(element_t ele) ;

#endif
