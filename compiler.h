#ifndef _COMPILER_H_
#define _COMPILER_H_

#include <stdint.h>
#include "parser.h"

typedef struct
{
	node_t *prog ;
	uint8_t *bin ;
	int len ;
} compiler_t ;

compiler_t compiler_create(node_t *c) ;
void compiler_exec(compiler_t *c) ;
void compiler_delete(compiler_t *c) ;

void compiler_add(compiler_t *c, uint8_t val) ;

#endif
