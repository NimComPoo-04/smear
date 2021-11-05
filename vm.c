#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "vm.h"

vm_t vm_create(size_t mem)
{
	vm_t x = {0} ;
	x.SP = mem ;
	x.mem = calloc(mem, sizeof(uint8_t)) ;
	return x ;
}

static void pic(vm_t *m)
{
	uint32_t oi = m->X ;
	switch(oi)
	{
		case PIC_PRINT: printf("%s", &m->mem[m->I]) ; break ;
		default:
			printf("<-- Not implemented -->") ;
	}
}

static uint32_t tou32(uint8_t *buff) 
{
	return (buff[3] << 24) | (buff[2] << 16) | (buff[1] << 8) | buff[0] ;
}

static void toarr(uint32_t x, uint8_t *buff)
{
	buff[3] = (x >> 24) & 0xFF ;
	buff[2] = (x >> 16) & 0xFF ;
	buff[1] = (x >> 8) & 0xFF ;
	buff[0] = (x >> 0) & 0xFF ;
}

void vm_step(vm_t *m)
{
	uint8_t opcode = m->mem[m->IP] ;

	switch(opcode)
	{
		case VM_NOP: m->IP++; break ;
		case VM_HALT: return ;
		case VM_INT: pic(m) ; m->IP++; break ;

		case VM_ADD: m->A = m->X + m->Y; m->IP++; break ;
		case VM_SUB: m->A = m->X - m->Y; m->IP++; break ;
		case VM_MUL: m->A = m->X * m->Y; m->IP++; break ;
		case VM_DIV: m->A = m->X / m->Y; m->Y = m->X % m->Y; m->IP++; break ;
		case VM_AND: m->A = m->X & m->Y; m->IP++; break ;
		case VM_OR : m->A = m->X | m->Y; m->IP++; break ;
		case VM_XOR: m->A = m->X ^ m->Y; m->IP++; break ;
		case VM_NOT: m->A = ~m->X; m->IP++; break ;
		case VM_SHL: m->A = m->X << m->Y; m->IP++; break ;
		case VM_SHR: m->A = m->X >> m->Y; m->IP++; break ;

		case VM_CMP: m->PS = 0 ;
			     if(m->X < m->Y) m->PS |= 1 ; 
			     if(m->X > m->Y) m->PS |= 2 ; 
			     if(m->X == m->Y) m->PS |= 4 ; 
			     if(m->X == 0) m->PS |= 8 ; 
			     m->IP++ ;
			     break ;

		case VM_JMP: m->IP = m->I; break ;
		case VM_JLT: if(m->PS & 1) m->IP = m->I; break ;
		case VM_JGT: if(m->PS & 2) m->IP = m->I; break ;
		case VM_JEQ: if(m->PS & 4) m->IP = m->I; break ;
		case VM_JZE: if(m->PS & 8) m->IP = m->I; break ;

		case VM_LDA: m->A = tou32(&m->mem[m->IP+1]); m->IP+=5; break ;
		case VM_LDX: m->X = tou32(&m->mem[m->IP+1]); m->IP+=5; break ;
		case VM_LDY: m->Y = tou32(&m->mem[m->IP+1]); m->IP+=5; break ;
		case VM_LDI: m->I = tou32(&m->mem[m->IP+1]); m->IP+=5; break ;

		case VM_STA: toarr(m->A, &m->mem[m->I]); m->IP++; break ;
		case VM_STX: toarr(m->X, &m->mem[m->I]); m->IP++; break ;
		case VM_STY: toarr(m->Y, &m->mem[m->I]); m->IP++; break ;

		case VM_TAS: m->SP = m->A ; m->IP++; break ;
		case VM_TAI: m->I = m->A ; m->IP++; break ;
		case VM_TSA: m->A = m->SP ; m->IP++; break ;
		case VM_TIA: m->A = m->I ; m->IP++; break ;

		case VM_MOV: m->A = tou32(&m->mem[m->I]); m->IP++; break ;

		case VM_PUSH: toarr(m->A, &m->mem[m->SP-4]); m->SP-=4; break;
		case VM_POP:  m->A = tou32(&m->mem[m->SP]); m->SP+=4; break;

		default: printf("<-- Not Implemented -->\n") ;
	}
}

void vm_log(vm_t *m)
{
	printf("A: %d\n", m->A) ;
	printf("X: %d\n", m->X) ;
	printf("Y: %d\n", m->Y) ;
	printf("I: %d\n\n", m->I) ;

	printf("SP: %d\n", m->SP) ;
	printf("IP: %d\n", m->IP) ;
	printf("PS: %d\n\n", m->PS) ;

	printf(":: %d ::\n", m->mem[m->IP]) ;
	printf(":: %d ::\n\n", m->mem[m->SP]) ;
}

void vm_delete(vm_t *m)
{
	free(m->mem) ;
}
