CC=gcc
VAL=valgrind
NAME=evento_pesca
CFLAGS=-g -Wall Wconversion -Werror -std=c99
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes 

build: main.c
	$(CC) $(CFLAGS) *.c -o $(NAME)

exe: build
	./$(NAME)

leak: build
	$(VAL) $(VFLAGS) ./$(NAME)
