#ifndef _VM_H_
#define _VM_H_

#include <stdint.h>

enum
{
	PIC_PRINT
} ;

enum
{
	VM_NOP,
	VM_HALT,
	VM_INT,

	VM_ADD,
	VM_SUB,
	VM_MUL,
	VM_DIV,
	VM_AND,
	VM_OR,
	VM_XOR,
	VM_NOT,
	VM_SHL,
	VM_SHR,

	VM_CMP,
	VM_JMP,
	VM_JLT,
	VM_JGT,
	VM_JEQ,
	VM_JZE,

	VM_LDA,
	VM_LDX,
	VM_LDY,
	VM_LDI,
	VM_STA,
	VM_STX,
	VM_STY,
	VM_TAS,
	VM_TAI,
	VM_TSA,
	VM_TIA,
	VM_MOV,

	VM_PUSH, // Not needed but still
	VM_POP
} ;

typedef struct
{
	uint32_t A ; // Acumulator
	uint32_t X ; // X index register
	uint32_t Y ; // Y index register
	uint32_t I ; // Index register

	uint32_t SP ; // stack pointer
	uint32_t IP ; // instruction pointer
	uint8_t  PS ; // Programming Status

	uint8_t *mem;
} vm_t ;

vm_t vm_create(size_t mem) ;
void vm_step(vm_t *m) ;
void vm_log(vm_t *m) ;
void vm_delete(vm_t *m) ;

#endif
