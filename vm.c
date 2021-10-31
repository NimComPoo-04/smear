#include <stdio.h>
#include <stdlib.h>
#include "vm.h"

vm_t vm_create(void)
{
	vm_t v = {0} ;
	v.A = 0 ;
	v.X = 0 ;
	v.Y = 0 ;
	v.SP = MEMORY_CAP-1 ;
	v.IP = 0 ;
	v.PS = 0 ;
	v.mem = calloc(sizeof(uint8_t), MEMORY_CAP) ;

	return v ;
}

static void pic(vm_t *v)
{
	(void)v ;
	printf("<-- PIC -->\n") ;
}

void vm_step(vm_t *v)
{
	uint8_t opcode = v->mem[v->IP] ;
	uint32_t h = (v->mem[v->IP+4] << 24) | (v->mem[v->IP+3] << 16) | (v->mem[v->IP+2] << 8) | v->mem[v->IP+1] ;

	switch(opcode)
	{
		case VM_HALT:break ;
		case VM_INT: pic(v); v->IP++; break ;
		case VM_PUSH: v->mem[v->SP] = v->X; v->SP--; v->IP++; break ;
		case VM_POP:  v->X = v->mem[v->SP]; v->SP++; v->IP++; break ;

		case VM_LDA: v->A = h; v->IP += 5; break;
		case VM_LDX: v->X = h; v->IP += 5; break;
		case VM_LDY: v->Y = h; v->IP += 5; break;

		case VM_MOV: v->X = v->mem[v->A]; v->IP++; break ;
		case VM_ADD: v->X = v->X + v->Y; v->IP++; break ;
		case VM_SUB: v->X = v->X - v->Y; v->IP++; break ;
		case VM_AND: v->X = v->X & v->Y; v->IP++; break ;
		case VM_OR:  v->X = v->X | v->Y; v->IP++; break ;
		case VM_LSH: v->X = v->X << v->Y; v->IP++; break ;
		case VM_RSH: v->X = v->X >> v->Y; v->IP++; break ;
		case VM_NOT: v->X = ~v->X; v->IP++; break ;

		case VM_JMP: v->IP = v->A; break ;
		case VM_JLT: if((v->PS >> 0) & 0x1) v->IP = v->A; break ;
		case VM_JGT: if((v->PS >> 1) & 0x1) v->IP = v->A; break ;
		case VM_JEQ: if((v->PS >> 2) & 0x1) v->IP = v->A; break ;
		//case VM_JNE: if((v->PS >> 3) & 0x1) v->IP = v->A; break ;

		case VM_CMP: if(v->X < v->Y) v->PS = 0x8;
			     if(v->X > v->Y) v->PS = 0x4;
			     if(v->X == v->Y) v->PS = 0x2;
			     //if(v->X < 0) v->PS = 0x1;
			     break ;
		default:
			     printf("<-- Undefined -->") ;
	}
}

static char *str_vm_ins[VM_CMP+1] =
{
	[VM_HALT] = "HALT",
	[VM_INT]  = "INT",
	[VM_PUSH] = "PUSH",
	[VM_POP]  = "POP",
	[VM_LDA]  = "LDA",
	[VM_LDX]  = "LDX",
	[VM_LDY]  = "LDY",
	[VM_MOV]  = "MOV",
	[VM_ADD]  = "ADD",
	[VM_SUB]  = "SUB",
	[VM_AND]  = "AND",
	[VM_OR]   = "OR" ,
	[VM_LSH]  = "LSH",
	[VM_RSH]  = "RSH",
	[VM_NOT]  = "NOT",
	[VM_JMP]  = "JMP",
	[VM_JLT]  = "JLT",
	[VM_JGT]  = "JGT",
	[VM_JEQ]  = "JEQ",
	[VM_JNE]  = "JNE",
	[VM_CMP]  = "CMP"
} ;

void vm_dump(vm_t *v)
{
	printf("A : 0x%x\n", v->A) ;
	printf("X : 0x%x\n", v->X) ;
	printf("Y : 0x%x\n\n", v->Y) ;

	printf("PS: %d %d %d\n", (v->PS >> 0) & 1, (v->PS >> 1) & 1, (v->PS >> 2) & 1) ;

	printf("\nINSTRUCTION\tIP: %x\n\n", v->IP) ;
	for(uint32_t i = 0; v->mem[i] != VM_HALT; i++)
	{
		printf("\t%s", str_vm_ins[v->mem[i]]) ;
		if(v->mem[i] == VM_LDA || v->mem[i] == VM_LDX || v->mem[i] == VM_LDY)
		{
			uint32_t h = (v->mem[i+4] << 24) | (v->mem[i+3] << 16) | (v->mem[i+2] << 8) | v->mem[i+1] ;
			printf("\t%d", h) ;
			i+=4 ;
		}
		printf("\n") ;
	}

	printf("\nSTACK\t\tSP: %x\n\n", v->SP) ;
	for(uint32_t i = v->SP; i < MEMORY_CAP; i++)
		printf("\t%x\t%x\n", i, v->mem[i]) ;

	printf("\n") ;
}

void vm_load(vm_t *v, uint8_t *mem, int l)
{
	for(int i = 0; i < l; i++)
	{
		v->mem[i] = mem[i] ;
	}
}

void vm_delete(vm_t *v)
{
	free(v->mem) ;
}
