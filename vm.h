#ifndef _VM_H_
#define _VM_H_

#define MEMORY_CAP (2048)

#include <stdint.h>

enum
{
	VM_HALT,
	VM_INT,
	VM_PUSH,
	VM_POP,
	VM_LDA,
	VM_LDX,
	VM_LDY,
	VM_MOV,
	VM_ADD,
	VM_SUB,
	VM_AND,
	VM_OR,
	VM_LSH,
	VM_RSH,
	VM_NOT,
	VM_JMP,
	VM_JLT,
	VM_JGT,
	VM_JEQ,
	VM_JNE,
	VM_CMP,
} ;

typedef struct
{
	uint32_t A ;
	uint32_t X ;
	uint32_t Y ;
	uint32_t SP ;
	uint32_t IP ;
	uint32_t PS ; // [LT | GT | EQ | NE]
	uint8_t *mem ;
} vm_t ;

vm_t vm_create(void) ;
void vm_step(vm_t *v) ;
void vm_load(vm_t *v, uint8_t *mem, int i) ;
void vm_dump(vm_t *v) ;
void vm_delete(vm_t *v) ;

#endif
