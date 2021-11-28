#include <stdlib.h>
#include <stdio.h>
#include "vm.h" 
vm_t vm_create(void)
{
	vm_t v = {0} ;
	v.mem = malloc(MEMCAP) ;
	v.R[REG_SP] = MEMCAP ;
	return v ;
}

void vm_step(vm_t *v)
{
#	define INS_PT (v->R[REG_IP])
#	define OPCODE (v->mem[INS_PT])
#	define RS     (v->R[(v->mem[INS_PT+1] & 0xF)])
#	define RD     (v->R[(v->mem[INS_PT+1] >> 4)])
#	define IMM    (v->mem[INS_PT+2] | v->mem[INS_PT+3] << 8)
#	define JIM    (v->mem[INS_PT+1] | v->mem[INS_PT+2] << 8)

#	define FLAG_ON(x) (v->F[x] = 1)
#	define FLAG_OFF(x) (v->F[x] = 0)

	switch(OPCODE)
	{
		case VM_NOP: INS_PT += 1; break;

		case VM_HALT: break;

		case VM_ADD:  RS += RD  ; INS_PT += 2; break;
		case VM_ADDI: RS += IMM ; INS_PT += 4; break;
		case VM_SUB:  RS -= RD  ; INS_PT += 2; break;
		case VM_SUBI: RS -= IMM ; INS_PT += 4; break;
		case VM_AND:  RS &= RD  ; INS_PT += 2; break;
		case VM_ANDI: RS &= IMM ; INS_PT += 4; break;
		case VM_NOT:  RS  =~RS  ; INS_PT += 2; break;
		case VM_NOTI: RS  =~IMM ; INS_PT += 4; break;
		case VM_SHL:  RS <<= RD ; INS_PT += 2; break;
		case VM_SHLI: RS <<= IMM; INS_PT += 4; break;
		case VM_SHR:  RS >>= RD ; INS_PT += 2; break;
		case VM_SHRI: RS >>= IMM; INS_PT += 4; break;

		case VM_CMP:
			      if(RS > RD) FLAG_ON(FLAG_GT); else FLAG_OFF(FLAG_GT);
			      if(RS < RD) FLAG_ON(FLAG_LT); else FLAG_OFF(FLAG_LT);
			      if(RS == RD)FLAG_ON(FLAG_EQ); else FLAG_OFF(FLAG_EQ);

			      if(RD == 0 || RS == 0) FLAG_ON(FLAG_ZE);
			      else FLAG_OFF(FLAG_ZE);
			      INS_PT += 2;
			      break;

		case VM_CMPI:
			      if(RS > (uint32_t)IMM) FLAG_ON(FLAG_GT); else FLAG_OFF(FLAG_GT);
			      if(RS < (uint32_t)IMM) FLAG_ON(FLAG_LT); else FLAG_OFF(FLAG_LT);
			      if(RS == (uint32_t)IMM)FLAG_ON(FLAG_EQ); else FLAG_OFF(FLAG_EQ);

			      if(RS == 0 || IMM == 0) FLAG_ON(FLAG_ZE);
			      else FLAG_OFF(FLAG_ZE);
			      INS_PT += 4;
			      break;

		case VM_JMP: INS_PT = JIM; break;

		case VM_JLT: INS_PT = v->F[FLAG_LT] ? (uint32_t)JIM : (INS_PT + 3); break;
		case VM_JGT: INS_PT = v->F[FLAG_GT] ? (uint32_t)JIM : (INS_PT + 3); break;
		case VM_JEQ: INS_PT = v->F[FLAG_EQ] ? (uint32_t)JIM : (INS_PT + 3); break;
		case VM_JZE: INS_PT = v->F[FLAG_ZE] ? (uint32_t)JIM : (INS_PT + 3); break;

		case VM_JLE: INS_PT = v->F[FLAG_LT] && v->F[FLAG_EQ] ? (uint32_t)JIM : (INS_PT + 3); break;
		case VM_JGE: INS_PT = v->F[FLAG_GT] && v->F[FLAG_EQ] ? (uint32_t)JIM : (INS_PT + 3); break;

		case VM_JNE: INS_PT = !v->F[FLAG_EQ] ? (uint32_t)JIM : (INS_PT + 3); break;
		case VM_JNZ: INS_PT = !v->F[FLAG_ZE] ? (uint32_t)JIM : (INS_PT + 3); break;

		case VM_JSR: v->R[REG_RP] = INS_PT;
			     INS_PT = JIM;
			     INS_PT += 3;
			     break;

		case VM_JRE: INS_PT = RS;
			     INS_PT += 2;
			     break;

		case VM_JAR: v->R[REG_RP] = INS_PT;
			     INS_PT = RS;
			     INS_PT += 2; 
			     break;

		case VM_LDR: RS = RD; INS_PT += 2; break;
		case VM_LDI: RS = IMM; INS_PT += 4; break;

		case VM_LDDI: RS = v->mem[IMM]; INS_PT += 4; break;
		case VM_LDDR: RS = v->mem[RD]; INS_PT += 2; break;
		case VM_LDII: RS = v->mem[v->mem[IMM]]; INS_PT += 4; break;
		case VM_LDIR: RS = v->mem[v->mem[RD]]; INS_PT += 2; break;

		case VM_STDI: v->mem[IMM] = RD; INS_PT += 4; break;
		case VM_STDR: v->mem[RS] = RD; INS_PT += 2; break;
		case VM_STII: v->mem[v->mem[IMM]] = RD; INS_PT += 4; break;
		case VM_STIR: v->mem[v->mem[RS]] = RD; INS_PT += 4; break;

		case VM_LOG: vm_log(v) ;
			     INS_PT++;
			     break;
		case VM_INT: FLAG_ON(FLAG_IN);
			     INS_PT++ ;
			     break ;
	}
}

void vm_log(vm_t *v)
{
	printf("┌──────────────┬──────────────┬──────────────┬──────────────┐\n");
	printf("| A : %8x | B : %8x | C : %8x | I : %8x |\n",
			v->R[REG_A], v->R[REG_B], v->R[REG_C], v->R[REG_I]);
	printf("├──────────────┼──────────────┴──────────────┴──────────────┘\n");
	printf("| T : %8x |\n", v->R[REG_T]);
	printf("├──────────────┼──────────────┐\n");
	printf("| SI :%8x | DI :%8x |\n", v->R[REG_SI], v->R[REG_DI]);
	printf("├──────────────┼──────────────┼──────────────┬──────────────┐\n");
	printf("| BP :%8x | RP :%8x | SP :%8x | IP :%8x |\n",
			v->R[REG_BP], v->R[REG_RP], v->R[REG_SP], v->R[REG_IP]);
	printf("└──────────────┴──────────────┴──────────────┴──────────────┘\n\n");

	printf("┌────────┬────────┬────────┬────────┬────────┐\n") ;
	printf("│ LT : %d │ GT : %d │ EQ : %d │ ZE : %d │ IN : %d │\n",
			v->F[FLAG_LT], v->F[FLAG_GT], v->F[FLAG_EQ], v->F[FLAG_ZE], v->F[FLAG_IN]);
	printf("└────────┴────────┴────────┴────────┴────────┘\n\n") ;
}

void vm_exec(vm_t *v)
{
	while(1) vm_step(v) ;
}

void vm_delete(vm_t *v)
{
	free(v->mem) ;
}
