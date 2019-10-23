CC=gcc
FLAGS=-Wall -g 
LIBS=-lpthread -ltermbox
OUT=lineracer
INCLUDE=-I headers/
OBJS=./out/bike.o ./out/main.o

$(OUT): $(OBJS) ./out
	$(CC) $(FLAGS) $(LIBS) $(INCLUDE) -o $(OUT) $(OBJS) 

./out:
	mkdir ./out

./out/main.o: main.c headers/main.h headers/constants.h 
	$(CC) $(FLAGS) $(INCLUDE) -o ./out/main.o -c main.c 
	
./out/bike.o: bike.c headers/bike.h
	$(CC) $(FLAGS) $(INCLUDE) -o ./out/bike.o -c bike.c

.Phony: run

run:
	./$(OUT)

clean:
	rm $(OUT) out/*
