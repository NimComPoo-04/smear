#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

#include "lexer.h"
#include "parser.h"
#include "compiler.h"

int main(int argv, char **args)
{
	if(argv < 2) 
	{
		fprintf(stderr, "ERROR: INPUT THE NAME OF THE SOURCE FILE\n") ;
		return 1 ;
	}
#if 0
	// TODO: fix this person he is broken beyond repair
	// TBH what happed is something is getting at the end and idk what to do

	FILE *f = fopen(args[1], "r") ;
	if(f == NULL)
	{
		fprintf(stderr, "ERROR: THE FILE DOES NOT EXISTS\n") ;
		return 1 ;
	}

	fseek(f, 0, SEEK_END) ;
	int num = ftell(f) ;
	fseek(f, 0, SEEK_SET) ;
	char *prog = calloc(num, sizeof(char));
	fread(prog, sizeof(char), num, f) ;
#endif
#if 1
	int f = open(args[1], O_RDONLY, 0) ;
	char *prog = mmap(0, 1, PROT_READ, MAP_SHARED, f, 0) ;
#endif

	FILE *fw = fopen("a.lua", "w+") ;

	printf("+---------------------------------------+\n") ;
	printf("%s\n", prog) ;
	printf("\n+---------------------------------------+\n") ;
	lexer_t l = lexer_create(prog) ;
	lexer_debug_prnt(&l) ;
	lexer_reset(&l) ;

	printf("\n+---------------------------------------+\n") ;
	node_t *n = parse(&l) ;
	parser_debug_prnt(n, 0) ;
	printf("\n+---------------------------------------+\n") ;
	compile(n, fw) ;

	node_delete(n) ;
	lexer_delete(&l) ;

	//free(prog) ;
	fclose(fw) ;
	//fclose(f) ;
	munmap(prog, 1) ;
	close(f) ; 
}
