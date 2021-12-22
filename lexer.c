#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

lexer_t lexer_create(const char *buffer) 
{
	lexer_t l = {0} ;

	l.buff_len = strlen(buffer) ;
	l.buffer = malloc(l.buff_len) ;
	memcpy(l.buffer, buffer, l.buff_len) ;

	l.list = NULL ;
	l.list_len = 0 ;
	l.current = 0 ;

	for(int i = 0; i < l.buff_len; i++)
	{
		element_t e = {0, l.buffer + i, 0} ;

		switch(buffer[i])
		{
			case 0:
			case ' ':
			case '\t':
			case '\n': continue ;

			case ';': while(buffer[i++] != '\n') ; i--; continue;

			case '(': e.type = TOKEN_LPAREN; e.len = 1 ; break ;
			case ')': e.type = TOKEN_RPAREN; e.len = 1 ; break ;
			case '\'':e.type = TOKEN_QUOTE ; e.len = 1 ; break ;
			case '#': e.type = TOKEN_HASH  ; e.len = 1 ; break ;
			case ':': e.type = TOKEN_COLON ; e.len = 1 ; break ;

			// case '-':
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':

				  e.type = TOKEN_NUMBER ;
				  e.len = i ;
				  while(i < l.buff_len)
				  {
					  if(strchr("0123456789", l.buffer[i]))
					  {
						  i++ ;
						  continue ;
					  }
					  break ;
				  }
				  e.len = i - e.len ;
				  i-- ;
				  break ;

			case '"':
				  e.type = TOKEN_STRING ;
				  e.len = i ;
				  i++ ;
				  while(i < l.buff_len)
				  {
					  if(l.buffer[i] == '"')
						  break ;
					  i++ ;
				  }
				  e.len = i - e.len + 1 ;
				  break ;

			default:
				  e.type = TOKEN_ATOM;
				  e.len = i ;
				  while(i < l.buff_len)
				  {
					  if(strchr(" \t\n()#:\"'", l.buffer[i]))
						  break ;
					  i++ ;
				  }
				  e.len = i - e.len ;
				  i-- ;
		}

		if(l.list_len % 4 == 0)
			l.list = realloc(l.list, sizeof(element_t) * (l.list_len+4)) ;
		l.list[l.list_len] = e ;
		l.list_len++ ;
	}

	return  l ;
}

void lexer_delete(lexer_t *l) 
{
	free(l->buffer) ;
	free(l->list) ;
}

element_t lexer_advance(lexer_t *l) 
{
	if(l->current >= l->list_len)
		return (element_t){TOKEN_EOF, 0, 0} ;

	element_t e = l->list[l->current] ;
	l->current++ ;
	return e ;
}

void lexer_reset(lexer_t *l) 
{
	l->current = 0 ;
}

const char *token_enum_str [TOKEN_EOF] = 
{
	[TOKEN_LPAREN]="TOKEN_LPAREN",
	[TOKEN_RPAREN]="TOKEN_RPAREN",
	[TOKEN_QUOTE] ="TOKEN_QUOTE",
	[TOKEN_HASH]  ="TOKEN_HASH",
	[TOKEN_COLON] ="TOKEN_COLON",
	[TOKEN_NUMBER]="TOKEN_NUMBER",
	[TOKEN_STRING]="TOKEN_STRING",
	[TOKEN_ATOM]  ="TOKEN_ATOM"
} ;

void lexer_debug_prnt(lexer_t *l) 
{
	for(int i = 0; i < l->list_len; i++)
	{
		printf("[ %s\t", token_enum_str[l->list[i].type]) ;
		lexer_debug_element_prnt(l->list[i]) ;
		printf(" ]\n") ;
	}
}

void lexer_debug_element_prnt(element_t ele) 
{
	for(int i = 0; i < ele.len; i++)
	{
		putc(ele.value[i], stdout) ;
	}
}
