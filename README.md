# smear

This is a lisp like programming language that I am attempting to build

Lists:

(10 11 12) -> this is a list and its fine

hash map to store symbols.
list to show execution cycles.

(define x 10)

("+" -> add)
("-" -> sub)
("\*" -> mul)
("/" -> div)
("%" -> div)

## Opcodes for the virtual machine

NOP, HALT, INT,

ADD : A = X + Y,
AND : A = X & Y,
NOT : A = ~X,
SHL : A = X << Y,
SHR : A = X >> Y,
ROL : A = rotleft(X),
ROR : A = rotright(X),

CMP : compare X and Y,
(JMP, JE, JNE, JG, JGE, JL, JLE, JZ) : to I,

LDR -- imm (5)
    -- mem (5)
    -- reg (1)

STR -- imm (5)
    -- mem (5)
    -- reg (1)
    -- ind (5),

LDM -- imm (5)
    -- mem (5)
    -- reg (1)
    -- ind (5),

STM -- imm (5)
    -- mem (5)
    -- reg (1)
    -- ind (5),

LEA I -- mem (5)
    I -- off (1)
    I -- reg (1),

PUSH,
POP,

TAS,
TSA,
TXA,
TAX,
TAI,
TIA
