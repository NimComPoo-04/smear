CC = gcc
CFLAGS = -Wall -Wextra -ggdb -O0 -std=c11 -pedantic

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, obj/%.o, $(SRC))

build:
	@mkdir -p obj
	@make smear

smear: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o: %.c
	$(CC) $(CFLAGS) -o $@ $^ -c

clean:
	-rm $(OBJ) smear
