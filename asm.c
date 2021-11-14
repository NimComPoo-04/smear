#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asm.h"

static uint32_t symbol_lookup(element_t e)
{
	// TODO: implement a hash map to look up symbol

	if(e.len < 0 || e.len > 1)
	{
		printf("ERROR: Symbol is not defined!") ;
		exit(0) ;
	}

	switch(e.value[0])
	{
		case '+': return IC_ADD ;
		case '-': return IC_SUB ;
		case '*': return IC_MUL ;
		case '/': return IC_DIV ;
		case '%': return IC_MOD ;
	}

	return IC_ERROR ;
}

static uint8_t iselekeyword(element_t e)
{
	int ret = 0 ;

	char c = e.value[e.len] ;
	e.value[e.len] = 0 ;

	if(strcmp(e.value, "if") == 0) ret = KW_IF ;
	if(strcmp(e.value, "rep") == 0) ret = KW_REP ;
	if(strcmp(e.value, "def") == 0) ret = KW_DEF ;

	e.value[e.len] = c ;

	return ret ;
}

void asm_lst(asm_t *x, node_t *n)
{
	if(n == NULL) return ;
	if(n->first == NULL)
	{
		if(n->value.type == TOKEN_NUMBER)
		{
			char c = n->value.value[n->value.len] ;
			n->value.value[n->value.len] = 0 ;
			uint32_t ddx = atoi(n->value.value) ;
			n->value.value[n->value.len] = c ;

			asm_add(x, (VM_PUSH << 2) | 0) ;

			asm_add(x, (ddx >> 8*0) & 0xFF) ;
			asm_add(x, (ddx >> 8*1) & 0xFF) ;
			asm_add(x, (ddx >> 8*2) & 0xFF) ;
			asm_add(x, (ddx >> 8*3) & 0xFF) ;
		}
		else if(n->value.type == TOKEN_ATOM)
		{
			uint32_t ux = symbol_lookup(n->value) ;

			if(ux != IC_ERROR)
			{
				asm_add(x, (VM_LDX << 2) | 0) ;

				asm_add(x, (ux >> 0*8) & 0xFF) ;
				asm_add(x, (ux >> 1*8) & 0xFF) ;
				asm_add(x, (ux >> 2*8) & 0xFF) ;
				asm_add(x, (ux >> 3*8) & 0xFF) ;
			}
		}
	}
	else
	{

		if(n->first->value.type == TOKEN_ATOM)
		{
			int kb_wrd = iselekeyword(n->first->value) ;
			switch(kb_wrd)
			{
				case KW_NONE:
					{
						node_t *f = n->first->next ;

						while(f != NULL)
						{
							asm_lst(x, f) ;
							f = f->next ;
						}

						if(n->first->value.type == TOKEN_NUMBER)
						{
							printf("ERROR: function name can not be a number!\n") ;
							exit(0) ;
						}

						asm_lst(x, n->first) ;

						asm_add(x, (VM_LDY << 2) | 0) ;
						asm_add(x, ((n->len_sub_nodes-1) >> 0*8) & 0xFF) ;
						asm_add(x, ((n->len_sub_nodes-1) >> 1*8) & 0xFF) ;
						asm_add(x, ((n->len_sub_nodes-1) >> 2*8) & 0xFF) ;
						asm_add(x, ((n->len_sub_nodes-1) >> 3*8) & 0xFF) ;
						asm_add(x, (VM_INT << 2) | 0) ;

						uint32_t ud = (n->len_sub_nodes-1) * 4 ;
						asm_add(x, (VM_LDX << 2) | 0) ;
						asm_add(x, (ud >> 0*8) & 0xFF) ;
						asm_add(x, (ud >> 1*8) & 0xFF) ;
						asm_add(x, (ud >> 2*8) & 0xFF) ;
						asm_add(x, (ud >> 3*8) & 0xFF) ;
						asm_add(x, (VM_ADD << 2) | 1) ;
						asm_add(x, (VM_PUSH << 2) | 1) ;
					}
					break ;

				case KW_IF:
					{
						if(n->len_sub_nodes != 4)
						{
							printf("ERROR: if statement error!!\n") ;
							exit(0) ;
						}

						uint32_t edit_loc1 = 0 ;
						uint32_t edit_loc2 = 0 ;

						asm_lst(x, n->first->next) ;

						asm_add(x, (VM_POP << 2) | 1) ;
						asm_add(x, (VM_CMP << 2) | 0) ;

						asm_add(x, (VM_JZE << 2) | 0) ;
						edit_loc1 = x->len ;
						asm_add(x, 0) ;
						asm_add(x, 0) ;
						asm_add(x, 0) ;
						asm_add(x, 0) ;

						// IF CASE
						asm_lst(x, n->first->next->next) ;

						asm_add(x, (VM_JMP << 2) | 0) ;
						edit_loc2 = x->len ;
						asm_add(x, 0) ;
						asm_add(x, 0) ;
						asm_add(x, 0) ;
						asm_add(x, 0) ;

						x->value[edit_loc1] = (x->len >> 0*8) & 0xFF ;
						x->value[edit_loc1+1] = (x->len >> 1*8) & 0xFF ;
						x->value[edit_loc1+2] = (x->len >> 2*8) & 0xFF ;
						x->value[edit_loc1+3] = (x->len >> 3*8) & 0xFF ;

						// ELSE CASE
						asm_lst(x, n->first->next->next->next) ;

						x->value[edit_loc2] = (x->len >> 0*8) & 0xFF ;
						x->value[edit_loc2+1] = (x->len >> 1*8) & 0xFF ;
						x->value[edit_loc2+2] = (x->len >> 2*8) & 0xFF ;
						x->value[edit_loc2+3] = (x->len >> 3*8) & 0xFF ;

					}
					break ;
				case KW_REP:
					{
						if(n->len_sub_nodes != 3)
						{
							printf("ERROR: rep statement error!!\n") ;
							exit(0) ;
						}

						uint32_t edit_loc1 = 0 ;
						uint32_t edit_loc2 = 0 ;

						asm_lst(x, n->first->next) ;

						asm_add(x, (VM_POP << 2) | 1) ;
						asm_add(x, (VM_CMP << 2) | 1) ;

						edit_loc1 = x->len ;
						asm_add(x, (VM_JZE << 2) | 0) ;
						edit_loc2 = x->len ;
						asm_add(x, 0) ;
						asm_add(x, 0) ;
						asm_add(x, 0) ;
						asm_add(x, 0) ;

						asm_lst(x, n->first->next->next) ;

						asm_add(x, (VM_POP << 2) | 0) ;

						asm_add(x, (VM_JMP << 2) | 0) ;
						asm_add(x, (edit_loc1 >> 0*8) & 0xFF) ;
						asm_add(x, (edit_loc1 >> 1*8) & 0xFF) ;
						asm_add(x, (edit_loc1 >> 2*8) & 0xFF) ;
						asm_add(x, (edit_loc1 >> 3*8) & 0xFF) ;

						x->value[edit_loc2] = (x->len >> 0*8) & 0xFF ;
						x->value[edit_loc2+1] = (x->len >> 1*8) & 0xFF ;
						x->value[edit_loc2+2] = (x->len >> 2*8) & 0xFF ;
						x->value[edit_loc2+3] = (x->len >> 3*8) & 0xFF ;

						asm_add(x, (VM_PUSH << 2) | 1) ;
					}
					break ;
				case KW_DEF:
					printf("<-- not figured out yet ;-) -->\n") ;
				break ;
			}
		}
	}
}

asm_t assemble(node_t *n)
{
	asm_t d =  asm_create();

	node_t *x = n->first ;

	while(x != NULL)
	{
		asm_lst(&d, x) ;
		x = x->next ;
	}
	
	asm_add(&d, (VM_HALT << 2) | 0) ;

	return d;
}

#define TOU(a, b, c, d) (a | (b << 8) | (c << 16) | (d << 24))

static char *opcode_str[] =
{
	"LDA", "LDX", "LDY", "STA", "STX", "STY", "TAX", "TAY", "TAS", "TAI", "TXA",
	"TYA", "TSA", "TIA", "ADD", "SUB", "SHL", "SHR", "CMP", "JMP", "JLT", "JGT",
	"JEQ", "JZE", "JSR", "RET", "PUSH", "POP", "INT", "HALT"
} ;

static char *reg_str[] = { "A", "X", "Y", "IP"} ;

void disassemble(vm_t *m)
{
	for(uint32_t i = 0; (m->mem[i] >> 2) != VM_HALT && i < MEMCAP; i++)
	{
		printf("%x\t", i) ;

		switch(m->mem[i] >> 2)
		{
			case VM_LDA: case VM_LDX: case VM_LDY: 
				printf("%x %x %x %x %x\t", m->mem[i], m->mem[i+1], m->mem[i+2], m->mem[i+3], m->mem[i+4]) ;
				if((m->mem[i] & 3) == 0)
					printf("%s %d", opcode_str[m->mem[i] >> 2], TOU(m->mem[i+1], m->mem[i+2], m->mem[i+3], m->mem[i+4])) ;
				else
					printf("%s [%d]", opcode_str[m->mem[i] >> 2], TOU(m->mem[i+1], m->mem[i+2], m->mem[i+3], m->mem[i+4])) ;
				i += 4 ;
				break ;

			case VM_STA: case VM_STX: case VM_STY: case VM_JMP: case VM_JLT: 
			case VM_JGT: case VM_JEQ: case VM_JZE: case VM_JSR:
				printf("%x %x %x %x %x\t", m->mem[i], m->mem[i+1], m->mem[i+2], m->mem[i+3], m->mem[i+4]) ;
				printf("%s %d", opcode_str[m->mem[i] >> 2], TOU(m->mem[i+1], m->mem[i+2], m->mem[i+3], m->mem[i+4])) ;
				i += 4 ;
				break ;
			
			case VM_TAX: case VM_TAY: case VM_TXA: case VM_TYA: case VM_TAS:
			case VM_TAI: case VM_TSA: case VM_TIA:
			case VM_SHL: case VM_SHR: case VM_INT: case VM_HALT: case VM_CMP:
			case VM_RET:
				printf("%x\t\t", m->mem[i]) ;
				printf("%s", opcode_str[m->mem[i] >> 2]);
				break ;

			case VM_ADD: case VM_SUB:
				printf("%x\t\t", m->mem[i]);
				printf("%s $%s", opcode_str[m->mem[i] >> 2], (m->mem[i] & 3) ? "SP" : "A") ;
				break ;

			case VM_POP:
				printf("%x\t\t", m->mem[i]) ;
				printf("%s $%s", opcode_str[m->mem[i] >> 2], reg_str[m->mem[i] & 3]);
				break ;
			
			case VM_PUSH:
				if((m->mem[i] & 3) == 0)
				{
					printf("%x %x %x %x %x\t", m->mem[i], m->mem[i+1], m->mem[i+2], m->mem[i+3], m->mem[i+4]) ;
					printf("%s %d", opcode_str[m->mem[i] >> 2], TOU(m->mem[i+1], m->mem[i+2], m->mem[i+3], m->mem[i+4])) ;
					i += 4 ;
				}
				else
				{
					printf("%x\t\t", m->mem[i]) ;
					printf("%s $%s", opcode_str[m->mem[i] >> 2], reg_str[(m->mem[i] & 3) - 1]) ;
				}
				break ;
		}
		
		printf("\n") ;
	}
}

// helper functions

asm_t asm_create()
{
	return (asm_t){0, 0} ;
}

void asm_add(asm_t *a, uint8_t x)
{
	if(a->len % 4 == 0)
	{
		a->value = realloc(a->value, sizeof(uint8_t) * (a->len + 4)) ;
	}
	a->value[a->len] = x ;
	a->len++ ;
}

void asm_rem(asm_t *a)
{
	 a->len-- ;
}

void asm_delete(asm_t *a)
{
	free(a->value) ;
}
