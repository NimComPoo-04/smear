#ifndef _VM_H_
#define _VM_H_

#include <stdint.h>

#define MEMCAP (64)

enum
{
	VM_LDA, // loads immidiate number or direct number to A
	VM_LDX,
	VM_LDY,
	
	VM_STA, // store value of A to mem
	VM_STX,
	VM_STY,
	
	VM_TAX, // transfer A to X
	VM_TAY,
	VM_TXA,
	VM_TYA,

	VM_ADD, // add x, y to a
	VM_SUB,
	VM_SHL,
	VM_SHR,
	
	VM_CMP, // compare x to y then set the status
	VM_JMP, // jump to location
	VM_JLT, // jump less than
	VM_JGT, // jump greater than
	VM_JEQ, // jump if equals
	VM_JZE, // jumps if zero
	
	VM_JSR, // jump subroutine
	VM_RET, // returns from subroutine
	
	VM_PUSH, // pushes number onto stack
	VM_POP, // pops off the stack and then put into register
	VM_INT, // interupt fun ig ;-)
	VM_HALT // stops the machine
} ;

typedef struct
{
	uint32_t A ; // Accumulator
	uint32_t X ; // X index register
	uint32_t Y ; // Y index register

	uint32_t SP ; // stack pointer
	uint32_t IP ; // instruction pointer
	uint8_t PS ; // processor status [ LT | GT | EQ | ZE ]

	uint8_t *mem ; 
} vm_t ;

vm_t vm_create(void) ;
void vm_step(vm_t *v) ;
void vm_log(vm_t *v) ;
void vm_delete(vm_t *v) ;

#endif
