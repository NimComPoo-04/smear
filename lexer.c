#include "lexer.h"

token_t *tokenize(char *str)
{
	int len = strlen(str) ;
	token_t *t = NULL ;
	int cur = 0 ;

	for(int i = 0; i <= len; i++)
	{
		token_t tok = {0, str+i, 0} ;

		switch(str[i])
		{
			case 0:
				tok.type = TOKEN_EOF;
				break ;
			case ' ':
			case '\t':
			case '\n':
				continue ;
			case '(': tok.type = TOKEN_LPAREN; tok.len = 1; break ;
			case ')': tok.type = TOKEN_RPAREN; tok.len = 1; break ;
			case '\'': tok.type = TOKEN_FQUOTE; tok.len = 1; break ;
			case '`': tok.type = TOKEN_BQUOTE; tok.len = 1; break ;
			case '#': tok.type = TOKEN_HASH; tok.len = 1; break ;

			case ',':
				  if(str[i+1] == '@')
				  {
					  tok.type = TOKEN_COMMA_AT;
					  tok.len = 2 ;
					  i++ ;
					  break ;
				  }
				  tok.type = TOKEN_COMMA_AT;
				  tok.len = 1 ;
				  break ;

			case '"':
				  tok.type = TOKEN_STRING ;
				  i++ ;
				  while(i < len)
				  {
					  if(str[i] == '"') break ;
					  i++ ;
				  }
				  tok.len = str + i - tok.value ;
				  break ;
			default:
				  tok.type = TOKEN_ATOM ;
				  while(i < len)
				  {
					  if(strchr(" \t\n()\"'#`,@", str[i]) != NULL)
						  break ;
					  i++ ;
				  }
				  tok.len = str + i - tok.value ;
				  i-- ;
		}

		if(cur % 4 == 0)
			t = realloc(t, sizeof(token_t) * (cur + 4)) ;
		t[cur] = tok ;
		cur++ ;
	}

	return t ;
}

void token_str(token_t *t, char *str)
{
	memcpy(str, t->value, t->len) ;
}

void token_dump(FILE *f, token_t *t)
{
	while(t->type != TOKEN_EOF)
	{
		char c = t->value[t->len] ;
		t->value[t->len] = 0 ;
		fprintf(f, "%d %s\n", t->type, t->value) ;
		t->value[t->len] = c ;

		t++ ;
	}
}
