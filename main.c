#include "lexer.h"

char program[] = "(+ 10 (/ 10 5) (str-len \"Hello World\"))" ;

int main(void)
{
	token_t *t = tokenize(program) ;
	token_dump(stdout, t) ;
}
