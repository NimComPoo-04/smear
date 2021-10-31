# smear

This is a lisp like programming language that I am attempting to build

Lists:

(10 11 12) -> this is a list and its fine

but what int the world is this

(10 11 (23 42) 11)

(+ 10 11 (* 32 45 77) 32 (* 1 3))

> 10 > 11 > 32 > 45 > 77 > 3 > 3 ! > 32 > 1 > 3 > 2 > 2 ! > 4 > 0 !

.label 10

(eval '(some shit))

> SOME > SHIT ! 

+-------+
| VALUE |
| VALUE |
| VALUE | <- SP ! | E -> 0 | C -> 3 | L -> '(10 10 10)
| VALUE |
| VALUE |
| VALUE |
| VALUE |
| VALUE |
+-------+

(+ 10 (- 10 11) 12)

----------------------------------------
SMEAR_MAN
[
	REGISTERS: A, X, Y, SP, IP, PS
	MEMORY: [0 -- 2047]
	PIC: map(in, out)
]

HALT, INT,
PUSH, POP,
LDA, LDX, LDY,
MOV,
ADD, SUB, AND, OR, LSH, RSH, NOT
JMP, JLT, JGT, JEQ, JNE,
CMP,

Opcodes

HALT		Halts the system		0x00
INT		Calls the internal api		0x01

PUSH		Pushes a X onto stack		0x02
POP		Pops a X off the stack		0x03
LDA		Loads number to register	0x04
LDX		Loads number to register	0x05
LDY		Loads number to register	0x06
MOV		Moves X to M[A] a number	0x07

ADD		Adds X and Y register to X	0x08
SUB		Subs X and Y register to X	0x09
AND		Ands X and Y register to X	0x0A
OR		Ors X and Y register to X	0x0B
LSH		Lshs X using Y register to X	0x0C
RSH		Rshs X using Y register to X	0x0D
NOT		Nots X and stores it to X	0x0E

JMP		Jumps to A that it no really	0x0F
JLT		Jumps to A that it no really	0x10
JGT		Jumps to A that it no really	0x12
JEQ		Jumps to A that it no really	0x13
JNE		Jumps to A that it no really	0x14
CMP		Compares X and Y		0x15
