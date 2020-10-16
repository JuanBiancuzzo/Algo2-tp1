CC=gcc
VAL=valgrind
NAME=evento_pesca
CFLAGS=-g -Wall -Wconversion -Werror -std=c99
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes

build: main.c
	$(CC) $(CFLAGS) *.c -o $(NAME)

exe: build
	clear
	./$(NAME) pokemon_arrecife.csv pokemon_acuario.csv

leak: build
	clear
	$(VAL) $(VFLAGS) ./$(NAME)

debug: build
	clear
	gdb ./$(NAME) -tui

limpear_acuario: build pokemon_acuario.csv
	rm pokemon_acuario.csv
	touch pokemon_acuario.csv
	clear
