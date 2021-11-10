#include <stdlib.h>

#include "asm.h"

uint8_t *assemble(FILE *f)
{
	char buffer[80] = {0} ;
	// uint32_t ip = 0 ;

	while(!feof(f))
	{
		fscanf(f, "%s", buffer) ;
		printf(buffer) ;
	}

	return NULL ;
}

void disassemble(const uint8_t *val)
{
	(void)val ;
}
