#ifndef _COMPILER_H_
#define _COMPILER_H_

#include <stdio.h>
#include "parser.h"

void compile(node_t *n, FILE *f) ;
void com_list(node_t *x) ;
void com_atom(node_t *x) ;
void com_select(node_t *x) ;

#endif
