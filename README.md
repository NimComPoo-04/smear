# SMEAR

## TL;DR Transpiles to lua therefore dependency LUA (tested on version 5.1) also the error handeling is very bad.

This is smear a very bad programming langauge.
It is kind of like lisp without the best part of lisp
(SCUFFED LISP which is kind of what smear kinda symbolizes)

But I don't care like literally

It can take input and put out output and thats all that is
required.

It is my first langauge and I am very happy that i could make it without
giving the frick up!!

I wanted to roll my own vm but it turns out its gooing to
take a lot of time but i had to get this langauge out before 
chrismas (you know as a christmas present to myself) so i just 
transpiled to lua specificaly version 5.1 ('cause neovim ships with that).

That reveals my editor of choice does't it. Good I will flex my vimceps to 
all the world 'cause i am a total noob!!

and like Davie504 said *"My pp is small and ugly but it is my pp and i love it"*

If you (for what every reason) have the bright idea of using this
turd of a programming language just remember that it is buggy as buggy
as casu marzu.

yeah that is pretty much it idk what else to say.

Oh yeah I almost forgot the error handling of this language eats dirt
for dinner.

## Instructions

Clone the repository
```bash
git clone https://github.com/NimComPoo-04/smear
```
Compiling the compiler should not be difficult just go in the directory and run
```bash
make all
```

The compilation should generate a executable file called smear.
2 programs are given as example. demo.smear, rule110.smear
to compile them just use this comand: 
```bash
./smear demo.smear
```

The compilation should generate a a.lua file to run the file use this command
```bash
lua a.lua
```

## Usage

Everything is done between ()

so calling a function looks like ({function-name} {arguments})

#### Keywords
```
if, let, fn, rep
+, -, /, %, *, >, <, =, &   »operators behave just like c«
```

##### IF
if behaves like normal if-conditional statements

**(if {condition} {true statement} {else statement})**

there is no 'else if' construct but it is possible to nest if statements

```
(if true
    (if true
        (print "a")
	(print "b")) 
    (print "c"))
```

there is one caviat tho. you can not have multiple statements in a if conditional
only a single statement

##### REP
rep is a short form of repeat. it repeats a single statement as long as the condition
is true

**(rep {condition} {statement})**

```
(rep (= 0 0) (print "Infinite loop!!, :D"))
```
same caviat goes here you can have only one statement 
##### LET
let declares a variable. it also redefines a variable

**(let {variable name} {value})**

```
(let x 10)
```

sets the variable x to 10

variables can be redefined. everything is imutable nothing changes state so 
the only way of changing state is to redefine the variable

there are 3 types of values array and scaler and functions

arrays are declared as

```
(let x '(10 11 12))
```

we can retrive values from array by

\#(x 1) gets the first value in array

arrays start at 1 not at 0

##### FN
this keyword is used to declare functions.

**(fn ({arguments}) {statements...})**

```
(let fibo (fn (a b c)
              (print a)
              (if (= c 0)
	          a
		  (fibo (+ a b) a (- c 1))))

(fibo 1 0 100)
```

functions can have multiple statements

the functions returns the last statement's evaluated value

##### Operators
they behave just like functions so basically

**({operator} {arguments})**

```
(print (+ 10 10 10))
```

##### Utility Functions
currently all the stdlib functions that are available in lua are accisible in
smear. you can directly call them.

[https://www.lua.org/docs.html](Lua Documentation)

io.write - can be used to write output to write output to stdout
io.read  - can be used to read input from stdin
print    - can be use to log output quickly

##### Comments
Comment lines start with the ';' symbol like assembly programs

This symbol can be used to create comment blocks which looks
asthetic ;-)

```
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                              ;;
;;  Comments are cool innit :D  ;;
;;                              ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
```
