#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "vm.h"

vm_t vm_create()
{
	vm_t v = {0} ;

	v.A = 0 ;
	v.X = 0 ;
	v.Y = 0 ;

	v.SP = MEMCAP ;
	v.IP = 0 ;
	v.PS = 0 ;

	v.mem = calloc(sizeof(uint8_t), MEMCAP) ;

	return v ;
}

static uint32_t tou(uint8_t *m)
{
	return m[0] | (m[1] << 8) | (m[2] << 16) | (m[3] << 24) ;
}

static void toarr(uint32_t x, uint8_t *m)
{
	m[0] = (x >> 8 * 0) & 0xFF ;
	m[1] = (x >> 8 * 1) & 0xFF ;
	m[2] = (x >> 8 * 2) & 0xFF ;
	m[3] = (x >> 8 * 3) & 0xFF ;
}

static void interupt_controler(vm_t *m)
{
	uint32_t sp = m->SP;
	switch(m->X)
	{
		case IC_ADD:
			for(uint32_t i = 0; i < m->Y; i++)
			{
				m->A = tou(&m->mem[sp]) + m->A ;
				sp = sp + 4 ;
			}
			break ;

		case IC_MUL:
			for(uint32_t i = 0; i < m->Y; i++)
			{
				m->A = tou(&m->mem[sp]) * m->A ;
				sp = sp + 4 ;
			}
			break ;

		case IC_SUB:
			for(uint32_t i = 0; i < m->Y-1; i++)
			{
				m->A = tou(&m->mem[sp]) + m->A ;
				sp = sp + 4 ;
			}
			m->A = tou(&m->mem[sp]) - m->A; 
			break ;

		case IC_DIV:
			for(uint32_t i = 0; i < m->Y-1; i++)
			{
				m->A = tou(&m->mem[sp]) * m->A ;
				sp = sp + 4 ;
			}
			m->A = tou(&m->mem[sp]) / m->A; 
			break ;

		default: printf("<-- Wrong Intrupt -->") ;
	}
}

void vm_step(vm_t *v)
{
	uint8_t opcode = v->mem[v->IP] ;

	switch(opcode >> 2)
	{
		case VM_LDA: 
			if((opcode & 3) == 0) 
				v->A = tou(&v->mem[v->IP+1]);
			else if((opcode & 3) == 1)
				v->A = v->mem[tou(&v->mem[v->IP+1])];
			v->IP+=4;
			break;

		case VM_LDX: 
			if((opcode & 3) == 0) 
				v->X = tou(&v->mem[v->IP+1]);
			else if((opcode & 3) == 1)
				v->X = v->mem[tou(&v->mem[v->IP+1])];
			v->IP+=4;
			break;

		case VM_LDY: 
			if((opcode & 3) == 0) 
				v->Y = tou(&v->mem[v->IP+1]);
			else if((opcode & 3) == 1)
				v->Y = v->mem[tou(&v->mem[v->IP+1])];
			v->IP+=4;
			break;

		case VM_STA: toarr(v->A, &v->mem[tou(&v->mem[v->IP+1])]); v->IP+=4; break;
		case VM_STX: toarr(v->X, &v->mem[tou(&v->mem[v->IP+1])]); v->IP+=4; break;
		case VM_STY: toarr(v->Y, &v->mem[tou(&v->mem[v->IP+1])]); v->IP+=4; break;

		case VM_TAX: v->A = v->X; break;
		case VM_TAY: v->A = v->Y; break;
		case VM_TXA: v->X = v->A; break;
		case VM_TYA: v->Y = v->A; break;

		case VM_TSA: v->SP = v->A; break;
		case VM_TIA: v->IP = v->A; break;
		case VM_TAS: v->A = v->SP; break;
		case VM_TAI: v->A = v->IP; break;

		case VM_ADD:
			if((opcode & 3) == 0)
				v->A = v->X + v->Y;
			else if((opcode & 3) == 1)
				v->SP += v->X ;
			break;

		case VM_SUB:
			if((opcode & 3) == 0)
				v->A = v->X - v->Y;
			else if((opcode & 3) == 1)
				v->SP -= v->X ;
			break ;

		case VM_SHL: v->A = v->X << v->Y; break;
		case VM_SHR: v->A = v->X >> v->Y; break;

		case VM_CMP:
			     v->PS = 0 ;
			     if(v->X < v->Y) v->PS |= 8 ;
			     if(v->X > v->Y) v->PS |= 4 ;
			     if(v->X == v->Y) v->PS |= 2 ;
			     if(v->X == 0) v->PS |= 1 ;
			     break ;

		case VM_JMP: v->IP = tou(&v->mem[v->IP+1]); return;
		case VM_JLT: if(((v->PS & 8) >> 3) == 1) v->IP = tou(&v->mem[v->IP+1]); return;
		case VM_JGT: if(((v->PS & 4) >> 2) == 1) v->IP = tou(&v->mem[v->IP+1]); return;
		case VM_JEQ: if(((v->PS & 2) >> 1) == 1) v->IP = tou(&v->mem[v->IP+1]); return;
		case VM_JZE: if(((v->PS & 1) >> 0) == 1) v->IP = tou(&v->mem[v->IP+1]); return;

		case VM_JSR:
			toarr(v->IP, &v->mem[v->SP-4]) ;
			v->SP -= 4 ;
			v->IP = tou(&v->mem[v->IP+1]) ;
			return ;

		case VM_RET:
			v->IP = tou(&v->mem[v->SP]) ;
			v->SP += 4 ;
			return ;

		case VM_PUSH:
			if((opcode & 3) == 0)
			{
				toarr(tou(&v->mem[v->IP+1]), &v->mem[v->SP-4]) ;
				v->IP += 4 ;
				v->SP -= 4 ;
			}
			else if((opcode & 3) == 1)
			{
				toarr(v->A, &v->mem[v->SP-4]) ;
				v->SP -= 4 ;
			}
			else if((opcode & 3) == 2)
			{
				toarr(v->X, &v->mem[v->SP-4]) ;
				v->SP -= 4 ;
			}
			else if((opcode & 3) == 3)
			{
				toarr(v->Y, &v->mem[v->SP-4]) ;
				v->SP -= 4 ;
			}
			break;

		case VM_POP:
			if((opcode & 3) == 0)
			{
				v->A = tou(&v->mem[v->SP]) ;
				v->SP+=4 ;
			}
			else if((opcode & 3) == 1)
			{
				v->X = tou(&v->mem[v->SP]) ;
				v->SP+=4 ;
			}
			else if((opcode & 3) == 2)
			{
				v->Y = tou(&v->mem[v->SP]) ;
				v->SP+=4 ;
			}
			else if((opcode & 3) == 3)
			{
				v->IP = tou(&v->mem[v->SP]) ;
				v->SP+=4 ;
			}

			break;

		case VM_INT:
			interupt_controler(v) ;
			break;

		case VM_HALT: /* do nothing ;-) */return ;

		default: printf("<-- Wront Opcode -->\n") ;
	}

	v->IP++ ;
}

void vm_log(vm_t *v)
{
	printf("%d\t%d\t%d\n", v->A, v->X, v->Y) ;
	printf("%d\t%d\n\n", v->SP, v->IP) ;
	for(uint32_t i = v->SP; i < MEMCAP; i++)
	{
		printf("%d\t%d\n", i, v->mem[i]) ;
	}
}

void vm_delete(vm_t *v)
{
	free(v->mem) ;
}
