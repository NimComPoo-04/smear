#ifndef _VM_H_
#define _VM_H_

#include <stdint.h>

#define MEMCAP (1 << 16)

enum
{
	REG_A,	// accumulator
	REG_B,	// base register
	REG_C,	// count register
	REG_I,	// index register

	REG_T,  // temporary register

	REG_SI,	// source index
	REG_DI,	// destination index

	REG_BP,	// base pointer
	REG_RP, // retern pointer
	REG_SP,	// stack pointer
	REG_IP, // instruction poniter

	REG_COUNT   // number of register
} ;

enum
{
	FLAG_LT, // less than
	FLAG_GT, // greater than
	FLAG_EQ, // equal 
	FLAG_ZE, // zero
	FLAG_IN,  // interupt
	FLAG_COUNT
} ;

typedef struct
{
	uint32_t R[REG_COUNT] ;
	uint8_t F[FLAG_COUNT]; 
	uint8_t *mem ;
} vm_t ;

enum
{
	VM_NOP, VM_HALT, 
	VM_ADD, VM_ADDI,
	VM_SUB, VM_SUBI,
	VM_AND, VM_ANDI,
	VM_NOT, VM_NOTI,
	VM_SHL, VM_SHLI,
	VM_SHR, VM_SHRI,

	VM_CMP, VM_CMPI,

	VM_JMP, VM_JLT,
	VM_JGT, VM_JLE,
	VM_JGE, VM_JZE,
	VM_JEQ, VM_JNE,
	VM_JNZ, VM_JSR,
	VM_JRE, VM_JAR,

	VM_LDR, // register with other register
	VM_LDI, // register with immiditae

	VM_LDDI, // register with memory
	VM_LDDR,
	VM_LDII,
	VM_LDIR,

	VM_STDI, // memory with other register
	VM_STDR,
	VM_STII,
	VM_STIR,

	VM_LOG, VM_INT
} ;

vm_t vm_create(void) ;
void vm_step(vm_t *v) ;
void vm_log(vm_t *v) ;
void vm_exec(vm_t *v) ;
void vm_delete(vm_t *v) ;

#endif
