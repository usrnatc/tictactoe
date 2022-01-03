CC=gcc
CFLAGS= -o tictactoe --std=gnu99 -g -Wall -pedantic
.DEFAULT_GOAL:= cgame
.PHONY: clean

cgame: tictactoe.c ; $(CC) tictactoe.c $(CFLAGS)

clean: ; rm -rf tictactoe
