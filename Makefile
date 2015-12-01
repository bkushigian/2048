CC=g++
CFLAGS=-c -Wall -lncurses -lboost_regex

all: 2048

2048: boardDriver.o
	$(CC) $(CFLAGS) 
boardDriver.o: board_2048.o board_t.o gameStorage.o gamestate.o globals.o AI.o rowFill.o


